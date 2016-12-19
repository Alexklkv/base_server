<?php

	require_once 'RatingsUpdaterBase.inc.php';

	class LocationsFarmRatingsUpdater extends RatingsUpdaterBase
	{
		const RATINGS_TABLE = 'ratings_locations_farm';
		const TMP_PREFIX = '_temp';

		const PVP_BATTLE = 255;

		function __construct(&$db)
		{
			parent::__construct($db, LocationsFarmRatingsUpdater::RATINGS_TABLE, LocationsFarmRatingsUpdater::TMP_PREFIX);
		}

		protected function clear_ratings_query()
		{
			$target_table = LocationsFarmRatingsUpdater::RATINGS_TABLE;
			return "TRUNCATE TABLE ".$target_table;
		}

		protected function ratings_query()
		{
			$target_table = LocationsFarmRatingsUpdater::RATINGS_TABLE;
			$pvp_battle_id = LocationsFarmRatingsUpdater::PVP_BATTLE;

			return "INSERT INTO {$target_table}
				SELECT location_id, player_id, MAX(winnings) AS `value`
				FROM statistics
				WHERE location_id != {$pvp_battle_id}
				GROUP BY location_id;";
		}
	}

?>