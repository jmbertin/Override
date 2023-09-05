#!/bin/bash

for i in {1..28}
do
    echo "$i - %${i}\$p" | /home/users/level02/level02 | grep "does not have access"
done
