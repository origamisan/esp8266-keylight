#include <Arduino.h>

const char MAIN_page[] PROGMEM = R"=====(
<HTML>
	<HEAD>
			<TITLE>My first web page</TITLE>
	</HEAD>
<BODY>
	<CENTER>
			<a href='/on'>On</a><br>
            <a href='/off'>Off</a><br>
	</CENTER>	
</BODY>
</HTML>
)=====";