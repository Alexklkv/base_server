<?php

	require_once 'RatingsUpdaterBase.inc.php';

	class RespectRatingsUpdater extends RatingsUpdaterBase
	{
		const RATINGS_TABLE = 'ratings_respect';
		const TMP_PREFIX = '_temp';

		function __construct(&$db)
		{
			parent::__construct($db, RespectRatingsUpdater::RATINGS_TABLE, RespectRatingsUpdater::TMP_PREFIX);
		}

		protected function clear_ratings_query()
		{
			$target_table = RespectRatingsUpdater::RATINGS_TABLE;
			return "TRUNCATE TABLE ".$target_table;
		}

		protected function ratings_query()
		{
			$target_table = RespectRatingsUpdater::RATINGS_TABLE;
			$excluded = parent::excluded_types();

			return "INSERT INTO {$target_table}
				SELECT @place:=@place + 1 AS place, player_id, `value`
				FROM (
					SELECT inner_id AS player_id, respect AS `value`
					FROM players
					WHERE `type` NOT IN {$excluded}
					HAVING `value` > 0
					ORDER BY `value` DESC
				) respect_ratings, (SELECT @place := 0) places;";
		}
	}

?>