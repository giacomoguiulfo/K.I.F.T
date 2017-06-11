# KIFT
The future of voice commands and super cool robot assistants

## GETTING STARTED
```
git clone --recursive https://github.com/giacomoguiulfo/42-kift.git
make
./kift -inmic yes
```

## DEPENDENCIES
```
brew tap watsonbox/cmu-sphinx
brew install --HEAD watsonbox/cmu-sphinx/cmu-sphinxbase
brew install --HEAD watsonbox/cmu-sphinx/cmu-pocketsphinx
brew install --HEAD watsonbox/cmu-sphinx/cmu-sphinxtrain (only needed for training)
brew install swig sdl
```
