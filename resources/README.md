# Ideas

| Usage         | Code                                                                                                                               |
|---------------|------------------------------------------------------------------------------------------------------------------------------------|
| Invert colors | `osascript -e "tell application \"System Events\"" -e "key code 28 using {control down, option down, command down}" -e "end tell"` |
| Dim screen    | `osascript -e "tell application \"System Events\"" -e "repeat 16 times" -e "key code 145" -e "end repeat" -e "end tell"`           |
| Undim screen  | `osascript -e "tell application \"System Events\"" -e "repeat 16 times" -e "key code 144" -e "end repeat" -e "end tell"`           |

# Useful Links

- Install pocketphoenix:
  - http://www.moreiscode.com/getting-started-with-cmu-sphinx-on-mac-os-x/
- Training CMU Sphinx Speech Recognition: 
  - https://www.youtube.com/watch?v=IAHH6-t9jK0
- Sphinx Knowledge Base Tool: 
  - http://www.speech.cs.cmu.edu/tools/lmtool-new.html
- NodeJS Binding
  - https://github.com/mmende/pocketsphinx
- Javascript Sphinx
  - https://syl22-00.github.io/pocketsphinx.js/
  
