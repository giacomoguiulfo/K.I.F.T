// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   script.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/06/08 09:54:04 by jaleman           #+#    #+#             //
//   Updated: 2017/06/08 09:54:06 by jaleman          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

var d, h, m, i = 0;



// Scrollbar

$(window).load(function() {
  $('.messages-content').mCustomScrollbar();
  setTimeout(function() {
    fakeMessage();
  }, 100);
});

function updateScrollbar() {
  $('.messages-content').mCustomScrollbar("update").mCustomScrollbar('scrollTo', 'bottom', {
    scrollInertia: 10,
    timeout: 0
  });
}






function setDate(){
  d = new Date()
  if (m != d.getMinutes()) {
    m = d.getMinutes();
    $('<div class="timestamp">' + d.getHours() + ':' + m + '</div>').appendTo($('.message:last'));
  }
}

function insertMessage() {

	setTimeout(function() {
      msg = "patacon";
  }, 10000 + (Math.random() * 20) * 100);

	msg = "patacon";

  //msg = $('.message-input').val();
  //if ($.trim(msg) == 'patacon') {
//    return false;
  //}


  setTimeout(function() {
	  $('<div class="message message-personal">' + msg + '</div>').appendTo($('.mCSB_container')).addClass('new');
	  setDate();
	  $('.message-input').val(null);
	  updateScrollbar();
  }, 1000 + (Math.random() * 20) * 100);





  setTimeout(function() {
    fakeMessage();
  }, 1000 + (Math.random() * 20) * 100);
}

//$('.message-submit').click(function() {
 // insertMessage();
//});

$(window).on('keydown', function(e) {
  if (e.which == 13) {
    insertMessage();
    return false;
  }
})

var Fake = [
  'Hello Mr. Abraham. In what can I help you with?',
  'Don\'t call me that!',
  'Please!',
]

function fakeMessage() {

  //if ($('.message-input').val() != '') {
//    return false;
  //}

  if (insertMessage() == false)
  	return false;

  $('<div class="message loading new"><figure class="avatar"><img src="img/icon.png" style="width: 25px; height: auto;" alt="logo" /></figure><span></span></div>').appendTo($('.mCSB_container'));
  updateScrollbar();

  setTimeout(function() {
    $('.message.loading').remove();


	if (i > 2)
		i = 2;

	responsiveVoice.speak(Fake[i]);


    $('<div class="message new"><figure class="avatar"><img src="img/icon.png" style="width: 25px; height: auto;" alt="logo" /></figure>' + Fake[i] + '</div>').appendTo($('.mCSB_container')).addClass('new');
    setDate();
    updateScrollbar();
    i++;
  }, 1000 + (Math.random() * 20) * 100);

}
