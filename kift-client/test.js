var fs = require('fs');

var ps = require('pocketsphinx').ps;

modeldir = "/Volumes/Storage/goinfre/jkalia/homebrew/Cellar/cmu-pocketsphinx/HEAD-9221bf3/share/pocketsphinx/model/"

var config = new ps.Decoder.defaultConfig();
config.setString("-hmm", modeldir + "en-us/en-us");
config.setString("-dict", modeldir + "/en-us/cmudict-en-us.dict");
config.setString("-lm", modeldir + "/en-us/en-us.lm.bin");
var decoder = new ps.Decoder(config);

fs.readFile("goforward.raw", function(err, data) {
	if (err) throw err;
	decoder.startUtt();
	decoder.processRaw(data, false, false);
	decoder.endUtt();
	console.log(decoder.hyp().hypstr)
});
