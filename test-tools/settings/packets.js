'use strict';

let Packet = require('rg').Packet;

let server =
{
	ADMIN_INFO : new Packet(1, 'ADMIN_INFO', 'status:B', 'inner_id:I, name:S, towner_name:S, sex:B, gold:I, souls:I, respect:I, experience:I, flags:[value:W], main_characterictic:B, education_state:W'),
	HELLO : new Packet(2, 'HELLO'),
	LOGIN : new Packet(3, 'LOGIN', 'status:B', 'inner_id:I, client_id:I, tower:S, flags:[value:W], statistics:[], totems:[], items:[], equipment:[], decoration:[], slots:B, unread_messages_senders:[], time_to_next_midnight:I, vip_left:I, friends:[]'),
	INFO : new Packet(4, 'INFO', 'data:A, mask:I'),
	INFO_NET : new Packet(5, 'INFO_NET', 'data:A, mask:I'),
	ONLINE : new Packet(6, 'ONLINE', 'online:I'),
	BALANCE : new Packet(7, 'BALANCE', 'reason:B, coins:I, acorns:I'),
	EXPERIENCE : new Packet(8, 'EXPERIENCE', 'reason:B, exp:I'),
	RESPECT : new Packet(9, 'RESPECT', 'reason:B, value:I'),
	BUY : new Packet(10, 'BUY', 'status:B', 'good_id:I, target_id:I, gold_price:I, souls_price:I, data:I, data_group:A'),
	REWARD : new Packet(11, 'REWARD', 'category:B, data:I, game_items:[category:B, item_type:W, count:I]'),
	CARDS_REQUEST : new Packet(12, 'CARDS_REQUEST', 'reason:B, cards:[active_group:[id:W, type:W, sharp_item:B, sharp_times:B, level:B, health:W, damage:W], upgrading_group:[id:W, slot:B, tme_left:I], inactive_group:[id:W, type:W, sharp_item:B, sharp_times:B, level:B, health:W, damage:W]]'),
	CARD_SHARP : new Packet(13, 'CARD_SHARP', 'is_sharped:B'),
	QUESTS_INTO : new Packet(14, 'QUESTS_INTO', 'quests:[id:B, progress:I, reward_level_group:B, reward_type:B, data:I], next_update:I, replaced:B'),
	QUEST_PROGRESS : new Packet(15, 'QUEST_PROGRESS', 'quest:B, current_progress:I'),
	QUEST_FINISH : new Packet(16, 'QUEST_FINISH', 'status:B, quest_id:B', 'reward_level:B, reward_type:B, reward_data:I'),
	MAIN_QUEST_PROGRESS : new Packet(17, 'MAIN_QUEST_PROGRESS', 'quest_id:B, locations:[location_id:B], amount:B'),
	MAIN_QUEST_COMPLETED : new Packet(18, 'MAIN_QUEST_COMPLETED', 'group_rewards:A'),
	RATING_PAGE : new Packet(19, 'RATING_PAGE', 'category:B, type:B, page_num:I, page:[player_id:I]'),
	RATINGS_SIZES : new Packet(20, 'RATINGS_SIZES', 'group:A'),
	DAILY_BONUS : new Packet(21, 'DAILY_BONUS', 'current_day:B, bonus:B, data:W'),
	RATING_PAGE : new Packet(22, 'RATING_PAGE', 'page_num:I, page:[player_id:I]'),
	TROPHY_BONUS : new Packet(23, 'TROPHY_BONUS', 'trophy:B, amount:I'),
	ARENA : new Packet(24, 'ARENA', 'status:B', 'first_player_id:I'),
	ARENA_ACTIONS : new Packet(25, 'ARENA_ACTIONS', 'actions:[category:B, action_type:B, sources:[summoner_id:I, card_id:W], data:L, targets:[summoner_id:I, card_id:W, data:L]]'),
	ARENA_NEXT_ROUND : new Packet(26, 'ARENA_NEXT_ROUND'),
	ARENA_TURN_FINISHED : new Packet(27, 'ARENA_TURN_FINISHED'),
	CARD_CLICK : new Packet(28, 'CARD_CLICK', 'player_id:I, card_id:W'),
	CHAT : new Packet(29, 'CHAT', 'message:S'),
	BONUSES : new Packet(30, 'BONUSES', 'data:A'),
	BONUS_COLLECT : new Packet(31, 'BONUS_COLLECT', 'bonus_id:B', 'card_id:W, amount:B'),
	CARD_DATA : new Packet(32, 'CARD_DATA', 'id:W, type:W, sharp_item:B, sharp_times:B, level:B, health:W, damage:W'),
	RESULT : new Packet(33, 'RESULT', 'is_winner:B, experience:W, gold:W, respect:W, souls:W, items:A, cards:A'),
	MESSAGES : new Packet(34, 'MESSAGES', 'id:I, messages:A'),
	GIFTS_STORAGE : new Packet(35, 'GIFTS_STORAGE', 'gifts:[id:I, type:B, sender_id:I, duration:I], limit:B', 'excluded_players:[id:I]'),
	GIFTS_ACCEPT : new Packet(36, 'GIFTS_ACCEPT', 'status:B, gift_id:I', 'gift_type:B, bonus_id:W'),
	SUPPORTS_STORAGE : new Packet(37, 'SUPPORTS_STORAGE', 'limit_requests:B, supports:[type:B, id:W, duration:I, requested:[I], accepted:[I]], requests:[type:B, id:W, requester_id:I, duration:I], friends:[friend_id:I]'),
	SUPPORTS_REQUEST : new Packet(38, 'SUPPORTS_REQUEST', 'status:B', 'assistant_id:I, type:B, id:W'),
	SUPPORTS_REQUESTS : new Packet(39, 'SUPPORTS_REQUESTS', 'requester_id:I, type:B, id:W, duration:I'),
	SUPPORTS_SUPPORT : new Packet(40, 'SUPPORTS_SUPPORT', 'assistant_id:I, type:B, id:W, duration:I'),
	FLAG_STATE : new Packet(41, 'FLAG_STATE', 'flag_type:B, flag:W'),
	SACRIFICE : new Packet(42, 'SACRIFICE', 'status:B'),
	PVP_INVITE : new Packet(43, 'PVP_INVITE', 'player_id:I'),
	ENERGY_INFO : new Packet(44, 'ENERGY_INFO', 'energy:F')
};

let client =
{
	ADMIN_REQUEST : new Packet(1, 'ADMIN_REQUEST', 'inner_id:I'),
	ADMIN_EDIT : new Packet(2, 'ADMIN_EDIT', 'inner_id:I, name:S, tower:S, sex:B, gold:I, souls:I, respect:I, experience:I, flags:[W], main_characteristics:B, unallocated_stats_points:B, education_state:W, boost_totems_revenue:B, totems_reset:B, vip_need_change:B, vip_left:I, boosters:[booter_type:B, left:I]'),
	HELLO : new Packet(3, 'HELLO'),
	LOGIN : new Packet(4, 'LOGIN', 'net_id:L, type:B, auth_key:S, version:W', 'session_key:S, referrer:I, tag:I'),
	REQUEST : new Packet(5, 'REQUEST', 'player_id:[I], mask:I'),
	REQUEST_NET : new Packet(6, 'REQUEST_NET', 'net_id:[L], type:B, mask:I'),
	INFO : new Packet(7, 'INFO', 'name:S, sex:B, bday:I, photo:S, profile:S, tower_name:S'),
	REFILL : new Packet(8, 'REFILL'),
	BUY : new Packet(9, 'BUY', 'good_id:I, target_id:I, gold:I, souls:I, data:I, data:[I]'),
	REFERRER : new Packet(10, 'REFERRER', 'referrer_id:L'),
	CARDS_REQUEST : new Packet(11, 'CARDS_REQUEST'),
	ACCEPT_DECK : new Packet(12, 'ACCEPT_DECK', 'card_id:[W]'),
	ACCEPT_SPELLS : new Packet(13, 'ACCEPT_SPELLS', 'spell_id:[W]'),
	SET_MAIN_CHARACTERISTIC : new Packet(14, 'SET_MAIN_CHARACTERISTIC', 'stat_id:B'),
	WEAR : new Packet(15, 'WEAR', 'pauldron:B, body:B, gloves:B, legs:B, shoes:B, helmet:B, weapon:B, shield:B'),
	FACE : new Packet(16, 'FACE', 'hair:B, eyes:B, node:B, mouth:B'),
	DECORATION : new Packet(17, 'DECORATION', 'throne:B, wallpaper:B'),
	FLAG_SET : new Packet(18, 'FLAG_SET', 'flag_id:B, value:W'),
	TOTEM_REVENUE : new Packet(19, 'TOTEM_REVENUE', 'type:B'),
	SHARPENING : new Packet(20, 'SHARPENING', 'card_id:W, item_id:B'),
	RATING_PAGE : new Packet(21, 'RATING_PAGE', 'rating_category:B, rating_type:B, page:I'),
	RATINGS_SIZES : new Packet(22, 'RATINGS_SIZES'),
	FRIENDS_ADD : new Packet(23, 'FRIENDS_ADD', 'friends_ids:[I]'),
	FRIENDS_REMOVE : new Packet(24, 'FRIENDS_REMOVE', 'friends_ids:[I]'),
	ARENA_PLAY_BOT : new Packet(25, 'ARENA_PLAY_BOT', 'location_id:W'),
	ARENA_PLAY : new Packet(26, 'ARENA_PLAY', '', 'attacker_id:I'),
	ARENA_LOADED : new Packet(27, 'ARENA_LOADED'),
	ARENA_LEAVE : new Packet(28, 'ARENA_LEAVE'),
	ROOM_CARD_ADD : new Packet(29, 'ROOM_CARD_ADD', 'card_id:W, slot:B'),
	ROOM_CARD_MOVE : new Packet(30, 'ROOM_CARD_MOVE', 'card_id:W, slot_to:B'),
	ROOM_CARD_ATTACK : new Packet(31, 'ROOM_CARD_ATTACK', 'attacker_id:W, target_id:W'),
	ROOM_END_TURN : new Packet(32, 'ROOM_END_TURN'),
	ROOM_TURN_FINISHED : new Packet(33, 'ROOM_TURN_FINISHED'),
	ROOM_SPELL : new Packet(34, 'ROOM_SPELL', 'spell_id:W, player_id:I', 'card_id:W'),
	ROOM_NEXT_ACTION : new Packet(35, 'ROOM_NEXT_ACTION'),
	ROOM_BONUS : new Packet(36, 'ROOM_BONUS', 'gold_id:B'),
	ROOM_CARD_CLICK : new Packet(37, 'ROOM_CARD_CLICK', 'player_id:I, card_id:W'),
	ROOM_CHAT : new Packet(38, 'ROOM_CHAT', 'message:S'),
	ROOM_NEW_CARD_DATA : new Packet(39, 'ROOM_NEW_CARD_DATA', 'summoner_id:I, card_id:W'),
	MESSAGES_NEW : new Packet(40, 'MESSAGES_NEW', 'recipient_id:I, text:S'),
	MESSAGES_REQUEST : new Packet(41, 'MESSAGES_REQUEST', 'interlocutor_id:I'),
	FRIEND_VISITED : new Packet(42, 'FRIEND_VISITED', 'visited_id:I'),
	EDUCATION_TRY_COMPLETE : new Packet(43, 'EDUCATION_TRY_COMPLETE', 'education_state_id:B'),
	GIFT_SEND : new Packet(44, 'GIFT_SEND', '[target_id:I, gift:B]'),
	GIFT_ACCEPT : new Packet(45, 'GIFT_ACCEPT', 'gift_id:I'),
	CHECK_CARD_PARAMS : new Packet(46, 'CHECK_CARD_PARAMS', 'params:[id:W, baseHealth:W, baseDamage:W, addlHealth:W, addlDamage:W]'),
	CARD_SACRIFICE : new Packet(47, 'CARD_SACRIFICE', 'card_id:W, is_sacrifice:B, slot:B, sacrifice_type:B, victims:[W]'),
	SUPPORTS_REQUEST : new Packet(48, 'SUPPORTS_REQUEST', 'assistant_id:I, type:B, object_id:W'),
	SUPPORTS_ACCEPT : new Packet(49, 'SUPPORTS_ACCEPT', 'requester_id:I, type:B, object_id:W'),
	QUESTS_CANCEL : new Packet(50, 'QUESTS_CANCEL', 'quest_id:B'),
	QUESTS_REQUEST : new Packet(51, 'QUESTS_REQUEST'),
	QUESTS_FINISH : new Packet(52, 'QUESTS_FINISH', 'quest_id:B'),
	DEBUG_CLEAR : new Packet(53, 'DEBUG_CLEAR'),
	PVP_INVITE_REFUSE : new Packet(54, 'PVP_INVITE_REFUSE', 'attacker_id:I'),
	ENERGY_REQUEST : new Packet(55, 'ENERGY_REQUEST'),
	ENERGY_USE_BOOSTER : new Packet(56, 'ENERGY_USE_BOOSTER', 'type:B')
};


function createIndex(object)
{
	let array = [];

	for (let key in object)
	{
		if (!object.hasOwnProperty(key))
			continue;

		array[object[key].id] = object[key];
	}

	return array;
}


module.exports =
{
	server : server,
	client : client,
	indexServer : createIndex(server)
};