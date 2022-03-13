#!/usr/bin/expect

set timeout -1

spawn ssh pi@192.168.50.98
expect "*: " 
send "raspberry\r"

expect "pi@" 
send "cd Programs/Molly_rasp\r"
send "./take_photo\r"
send "logout\r"

expect eof
