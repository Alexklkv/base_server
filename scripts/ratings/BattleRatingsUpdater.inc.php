<?php

	require_once 'RatingsUpdaterBase.inc.php';

	class BattleRatingsUpdater extends RatingsUpdaterBase
	{
		const RATINGS_TABLE = 'ratings_battle';
		const TMP_PREFIX = '_temp';

		function __construct(&$db)
		{
			parent::__construct($db, BattleRatingsUpdater::RATINGS_TABLE, BattleRatingsUpdater::TMP_PREFIX);
		}

		protected function clear_ratings_query()
		{
			$target_table = BattleRatingsUpdater::RATINGS_TABLE;
			return "TRUNCATE TABLE ".$target_table;
		}

		protected function ratings_query()
		{
			$target_table = BattleRatingsUpdater::RATINGS_TABLE;
			$excluded = parent::excluded_types();

			return "INSERT INTO {$target_table}
				SELECT @place := @place + 1 AS place, player_id, value
				FROM (
					SELECT player_id, (SUM(winnings) - SUM(losses)) AS `value`
					FROM statistics
					WHERE player_id NOT IN (
						SELECT inner_id
						FROM players
						WHERE type IN {$excluded}
					)
					GROUP BY player_id
					HAVING `value` > 0
					ORDER BY `value` DESC
				) ratings, (SELECT @place := 0) places;";
		}
	}

?>