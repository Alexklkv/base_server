<?php

	require_once "queries.inc.php";
	require_once "defines.inc.php";

	const RATING_SCRIPT_PREFIX = 'RatingsUpdater';
	const LOG_FILE = '../logs/ratings_update.log';

	$ratings = ['Common', 'Battle', 'Respect', 'Elo', 'EloAsync', 'LocationsFarm'];

	$db = new mysqli(DATABASE_HOST, DATABASE_USER, DATABASE_PASSWORD, DATABASE_NAME);
	if ($db->connect_errno)
	{
		file_put_contents(LOG_FILE, "Connection error: " . $db->connect_errno, FILE_APPEND);
		exit();
	}

	foreach ($ratings as $rating) 
	{
		try
		{
			$class = $rating . RATING_SCRIPT_PREFIX;
			require_once $class . '.inc.php';
			$updater = new $class($db);
			$updater->update();
		}
		catch (Exception $e)
		{
			echo $e;
			file_put_contents(LOG_FILE, $e, FILE_APPEND);
		}
	}

?>