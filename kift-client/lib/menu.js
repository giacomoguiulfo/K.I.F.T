'use strict'

const isDev = (require('electron-is-dev') || global.appSettings.debug)
const { app, BrowserWindow } = require('electron')
const ipc = require('electron').ipcMain

function sendAction (action) {
  const win = BrowserWindow.getFocusedWindow()
  if (process.platform === 'darwin') {
    win.restore()
  }
  win.webContents.send(action)
}







// Improve this in the future.
// Undo = Unmake the command, it will re-invert colors, close spotify, etc...
// Redo = Will go forward, and make the command that was undo-ed.

const editSubmenu = [
  {
    role: 'undo'
  },
  {
    role: 'redo'
  }
]





// Need to be edited with Dev Tools items
var viewSubmenu = [
  {
    role: 'togglefullscreen'
  }
]











const helpSubmenu = [
  {
    label: 'Info',
    click: () => {
      ipc.emit('open-info-window')
    }
  }
]

const darwinTemplate = [
  {
    label: app.getName(),
    submenu: [
      {
        role: 'about'
      },
      {
        type: 'separator'
      },
      {
        role: 'services',
        submenu: []
      },
      {
        type: 'separator'
      },
      {
        role: 'hide'
      },
      {
        role: 'hideothers'
      },
      {
        role: 'unhide'
      },
      {
        type: 'separator'
      },
      {
        role: 'quit'
      }
    ]
  },
  {
    label: 'Edit',
    submenu: editSubmenu
  },
  {
    label: 'View',
    id: 'view',
    submenu: viewSubmenu
  },
  {
    label: 'Help',
    role: 'help',
    submenu: helpSubmenu
  }
]

const otherTemplate = [
  {
    label: 'File',
    submenu: [
      {
        role: 'quit'
      }
    ]
  },
  {
    label: 'Edit',
    submenu: editSubmenu
  },
  {
    label: 'View',
    id: 'view',
    submenu: viewSubmenu
  },
  {
    label: 'Help',
    role: 'help',
    submenu: helpSubmenu
  }
]

// Show Dev Tools menu if running in development
if (isDev) {
  viewSubmenu.push({
    type: 'separator'
  })
  viewSubmenu.push(
    {
      label: 'Toggle Developer Tools',
      accelerator: process.platform === 'darwin' ? 'Alt+Command+I' : 'Ctrl+Shift+I',
      click: function (item, focusedWindow) {
        if (focusedWindow) {
          focusedWindow.webContents.toggleDevTools()
        }
      }
    }
  )
}

module.exports = process.platform === 'darwin' ? darwinTemplate : otherTemplate
