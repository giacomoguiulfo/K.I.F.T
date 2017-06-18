// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   record.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/06/14 00:13:40 by jaleman           #+#    #+#             //
//   Updated: 2017/06/14 00:13:41 by jaleman          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

/*
        ##
        ##
        ##       ##
        ##     ##
        ##    ##
        ##  ##
        ## #
        ###        ###############
        ###       ##             ##
        ## ##    ##            ##
        ##  ##   ##          ##
        ##    ## ##       ##~
        ##     ####    ##
        ##      ######
                 ##
                 ##
                  ##
                   ###############
*/

// Declarations
var fs = require('fs');
var record = require('node-record-lpcm16');
var filename = "../test.wav";

// ...
function idleMode() {
	stats = fs.statSync(filename).size;
	//console.log(stats.toString());
	client.write(stats.toString());
	var readStream = fs.createReadStream(filename);
	readStream.pipe(client);
	//fs.unlinkSync(filename);
}

// ...
function startRecording() {
	var file = fs.createWriteStream(filename, { encoding: 'binary' })
	record.start({
	  sampleRate: 16000,
	  verbose: true
	})
	.on('close', () => {
	  //console.log('finished recording audio')
	  idleMode();
	  //startRecording();
	  })
	.pipe(file);
}


// start recording again when I receive the json string format shit thingy.
startRecording();
