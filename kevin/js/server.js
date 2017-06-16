// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   server.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/06/15 02:11:03 by jaleman           #+#    #+#             //
//   Updated: 2017/06/15 02:11:04 by jaleman          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

var net = require('net');
var ip = "127.0.0.1";
var port = 8080;


//////////////////////////////////////////////////////


var client = new net.Socket();

client.connect(port, ip, function() {
	console.log('Connected');
	//client.write('Hello, server! Love, Client.');
	//console.write('Hello, server! Love, Client.');
});

client.on('data', function(data) {
	console.log('Received: ' + data);
	//client.destroy(); // kill client after server's response
});

client.on('close', function() {
	console.log('Connection closed');
});



///////////////////////////////////////////////////

/*
io.set('log level', 0);


var io = require('socket.io');

io.sockets.on('connection', function (socket) {
  socket.emit('message', 'connected');
  socket.on('message', function (data) {
    console.log(data);
    var address = srv.address();
    var client = dgram.createSocket("udp4");
    var message = new Buffer(data);
    client.send(message, 0, message.length, address.port, address.address, function(err, bytes) {
     // client.close();
    });
  });
});
*/

/*
var server = net.createServer(function(socket) {
	//socket.write('Echo server\r\n');
	socket.pipe(socket);
});

server.listen(ip, '127.0.0.1');
*/
