<?php

	require_once "scripts/orders.inc.php";

	$orders = array(
		PRODUCT_SOULS_21	=> array('offer' => OFFER_NONE,			'amount' => 21,		'price' => array('USD' => 2,	'RUB' => 120,	'EUR' => 2),		'unique' => "no"),
		PRODUCT_SOULS_120	=> array('offer' => OFFER_NONE,			'amount' => 120,	'price' => array('USD' => 5,	'RUB' => 300,	'EUR' => 5),		'unique' => "no"),
		PRODUCT_SOULS_500	=> array('offer' => OFFER_NONE,			'amount' => 500,	'price' => array('USD' => 20,	'RUB' => 1200,	'EUR' => 20),		'unique' => "no"),
		PRODUCT_SOULS_1800	=> array('offer' => OFFER_NONE,			'amount' => 1800,	'price' => array('USD' => 50,	'RUB' => 3000,	'EUR' => 50),		'unique' => "no"),
		PRODUCT_CHAMPION_PACK	=> array('offer' => OFFER_CHAPMPION_PACK,	'amount' => 1,		'price' => array('USD' => 2.99,	'RUB' => 179.4,	'EUR' => 2.99),		'unique' => "no"),
	);

	$multiple = array(
		'souls'			=> array('offer' => OFFER_NONE,			'price' => array('USD' => 0.1,	'RUB' => 6,	'EUR' => 0.1),	'unique' => "no")
	);
?>