<?php

	require_once "keys.inc.php";

	define('FACEBOOK_APP_URL',		"https://apps.facebook.com/legend_wars");
	define('FACEBOOK_PRODUCT_URL',		"https://legendspay.itsrealgames.com/legends/products/");
	define('LEGENDS_IMAGE_BASE', 		"http://legends2.itsrealgames.com/release/images/");

	define('API_TYPE_VK',			0);
	define('API_TYPE_MM',			1);
	define('API_TYPE_OK',			4);
	define('API_TYPE_FB',			5);
	define('API_TYPE_AP',			40);
	define('API_TYPE_GL',			41);

	// Offers
	define('OFFER_NONE',			0);

	define('OFFER_SPONSORPAY',		1);
	define('OFFER_FOTOSTRANA',		2);
	define('OFFER_VKONTAKTE',		3);
	define('OFFER_CHAPMPION_PACK',		4);

	define('OFFER_MAX_TYPE', 		5);

	define('OFFER_RENEW_TIME',		"2016-06-01 00:00:00");

	// Products
	define('PRODUCT_SOULS_21',		"souls_21.html");
	define('PRODUCT_SOULS_120',		"souls_120.html");
	define('PRODUCT_SOULS_500',		"souls_500.html");
	define('PRODUCT_SOULS_1800',		"souls_1800.html");
	define('PRODUCT_CHAMPION_PACK',		"champion_pack.html");

	// Memcache
	define('MEMCACHE_HOST',			"localhost");
	define('MEMCACHE_PORT',			11211);
	define('MEMCACHE_PREFIX',		"legends_");

?>