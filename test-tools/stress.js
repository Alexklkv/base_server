'use strict';

let stress = require('rg').stress;

let settings =
{
	keys : require('./settings/keys.json'),
	server : require('./settings/server.json'),
	packets : require('./settings/packets'),
	minId : 1,
	maxId : 400,
	useAdmin : false,
	packetDuration : 10,
	verbose : true
};

stress(settings);