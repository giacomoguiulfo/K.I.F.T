# K.I.F.T
VUI (Voice User Interface) based on CMUSphinx written in C and JavaScript using Electron.

<img width="590" alt="kift_view" src="https://user-images.githubusercontent.com/14208431/30776959-f32e6e90-a064-11e7-8cea-deb5ae96b686.png">

## Getting Started
```sh
# Clone Repo
git clone https://github.com/giacomoguiulfo/kift.git
cd kift

# Build Dependencies
sh build.sh

# Run Server
./kift

# Launch App
electron kift-client/main.js
```
## Built With

* [Electron](https://github.com/electron/electron.git) - Front End
* [CMU SPHINX](https://cmusphinx.github.io/wiki/download/) - Recognizer Library
* [node-record-lpcm16](https://www.npmjs.com/package/node-record-lpcm16) - Recording Library

## Authors
* [José Ramón](https://github.com/jraleman)
* [Jibran Kalia](https://github.com/JibranKalia)
* [Giacomo Guiulfo](https://github.com/giacomoguiulfo)
* [Abraham Nieto](https://github.com/hardtargetmullet)
