<?php

	define('STATUS_SUCCESS', 1);
	define('STATUS_ERROR', 2);

	define('CHECK_URL', "https://graph.facebook.com/debug_token");

	require_once "scripts/defines.inc.php";

	header("Content-type: application/json; charset=utf-8");
	header("Access-control-allow-origin: *");

	if (empty($_REQUEST['id']) || empty($_REQUEST['token']))
		print_status(STATUS_ERROR, "Wrong input");

	$id = $_REQUEST['id'];
	$token = $_REQUEST['token'];

	$settings = array(
		'method' => "GET",
		'header' => "Content-Type: application/x-www-form-urlencoded".PHP_EOL
	);

	$context = stream_context_create(array('https' => $settings));

	$params = array(
		'input_token' => $token,
		'access_token' => API_FB_TOKEN
	);

	$json = @file_get_contents(CHECK_URL."?".http_build_query($params), false, $context);
	if ($json === false)
		print_status(STATUS_ERROR, "Incorrect answer");

	$result = json_decode($json, true);

	if (!isset($result['data']['user_id']) || !isset($result['data']['app_id']) || !isset($result['data']['is_valid']))
		print_status(STATUS_ERROR, "Bad request");

	$user_id = $result['data']['user_id'];
	$app_id = $result['data']['app_id'];
	$is_valid = $result['data']['is_valid'];

	if ($id != $user_id || $app_id != API_FB_ID || $is_valid == false)
		print_status(STATUS_ERROR, "Bad data");

	$signature = md5($app_id."_".$user_id."_".API_SECRET_FB);

	print_status(STATUS_SUCCESS, $signature);

	function print_status($status, $data)
	{
		if ($status == STATUS_SUCCESS)
		{
			if (isset($_REQUEST['html5']))
				echo json_encode(array("access_token"=>$data));
			else
				echo $data;
			exit;
		}

		ob_start();
		print_r($_REQUEST);
		$date = date("[d.m.Y H:i:s]");

		file_put_contents("logs/auth_fb.log", $date."\n".$status.", ".$data.":\n".ob_get_contents()."\n\n", FILE_APPEND);
		ob_end_clean();

		header("HTTP/1.1 403 Forbidden");
		exit;
	}

?>