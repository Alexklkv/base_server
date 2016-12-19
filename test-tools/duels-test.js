'use strict';

let duels_test = require('rg').duels_test;

let settings =
{
	keys : require('./settings/keys.json'),
	server : require('./settings/server.json'),
	packets : require('./settings/packets'),
	minId : 1,
	maxId : 1,
	useAdmin : false,
	packetDuration : 1,
	packetsCount : 1000,
	verbose : true
};

duels_test(settings);
console.log(`Test finished`);