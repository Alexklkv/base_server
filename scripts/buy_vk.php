<?php

	ob_start();

	define('STATUS_SUCCESS', 0);
	define('STATUS_ERROR', 1);

	define('ERROR_DATABASE', 2);
	define('ERROR_BAD_SIGNATURE', 10);
	define('ERROR_BAD_REQUEST', 11);
	define('ERROR_GOOD_NOT_EXIST', 20);
	define('ERROR_GOOD_NOT_AVAILABLE', 21);

	define('SOULS_PER_VOTE', 3);

	require_once "scripts/orders.inc.php";

	$orders = array(
		//TODO: add orders like:
		//'shows'			=> array('offer' => OFFER_PHOTO_SHOWS,		'price' => 3,	'unique' => "no",	'image' => "photo_shows_v2.png",	'title' => "Показы фотографий"),
		//'shows-special'		=> array('offer' => OFFER_PHOTO_SHOWS_SPECIAL,	'price' => 1,	'unique' => "always",	'image' => "photo_shows_v2.png",	'title' => "100 показов фотографий"),
		'champion-pack'		=> array('offer' => OFFER_CHAPMPION_PACK,		'price' => 10,	'unique' => "renew",	'image' => "champion_pack.png",		'title' => "Набор чемпиона"),
	);

	check_sig();

	$sql = new mysqli(DATABASE_HOST, DATABASE_USER, DATABASE_PASSWORD, DATABASE_NAME);

	$order = array(
		'transaction_id' => $sql->escape_string($_REQUEST['order_id']),
		'provider_id' => API_TYPE_VK,
		'service_id' => intval($_REQUEST['app_id']),
		'net_id' => $sql->escape_string($_REQUEST['receiver_id']),
		'type' => API_TYPE_VK
	);

	switch ($_REQUEST['notification_type'])
	{
		case "get_item":
		case "get_item_test":
		{
			$item = parse_item($_REQUEST['item']);

			print_status(STATUS_SUCCESS, array('title' => $item['title'], 'photo_url' => $item['image'], 'price' => $item['price'], 'item_id' => $_REQUEST['item']));
			break;
		}
		case "order_status_change":
		case "order_status_change_test":
		{
			if (empty($_REQUEST['status']) || $_REQUEST['status'] != "chargeable")
				print_status(STATUS_ERROR, ERROR_BAD_REQUEST, null, "Wrong order status");

			if (empty($_REQUEST['item_id']))
			{
				if (empty($_REQUEST['item_price']) || strpos($_REQUEST['item'], "offer") !== 0)
					print_status(STATUS_ERROR, ERROR_BAD_REQUEST, null, "Not enough params for processing offer");

				$price = intval($_REQUEST['item_price']);

				$order['offer'] = OFFER_VKONTAKTE;
				$order['amount'] = $price * SOULS_PER_VOTE;
				$order['revenue'] = $price;
				$order['unique'] = "no";
			}
			else
			{
				$item = parse_item($_REQUEST['item_id']);

				$order['offer'] = $item['offer'];
				$order['amount'] = $item['amount'];
				$order['revenue'] = $item['price'];
				$order['unique'] = $item['unique'];
			}

			$status = buy($sql, $order);
			switch ($status)
			{
				case ORDER_SUCCESS:
					print_status(STATUS_SUCCESS, array('order_id' => $order['transaction_id'], 'app_order_id' => $order['id']));
					break;
				case ORDER_ALREADY_PURCHASED:
					print_status(STATUS_ERROR, ERROR_GOOD_NOT_AVAILABLE, null, "Order already purchased");
					break;
				case ORDER_DATABASE_ERROR:
					print_status(STATUS_ERROR, ERROR_DATABASE, $sql, "Transaction insert error");
					break;
			}
			break;
		}
	}

	print_status(STATUS_ERROR, ERROR_BAD_REQUEST, null, "Wrong notification type");

	function parse_item($item)
	{
		global $orders;

		$params = explode("_", $item);

		$type = $params[0];

		$amount = 1;
		if (isset($params[1]))
			$amount = $params[1];

		if (isset($orders[$type]))
		{
			$order = &$orders[$type];

			$price = $order['price'];
			$price *= $amount;

			$title = "";
			if (isset($order['title']))
				$title = $order['title'];

			$image = LEGENDS_IMAGE_BASE.$order['image'];

			return array(
				'title' => $title,
				'image' => $image,
				'offer' => $order['offer'],
				'amount' => $amount,
				'price' => $price,
				'unique' => $order['unique']
			);
		}

		$souls = (strcasecmp($type, "souls") == 0);

		if (!$souls || $amount <= 0)
			print_status(STATUS_ERROR, ERROR_GOOD_NOT_EXIST, null, "Order not exist");

		$offer = OFFER_NONE;

		$price = $amount / SOULS_PER_VOTE;

		if ($amount == 1800)
			$price = 300;
		else if ($amount == 500)
			$price = 100;
		else if ($amount == 120)
			$price = 30;

		if ($amount >= 1500)
			$image = "large";
		else if ($amount >= 500)
			$image = "big";
		else if ($amount >= 150)
			$image = "medium";
		else
			$image = "small";

		$title = $amount." ".get_word_form($amount, ["кристалл", "криталлы", "кристаллов"]);

		return array(
			'title'	=> $title,
			'image' => LEGENDS_IMAGE_BASE."souls_".$image.".png",
			'offer' => $offer,
			'amount' => $amount,
			'price' => $price,
			'unique' => "no"
		);
	}

	function check_sig()
	{
		if (empty($_REQUEST['sig']) || empty($_REQUEST['notification_type']) || empty($_REQUEST['app_id']) || empty($_REQUEST['user_id']) || empty($_REQUEST['receiver_id']) || empty($_REQUEST['order_id']) || empty($_REQUEST['item']))
			print_status(STATUS_ERROR, ERROR_BAD_REQUEST, null, "Query params mismatch");

		$sig = $_REQUEST['sig'];
		unset($_REQUEST['sig']);

		$params = array();

		while (list($key, $value) = each($_REQUEST))
			$params[] = $key."=".$value;

		$_REQUEST['sig'] = $sig;

		sort($params);

		$query = implode("", $params);
		$query = md5($query.API_SECRET_VK);

		$_REQUEST['sig_my'] = $query;

		if ($query == $sig)
			return;

		print_status(STATUS_ERROR, ERROR_BAD_SIGNATURE, null, "Signature check failed");
	}

	function print_status($status, $code, $sql = null, $text = "")
	{
		if ($status == STATUS_SUCCESS)
		{
			ob_end_clean();
			header("Content-Type: application/json; encoding=utf-8");
			echo json_encode(array('response' => $code));
			exit;
		}

		print_r($_REQUEST);
		if ($sql != null && $sql->errno != 0)
			echo $sql->errno.", ".$sql->error."\n";
		$date = date("[d.m.Y H:i:s]");

		file_put_contents("logs/buy_vk.log", $date."\nstatus: ".$status.", code: ".$code.", message: ".$text."\n".ob_get_contents()."\n\n", FILE_APPEND);

		ob_end_clean();
		header("Content-Type: application/json; encoding=utf-8");
		echo json_encode(array('error' => array('error_code' => $code)));
		exit;
	}

?>