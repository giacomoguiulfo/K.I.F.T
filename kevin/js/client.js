// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   client.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/06/14 00:13:24 by jaleman           #+#    #+#             //
//   Updated: 2017/06/14 00:13:25 by jaleman          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

var net = require('net');
var client = new net.Socket();
var ip = "127.0.0.1";
var port = 8000;

client.connect(port, ip, function() {
	console.log('Connected');
	//client.write('Hello, server! Love, Client.');
	//console.write('Hello, server! Love, Client.');
});

client.on('data', function(data) {
	console.log('Received: ' + data);
	client.destroy(); // kill client after server's response
});

client.on('close', function() {
	console.log('Connection closed');
});
