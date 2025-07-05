#! /bin/bash

lenght=$1

# to uncomment at school42
#pwd=$(base92 $lenght < /dev/urandom | head -n 1)

pwd=$(base32 < /dev/urandom | head -c 50)
echo "Status: 300"
echo "Location: /html/pwd_generator.html?pwd=\"$pwd\""
echo ""