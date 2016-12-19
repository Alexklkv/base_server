'use strict';

let rg = require('rg');
let Future = rg.Future;

let packets = require('./settings/packets');
let playerMask = require('./settings/mask-player');
let keys = require('./settings/keys.json');
let server = require('./settings/server.json');

let CLIENT = packets.client;
let SERVER = packets.server;

server.reconnect = false;

let auth = new rg.Auth(keys);
let client = new rg.Client(packets, server);
let loginData = auth.generate(rg.Auth.VK, new rg.Long(15225867), {referrer : 0, tag: 0});

function addCoins(innerId, coins)
{
	// let baseInfo;
	// let adminInfo;
	// let newCoins = 0;
	// let name;
	// let editedData;

	console.log(`start for player ${innerId}`);

	return client.connect().sequence(
		() => client.send(CLIENT.LOGIN, loginData),
		() => client.wait(SERVER.LOGIN),
		() => client.send(CLIENT.REQUEST, {ids : [innerId], mask : playerMask.full}),
		() => client.wait(SERVER.INFO).then((data) =>
		{
			data = data[1];
			let struct = playerMask.read(data.mask, data.data);
			
			let baseInfo = struct[0];

			let name = `${innerId}:${baseInfo.name}`;

			console.log(baseInfo);
		}),
		() => client.send(CLIENT.ADMIN_REQUEST, {inner_id : innerId}),
		// () => client.wait(SERVER.ADMIN_INFO).then((data) =>
		// {
		// 	adminInfo = data[1];
		// 	console.log(`admin info for ${name}`);

		// 	newCoins = coins + adminInfo.coins;
		// 	console.log(`new coins for ${name}: current(${adminInfo.coins}) + new(${coins}) = ${newCoins}`);

		// 	editedData =
		// 	{
		// 		player_id : innerId,
		// 		moderator : baseInfo.moderator,
		// 		editor : baseInfo.editor,
		// 		name : baseInfo.name,
		// 		photo : baseInfo.photo,
		// 		profile : baseInfo.profile,
		// 		energy : adminInfo.energy,
		// 		mana : adminInfo.mana,
		// 		coins : newCoins,
		// 		nuts : adminInfo.nuts,
		// 		clothes : baseInfo.clothes,
		// 		weared : baseInfo.weared,
		// 		awards : baseInfo.awards,
		// 		flags : adminInfo.flags,
		// 		experience : baseInfo.experience,
		// 		ban_update : 0,
		// 		ban_reason : 0,
		// 		ban_repeated : 0,
		// 		double_bonus : adminInfo.bonus_left
		// 	};

		// }),
		// () => client.send(CLIENT.ADMIN_EDIT_PLAYER, editedData).then(() => console.log(`${name} updated`)),

		() => client.disconnect()

	).catch((error) =>
	{
			console.error(error);
			console.error(error.stack);
			client.disconnect();
	});
}

addCoins(16, 0);