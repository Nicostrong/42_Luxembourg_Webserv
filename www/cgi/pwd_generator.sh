#! /bin/bash

lenght=$1

cat /dev/urandom | base92 $lenght | head -n 1