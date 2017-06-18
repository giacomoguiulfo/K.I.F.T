

// Parse dataa.
function parseMessage(data) {
	return String(data).split("\n");
}

// ...
function showMessage(message) {
	var userMessage = message[0];
	var kevinMessage = message[1];


    // timeout here??

	console.log(userMessage);
	console.log(kevinMessage);
}


// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   client.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/06/15 02:11:03 by jaleman           #+#    #+#             //
//   Updated: 2017/06/15 02:11:04 by jaleman          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

// Module declarations.
var net = require('net');

// ...
var PORT = 8080;
var HOST = '127.0.0.1';
var MSECONDS = 5000;

// ...
var client = new net.Socket();

// ...
client.connect(PORT, HOST, function() {
    console.log('Connected to: ' + HOST + ':' + PORT);
});

// ...
client.on('error', function(e) {
    if (e.code == 'ECONNREFUSED') {
        console.log('Is the server running at port ' + PORT + '?');
        client.setTimeout(MSECONDS, function() {
            client.connect(PORT, HOST, function() {
                console.log('Connected to: ' + HOST + ':' + PORT);
            });
        });
        console.log('Trying again in ' + (MSECONDS / 1000) + ' seconds...');
    }
});

// ...
client.on('data', function(data) {
    var message = parseMessage(data);
    showMessage(message);
    client.write("Send me another one!")
});

// ...
client.on('close', function() {
	client.destroy();
    console.log('Connection closed');
});








// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   record.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/06/15 02:11:03 by jaleman           #+#    #+#             //
//   Updated: 2017/06/15 02:11:04 by jaleman          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

// ...
var fs = require('fs');
var record = require('node-record-lpcm16');

// ...
var filename = "../test.wav";

// ...
function idleMode() {
    stats = fs.statSync(filename).size;
    client.write(stats.toString());
    var readStream = fs.createReadStream(filename);
    readStream.pipe(client);
    //fs.unlinkSync(filename);
}

// ...
function startRecording() {
    var file = fs.createWriteStream(filename, { encoding: 'binary' });



    record.start({
            sampleRate: 16000,
            verbose: true
        })
        .on('close', () => {
            idleMode();
            //listenServer();
        })
        .pipe(file);

}


// start recording again when I receive the json string format shit thingy.
startRecording();
