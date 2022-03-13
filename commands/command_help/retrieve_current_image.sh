#!/usr/bin/expect

spawn scp pi@192.168.50.98:/home/pi/Programs/Molly_rasp/current_image.jpg ./images/current_image.jpg

set pass "raspberry"
expect {
password: {send "$pass\r"; exp_continue}
          }
