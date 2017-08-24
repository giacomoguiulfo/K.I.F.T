// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   electron-init.js                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/08/24 00:51:15 by jaleman           #+#    #+#             //
//   Updated: 2017/08/24 00:51:16 by jaleman          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

const {remote} = require('electron')
const {Menu, MenuItem} = remote

const menu = new Menu()
menu.append(new MenuItem({label: 'MenuItem1', click() { console.log('item 1 clicked') }}))
menu.append(new MenuItem({type: 'separator'}))
menu.append(new MenuItem({label: 'MenuItem2', type: 'checkbox', checked: true}))

window.addEventListener('contextmenu', (e) => {
  e.preventDefault()
  menu.popup(remote.getCurrentWindow())
}, false)
