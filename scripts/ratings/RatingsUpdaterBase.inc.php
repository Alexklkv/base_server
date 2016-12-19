<?php

	require_once 'functions.inc.php';
	require_once 'RatingsUpdater.inc.php';

	abstract class RatingsUpdaterBase implements RatingsUpdater
	{
		const TYPE_BOT = 254;
		const TYPE_ADMIN = 255;
		const NONRATABLE_TYPES = array(RatingsUpdaterBase::TYPE_BOT, RatingsUpdaterBase::TYPE_ADMIN);

		protected $db;
		private $ratings_table;
		private $postfix;

		protected abstract function ratings_query();
		protected abstract function clear_ratings_query();

		protected function __construct(&$db, $ratings_table, $postfix)
		{
			$this->db = &$db;
			$this->ratings_table = $ratings_table;
			$this->postfix = $postfix;
		}

		public function update()
		{
			$this->prepare_tables();

			$query = $this->ratings_query();
			$result = $this->db->query($query);
			check_result($result, $this->db);

			//$this->commit_tables();
		}

		protected function prepare_tables()
		{
			$this->prepare_table($this->ratings_table);
		}

		protected function commit_tables()
		{
			$this->commit_table($this->ratings_table);
		}

		protected function prepare_table($table)
		{
			$query = $this->clear_ratings_query();
			$result = $this->db->query($query);

			//$postfix = $this->postfix;
			//$result = $this->db->query("CREATE TABLE {$table}{$postfix} LIKE {$table}");

			check_result($result, $this->db);
		}

		protected function commit_table($table)
		{
			$postfix = $this->postfix;

			$result = $this->db->query("RENAME TABLE {$table} TO {$table}_bak, {$table}{$postfix} TO {$table}, {$table}_bak TO {$table}{$postfix}");
			check_result($result, $this->db);

			$result = $this->db->query("DROP TABLE {$table}{$postfix}");
			check_result($result, $this->db);
		}

		protected function excluded_types()
		{
			return "(".join(",", RatingsUpdaterBase::NONRATABLE_TYPES).")";
		}
	}

?>