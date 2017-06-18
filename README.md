# KIFT
The future of voice commands and super cool robot assistants

## GETTING STARTED
```
git clone --recursive https://github.com/giacomoguiulfo/42-kift.git
make
./kift 8080
```

## DEPENDENCIES
```
brew install sox
brew install node
brew tap watsonbox/cmu-sphinx
brew install --HEAD watsonbox/cmu-sphinx/cmu-sphinxbase
brew install --HEAD watsonbox/cmu-sphinx/cmu-pocketsphinx
brew install --HEAD watsonbox/cmu-sphinx/cmu-sphinxtrain (only needed for training)
npm install electron
npm install node-record-lpcm16
```

## TODO

- Edit Makefile
- Clean directory
- Man page
- More commands
- Fix JS
- Verify norm and check everything is working
