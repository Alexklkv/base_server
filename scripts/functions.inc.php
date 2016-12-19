<?php

	function check_result(&$result, &$db)
	{
		if (!$result)
			throw new Exception($db->error, $db->errno);
	}

	function get_ip()
	{
		$ip = ip2long($_SERVER['REMOTE_ADDR']);
		if ($ip !== false)
			return $_SERVER['REMOTE_ADDR'];

		$ip = ip2long($_SERVER['HTTP_X_FORWARDED_FOR']);
		if ($ip !== false)
			return $_SERVER['HTTP_X_FORWARDED_FOR'];

		return "";
	}

	function get_word_form($count, $forms, $language = "ru")
	{
		$form = 0;

		switch ($language) {
			case "ru":
				if ($count % 10 == 1 && $count % 100 != 11)
					$form = 0;
				else if ($count % 10 >= 2 && $count % 10 <= 4 && ($count % 100 < 10 || $count % 100 > 20))
					$form = 1;
				else
					$form = 2;
				break;
			case "eng":
				if ($count == 1)
					$form = 0;
				else 
					$form = 1;
				break;
		}

		return $forms[$form];
	}

?>