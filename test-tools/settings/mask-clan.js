'use strict';

let Mask = require('rg').Mask;

module.exports = new Mask(
	'clan_id:I',
	[
		{name : 'info',				description : 'name:S, photo:S, emblem:S'},
		{name : 'news',				description : 'S'},
		{name : 'leader',			description : 'I'},
		{name : 'size',				description : 'I'},
		{name : 'state',			description : 'B'},
		{name : 'level',			description : 'level:B, experience:I, daily_experience:I'},
		{name : 'rank_range',		description : 'I'},
		{name : 'places',			description : 'I'},
		{name : 'rating',			description : 'place:I, weekly_place:I'},
		{name : 'ban',				description : 'I'},
		{name : 'totems',			description : '[slot:B, left:I, totem:B], booster_left:I'},
		{name : 'totems_levels',	description : '[totem:B, level:B, experience:I, max_experience:I]'},
		{name : 'totems_bonuses',	description : '[bonus:B, value:B]'},
		{name : 'statistics',		description : '[map_id:I, clan:I, player:I]'},
		{name : 'blacklist',		description : '[I]'},
		{name : 'level_limiter',	description : 'B'},
		{name : 'admin_balance',	description : 'coins:I, nuts:I'}
	]
);