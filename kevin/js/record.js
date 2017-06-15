// record voice

var record = require('node-record-lpcm16')
var fs = require('fs')

//	fs.unlinkSync('../test.wav')
function start_recording() {


	var file = fs.createWriteStream('../test.wav', { encoding: 'binary' })
	record.start({
	  sampleRate: 16000,
	  verbose: true
  }).pipe(file);


  setTimeout(function () {

		stats = fs.statSync('../test.wav').size;
		console.log(stats);
		client.write("#" + stats.toString());
		console.log("#" + stats.toString());
		var readStream = fs.createReadStream('../test.wav');
		readStream.pipe(client);
  }, 7000)

}


// client code

var net = require('net');

var client = new net.Socket();
client.connect(8200, '127.0.0.1', function() {
	console.log('Connected');


	//client.write('Hello, server! Love, Client.');
//	console.write('Hello, server! Love, Client.');
});



client.on('data', function(data) {
	console.log('Received: ' + data);
	client.destroy(); // kill client after server's response
});

client.on('close', function() {
	console.log('Connection closed');
});
