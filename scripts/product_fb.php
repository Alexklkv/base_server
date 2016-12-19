<?php

	require_once "scripts/orders_fb.inc.php";

	if (!isset($_REQUEST['params']))
	{
		header("HTTP/1.0 403 Forbidden");
		exit;
	}

	$products = array(
		PRODUCT_CHAMPION_PACK		=> array('title' => array('ru' => "Набор чемпиона", 'en' => "Starter Pack"), 'description' => array('ru' => "С помощью кристаллов вы можете приобрести наборы карт, монеты, игровые бонусы, а так же ускорить свой прогресс и многое другое!", 'en' => "With crystalls you can buy card packs, gold, in-game bonuses, boost game progress and other things!"), 'image' => LEGENDS_IMAGE_BASE."champion_pack.png"),
	);

	$product = $_REQUEST['params'];

	$params = get_info($product);
	if ($params == null)
	{
		header("HTTP/1.0 403 Forbidden");
		exit;
	}

	$params['url'] = FACEBOOK_PRODUCT_URL.$product;

	echo "<!DOCTYPE html>";
	echo "<html>";
	echo "<head prefix=\"og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# product: http://ogp.me/ns/product#\">";
	echo "<meta property=\"og:title\" content=\"".$params['title']."\" />";
	echo "<meta property=\"og:image\" content=\"".$params['image']."\" />";
	echo "<meta property=\"og:description\" content=\"".$params['description']."\" />";
	echo "<meta property=\"og:url\" content=\"".$params['url']."\" />";
	echo "<meta property=\"fb:app_id\" content=\"".API_FB_ID."\" />";

	echo "<meta property=\"og:type\" content=\"og:product\" />";

	if (isset($params['plural_title']))
		echo "<meta property=\"product:plural_title\" content=\"".$params['plural_title']."\" />";

	echo "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">";
	echo "</head>";
	echo "</html>";

	function get_info($product)
	{
		global $products;

		if (preg_match("/^(.+?)(_(en|ru))?\.html$/", $product, $matches) == 0)
			return null;

		$name = $matches[1].".html";
		$language = isset($matches[3]) ? $matches[3] : "en";

		if (isset($products[$name]))
			return array('title' => $products[$name]['title'][$language], 'description' => $products[$name]['description'][$language], 'image' => $products[$name]['image']);

		if (preg_match("/^(.+?)_(\d+)\.html$/", $name, $matches) == 0)
			return null;

		$name = $matches[1];
		$amount = intval($matches[2]);

		if ($name == "souls")
		{
			if ($language == "ru")
				$title = $amount." ".get_word_form($amount, ["кристалл", "кристаллы", "кристаллов"]);
			else
				$title = $amount." ".get_word_form($amount, ["crystalls", "crystalls", "crystalls"]);

			$image = "";
			if ($amount >= 1500)
				$image .= "large";
			else if ($amount >= 500)
				$image .= "big";
			else if ($amount >= 120)
				$image .= "medium";
			else
				$image .= "small";

			if ($language == "ru")
				$description = "С помощью кристаллов вы можете приобрести наборы карт, монеты, игровые бонусы, а так же ускорить свой прогресс и многое другое!";
			else
				$description = "With crystalls you can buy card packs, gold, in-game bonuses, boost game progress and other things!";

			$image = LEGENDS_IMAGE_BASE."souls_".$image.".png";
		}
		else
			return null;

		return array('title' => $title, 'description' => $description, 'image' => $image);
	}

?>