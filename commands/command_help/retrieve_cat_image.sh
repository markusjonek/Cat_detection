#!/usr/bin/expect

spawn scp pi@192.168.50.98:/home/pi/Programs/Cat_detection/cat_image.jpg ./images/cat_image.jpg

set pass "raspberry"
expect {
password: {send "$pass\r"; exp_continue}
		  }