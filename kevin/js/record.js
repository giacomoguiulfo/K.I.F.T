
var record = require('node-record-lpcm16')
var fs = require('fs')

//	fs.unlinkSync('../test.wav')
function start_recording() {


	var file = fs.createWriteStream('../test.wav', { encoding: 'binary' })
	record.start({
	  sampleRate: 16000,
	  verbose: true
  }).pipe(file);


}

/*
var http = require("http");
var server = http.createServer(function(request, response) {
  //response.writeHead(200, {"Content-Type": "text/html"});
  response.write("30");
  // response.write("<html>");
  // response.write("<head>");
  // response.write("<title>Hello World Page</title>");
  // response.write("</head>");
  // response.write("<body>");
  // response.write("Hello World!");
  // response.write("</body>");
  // response.write("</html>");
  response.end();
});

server.listen(3000, 'localhost');
console.log("Server is listening");
*/
