#! /bin/bash

lenght=$1

# to uncomment at school42
#pwd=$(base92 $lenght < /dev/urandom | head -n 1)

pwd=$(base32 < /dev/urandom | head -c 50 2> /dev/null)
echo -ne "Status: 301\r\n"
echo -ne "Location: /html/pwd_generator.html?pwd=\"$pwd\"\r\n"
echo -ne "\r\n"