<?php

	ob_start();

	define('STATUS_SUCCESS', 0);
	define('STATUS_ERROR', 1);

	define('VERIFY_URL', "https://graph.facebook.com/");

	require_once "scripts/orders_fb.inc.php";

	if (!isset($_REQUEST['signed_request']) && !isset($_REQUEST['hub_mode']))
	{
		$request = @file_get_contents("php://input");

		check_sig($request);

		$payload = json_decode($request, true);
		if ($payload === false)
			print_status(STATUS_ERROR, "Source info is not a JSON");

		if (!isset($payload['object']) || $payload['object'] != "payments" || !isset($payload['entry']))
			print_status(STATUS_ERROR, "Unsupported JSON object");

		if (!is_array($payload['entry']))
			print_status(STATUS_ERROR, "Entry must be an array");

		$sql = new mysqli(DATABASE_HOST, DATABASE_USER, DATABASE_PASSWORD, DATABASE_NAME);

		foreach ($payload['entry'] as &$payment)
		{
			if (!in_array("actions", $payment['changed_fields']) && !in_array("disputes", $payment['changed_fields']) && !in_array("refund", $payment['changed_fields']) && !in_array("chargeback", $payment['changed_fields']))
				continue;

			process_payment($payment['id'], $sql);
		}

		print_status(STATUS_SUCCESS);
	}

	if (isset($_REQUEST['hub_mode']))
	{
		if (!isset($_REQUEST['hub_challenge']) || !isset($_REQUEST['hub_verify_token']))
			print_status(STATUS_ERROR, "Not enough params");

		if ($_REQUEST['hub_mode'] != "subscribe")
			print_status(STATUS_ERROR, "Incorrect hub_mode");

		if ($_REQUEST['hub_verify_token'] != API_FB_SUBCRIBE)
			print_status(STATUS_ERROR, "Incorrect token");

		print_status(STATUS_SUCCESS, $_REQUEST['hub_challenge']);
	}

	$payload = parse_signed_request($_REQUEST['signed_request']);
	if (!isset($_REQUEST['method']))
		die("No method was specified");

	$method = $_REQUEST['method'];

	switch ($method)
	{
		case "payments_get_item_price":
		{
			$order_info = parse_info($payload['payment']);

			$answer = json_encode(array('method' => "payments_get_item_price", 'content' => $order_info));

			print_status(STATUS_SUCCESS, $answer);
			break;
		}
		case "payments_item_update":
		{
			$sql = new mysqli(DATABASE_HOST, DATABASE_USER, DATABASE_PASSWORD, DATABASE_NAME);

			if ($payload === false)
				print_status(STATUS_ERROR, "Incorrect payment details");

			if ($payload['status'] != "completed")
				print_status(STATUS_ERROR, "Not completed transaction");

			process_payment($payload['payment_id'], $sql);

			print_status(STATUS_SUCCESS);
			break;
		}
	}

	print_status(STATUS_ERROR, "Incorrect method: ".$method);

	function parse_info($order)
	{
		global $orders, $multiple;

		if (!isset($order['product']) || !isset($order['quantity']) || !isset($order['user_currency']))
			print_status(STATUS_ERROR, "Not enough params");

		$product = get_product($order['product']);
		if (empty($product))
			print_status(STATUS_ERROR, "Bad product URL: ".$order['product']);

		$amount = intval($order['quantity']);
		if ($amount == 0)
			print_status(STATUS_ERROR, "Incorrect amount: ".$amount);

		$currency = $order['user_currency'];

		if ($currency != "RUB" && $currency != "EUR")
			$currency = "USD";

		if (isset($orders[$product]))
		{
			return array(
				'product' => $order['product'],
				'amount' => round($orders[$product]['price'][$currency], 2),
				'currency' => $currency
			);
		}

		$amount = get_amount($product);
		if ($amount == 0)
			print_status(STATUS_ERROR, "Bad product: ".$product);

		return array(
			'product' => $order['product'],
			'amount' => round($multiple[$product]['price'][$currency] * $amount, 2),
			'currency' => $currency
		);
	}

	function get_amount(&$product)
	{
		global $multiple;

		if (preg_match("/^(.+?)_(\d+)(_(en|ru))?\.html$/", $product, $matches) == 0)
			return 0;

		$product = $matches[1];
		$amount = intval($matches[2]);

		if (!isset($multiple[$product]))
			return 0;

		return $amount;
	}

	function get_product($url)
	{
		if (preg_match("/^.+\/([^\/]+)_(en|ru)(\.html)$/", $url, $matches) == 0)
			return "";

		return $matches[1].$matches[3];
	}

	function get_payment($payment_id)
	{
		$settings = array(
			'method' => "GET",
			'header' => "Content-Type: application/x-www-form-urlencoded".PHP_EOL
		);

		$context = stream_context_create(array('https' => $settings));

		$src = @file_get_contents(VERIFY_URL.$payment_id."?fields=actions,items,user,disputes&access_token=".API_FB_TOKEN, false, $context);
		if ($src === false)
			print_status(STATUS_ERROR, "Failed to query FB");

		$payment = json_decode($src, true);
		if ($payment === false)
			print_status(STATUS_ERROR, "Incorrect payment info");

		return $payment;
	}

	function process_payment($payment_id, &$sql)
	{
		global $orders, $multiple;

		$payment_info = get_payment($payment_id);

		$payed = false;
		foreach ($payment_info['actions'] as &$action)
		{
			if ($action['status'] != "completed")
				continue;

			$payed = true;
			break;
		}

		if (!$payed)
			return;

		if (isset($payment_info['disputes']) || isset($payment_info['refund']) || isset($payment_info['chargeback']))
		{
			add_refund($payment_info);
			return;
		}

		foreach ($payment_info['items'] as &$item)
		{
			$product = get_product($item['product']);
			if (empty($product))
				print_status(STATUS_ERROR, "Bad product URL: ".$item['product']);

			if (isset($orders[$product]))
			{
				$amount = isset($item['quantity']) ? $item['quantity'] : 1;
				$amount *= isset($orders[$product]['amount']) ? $orders[$product]['amount'] : 1;
				$info = $orders[$product];
			}
			else
			{
				$amount = get_amount($product);
				$info = $multiple[$product];
			}

			$order = array(
				'transaction_id' => $sql->escape_string($payment_info['id']),
				'provider_id' => API_TYPE_FB,
				'service_id' => 1,
				'net_id' => $sql->escape_string($payment_info['user']['id']),
				'type' => API_TYPE_FB
			);

			$order['offer'] = $info['offer'];
			$order['amount'] = $amount;
			$order['revenue'] = isset($orders[$product]['amount']) ? $info['price']['USD'] : $info['price']['USD'] * $amount;
			$order['unique'] = $info['unique'];

			$status = buy($sql, $order);
			switch ($status)
			{
				case ORDER_SUCCESS:
					break;
				case ORDER_ALREADY_PURCHASED:
					print_status(STATUS_ERROR, "Order already purchased");
					break;
				case ORDER_DATABASE_ERROR:
					print_status(STATUS_ERROR, "Transaction insert error", $sql);
					break;
			}
		}
	}

	function add_refund($payment_info)
	{
		ob_clean();
		print_r($payment_info);
		file_put_contents("logs/refund_fb.log", ob_get_contents()."\n\n", FILE_APPEND);
		ob_clean();
	}

	function parse_signed_request($signed_request)
	{
		list($encoded_sig, $payload) = explode(".", $signed_request, 2);

		$sig = base64_url_decode($encoded_sig);
		$data = json_decode(base64_url_decode($payload), true);

		if (strtoupper($data['algorithm']) !== "HMAC-SHA256")
			print_status(STATUS_ERROR, "Unknown algorithm. Expected HMAC-SHA256");

		$expected_sig = hash_hmac("sha256", $payload, API_SECRET_FB, $raw = true);
		if ($sig !== $expected_sig)
			print_status(STATUS_ERROR, "Bad Signed JSON signature!");

		return $data;
	}

	function base64_url_decode($input)
	{
		return base64_decode(strtr($input, "-_", "+/"));
	}

	function check_sig($request)
	{
		$headers = getallheaders();
		if (!isset($headers['X-Hub-Signature']))
			print_status(STATUS_ERROR, "Signature is missing");

		$sig = $headers['X-Hub-Signature'];

		$expected_sig = "sha1=".hash_hmac("sha1", $request, API_SECRET_FB);
		if ($sig !== $expected_sig)
			print_status(STATUS_ERROR, "Signature is wrong");
	}

	function print_status($status, $data = null, $sql = null)
	{
		if ($status == STATUS_SUCCESS)
		{
			ob_end_clean();
			header("HTTP/1.0 200 OK");

			if ($data != null)
				echo $data;
			exit;
		}

		print_r($_REQUEST);
		if ($sql != null && $sql->errno != 0)
			echo $sql->errno.",".$sql->error."\n";
		$date = date("[d.m.Y H:i:s]");

		file_put_contents("logs/buy_fb.log", $date."\nstatus: ".$status.", message: ".$data."\n".ob_get_contents()."\n\n", FILE_APPEND);

		ob_end_clean();
		header("HTTP/1.1 403 Forbidden");

		echo "error";
		exit;
	}

?>