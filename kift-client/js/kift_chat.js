// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   kift_chat.js                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/06/18 02:47:07 by jaleman           #+#    #+#             //
//   Updated: 2017/06/18 02:47:08 by jaleman          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

// Put a message into the chat.
function putMessage(name, image, message) {
    var targetElement = document.getElementById("showMessage");
    var newElement = document.createElement('span');
    newElement.innerHTML = '<div class="' + name + '"><img src="' +
        image + '" width=32 height=32 /><div class="message"><p>' +
        message + '</p></div></div>';
    targetElement.appendChild(newElement);
}

// ...
function parseChat(message) {
    var userMessage = message[0];
    var kevinMessage = message[1];

	if (kevinMessage == "name missing\n")
		return ;
    putMessage("user", "images/avatar.png", userMessage);
    putMessage("kevin", "images/logo-icon.png", kevinMessage);
    responseVoice(kevinMessage);
}
