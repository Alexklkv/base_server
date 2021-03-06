<?php

	require_once 'RatingsUpdaterBase.inc.php';

	class EloAsyncRatingsUpdater extends RatingsUpdaterBase
	{
		const RATINGS_TABLE = 'ratings_async_elo';
		const TMP_PREFIX = '_temp';

		function __construct(&$db)
		{
			parent::__construct($db, EloAsyncRatingsUpdater::RATINGS_TABLE, EloAsyncRatingsUpdater::TMP_PREFIX);
		}

		protected function clear_ratings_query()
		{
			$target_table = EloAsyncRatingsUpdater::RATINGS_TABLE;
			return "DELETE FROM ".$target_table." WHERE week = WEEKOFYEAR(NOW())";
		}

		protected function ratings_query()
		{
			$target_table = EloAsyncRatingsUpdater::RATINGS_TABLE;
			$excluded = parent::excluded_types();

			return "INSERT INTO {$target_table} (place, player_id, category, week, value)
				SELECT IF(@category <> category, @place := 1, @place := @place + 1) AS place, player_id, IF(@category <> category, @category := category, @category) category, WEEKOFYEAR(NOW()) AS week, `value`
				FROM (
					SELECT inner_id AS player_id, elo_async_rating AS value, elo_async_category AS category, experience 
					FROM players LEFT JOIN statistics ON inner_id = player_id AND location_id = 253 
					WHERE `type` NOT IN {$excluded} AND elo_async_rating > 0
					ORDER BY category ASC, value DESC, winnings - losses DESC, experience ASC 
				) ratings, (SELECT @place := 0, @category := 0) places;";
		}
	}

?>