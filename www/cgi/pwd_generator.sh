#! /bin/bash

read -n "$CONTENT_LENGTH" post_data

length=$(echo "$post_data" | awk -F '&' '{
  for (i = 1; i <= NF; i++) {
    split($i, kv, "=")
    if (kv[1] == "length") {
      print kv[2]
      exit
    }
  }
}')

echo "Length: $length" > /tmp/debug

# to uncomment at school42
pwd=$(cat /dev/urandom | base92 $length | head -n 1)
#pwd=$(base32 < /dev/urandom | head -c $length 2> /dev/null)

echo "pwd : $pwd" >> /tmp/debug

pwd=$(base32 < /dev/urandom | head -c 50 2> /dev/null)
echo -ne "Status: 301\r\n"
echo -ne "Location: /html/pwd_generator.html?pwd=\"$pwd\"\r\n"
echo -ne "\r\n"