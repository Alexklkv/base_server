'use strict';

let Mask = require('rg').Mask;

module.exports = new Mask(
	'player_id:I',
	[
		{name : 'net_id',				description : 'L'},
		{name : 'type',					description : 'B'},
		{name : 'moderator',			description : 'B'},
		{name : 'editor',				description : 'B'},
		{name : 'name',					description : 'S'},
		{name : 'sex',					description : 'B'},
		{name : 'photo',				description : 'S'},
		{name : 'online',				description : 'B'},
		{name : 'info',					description : 'bday:I, profile:S, referrer:I, common_place:I, shaman_place:I, common_weekly_place:I, shaman_weekly_place:I, achieve_general_place:I, achieve_base_place:I, achieve_collector_place:I, achieve_shaman_place:I, achieve_epic_place:I'},
		{name : 'rank_place',			description : 'I'},
		{name : 'experience',			description : 'I'},
		{name : 'clothes',				description : '[W]'},
		{name : 'weared',				description : 'acessory_level:B, weared:[clothes_id:W, layer:B]'},
		{name : 'clan',					description : 'I'},
		{name : 'common_value',			description : 'I'},
		{name : 'common_weekly_value',	description : 'I'},
		{name : 'collection_sets',		description : '[type:B, element:B, count:I]'},
		{name : 'collection_exchange',	description : '[B]'},
		{name : 'is_gone',				description : 'B'},
		{name : 'clan_totem',			description : 'I'},
		{name : 'achivements',			description : '[counter:B, value:W]'},
		{name : 'vip',					description : 'left:I, color:B, vip_bonus:B'},
		{name : 'interior',				description : '[B]'},
		{name : 'decorations',			description : '[B]'},
		{name : 'shaman_exp',			description : 'I'},
		{name : 'shaman_info',			description : '[skill:B, free_level:B, paid_level:B]'}
	]
);