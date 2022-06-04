#!/bin/bash

clear

touch /tmp/previous_hash # Create a file to store the previous hash if it doesn't exist

current_hash=`sha1sum main.cpp`

previous_hash=`cat /tmp/previous_hash`

if [[ "$current_hash" == "$previous_hash" ]]; then # Detect if the file has been changed
    ./sfml-app
else # If the file has been changed, recompile
    g++ -c main.cpp
    g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
    
    echo "$current_hash" > /tmp/previous_hash
fi

