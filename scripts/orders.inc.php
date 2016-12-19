<?php

	define('ORDER_SUCCESS', 0);
	define('ORDER_ALREADY_PURCHASED', 1);
	define('ORDER_DATABASE_ERROR', 2);

	require_once "scripts/defines.inc.php";
	require_once "scripts/functions.inc.php";

	function buy(&$sql, &$order)
	{
		$result = $sql->query("SELECT `id`, `transaction_id` FROM `orders` WHERE `transaction_id` = '{$order['transaction_id']}' AND `provider_id` = {$order['provider_id']} AND `service_id` = {$order['service_id']} LIMIT 1");
		if ($row = $result->fetch_assoc())
		{
			$order['id'] = $row['id'];
			return ORDER_SUCCESS;
		}

		if ($order['unique'] != "no")
		{
			if ($order['unique'] == "renew")
				$result = $sql->query("SELECT `id`, `transaction_id` FROM `orders` WHERE `net_id` = '{$order['net_id']}' AND `type` = {$order['type']} AND `offer` = {$order['offer']} AND time > '".OFFER_BOX_RENEW."' LIMIT 1");
			else
				$result = $sql->query("SELECT `id`, `transaction_id` FROM `orders` WHERE `net_id` = '{$order['net_id']}' AND `type` = {$order['type']} AND `offer` = {$order['offer']} LIMIT 1");

			if ($row = $result->fetch_assoc())
			{
				if ($order['transaction_id'] != $row['transaction_id'])
					return ORDER_ALREADY_PURCHASED;

				$order['id'] = $row['id'];
				return ORDER_SUCCESS;
			}
		}

		$order['ip'] = get_ip();

		$sql->query("INSERT INTO `orders` SET `transaction_id` = '{$order['transaction_id']}', `provider_id` = {$order['provider_id']}, `service_id` = {$order['service_id']}, `net_id` = '{$order['net_id']}', `type` = {$order['type']}, `offer` = {$order['offer']}, `amount` = {$order['amount']}, `revenue` = {$order['revenue']}, `ip` = '{$order['ip']}'");
		if ($sql->affected_rows != 1)
			return ORDER_DATABASE_ERROR;

		$order['id'] = $sql->insert_id;
		return ORDER_SUCCESS;
	}

?>