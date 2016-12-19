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
let client = new rg.Client(packets, server, 1);
console.log(1);


client.connect().sequence(
	() => client.wait(SERVER.HELLO),

	() => client.send(packets.client.LOGIN, auth.generate(auth.randomType(settings.useAdmin), new rg.Long(12349876), {version: 1})),
	Future.pause(1000),

	() => client.disconnect()

).catch((error) => console.error(error.stack));

client.on('packet', (packet, data) =>
{
	console.log('server: ' + packet.name + '(' + packet.id + ')', data);
})

// LOGIN 33000000000000000400d49df1040000000000012000323661323639636462653434666138386461623339623332656263346330306600
