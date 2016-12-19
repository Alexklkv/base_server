<?php

	require_once 'RatingsUpdaterBase.inc.php';

	class CommonRatingsUpdater extends RatingsUpdaterBase
	{
		const RATINGS_TABLE = 'ratings_common';
		const TMP_PREFIX = '_temp';

		function __construct(&$db)
		{
			parent::__construct($db, CommonRatingsUpdater::RATINGS_TABLE, CommonRatingsUpdater::TMP_PREFIX);
		}

		protected function clear_ratings_query()
		{
			$target_table = CommonRatingsUpdater::RATINGS_TABLE;
			return "TRUNCATE TABLE ".$target_table;
		}

		protected function ratings_query()
		{
			$target_table = CommonRatingsUpdater::RATINGS_TABLE;
			$excluded = parent::excluded_types();

			return "INSERT INTO {$target_table}
				SELECT @place:=@place + 1 AS place, player_id, `value`
				FROM (
					SELECT inner_id AS player_id, inner_id AS `value`
					FROM players
					WHERE type NOT IN {$excluded}
					HAVING `value` > 0
					ORDER BY `value` DESC
				) ratings, (SELECT @place := 0) places;";
		}
	}

?>