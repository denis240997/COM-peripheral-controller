#!/bin/bash

while read -r line; do
    timestamp="$(date +'%H:%M:%S.%6N')"
    if [[ $line == "<"* ]]; then
        echo -e "\e[34m[$timestamp] $line\e[0m"
    elif [[ $line == ">"* ]]; then
        echo -e "\e[32m[$timestamp] $line\e[0m"
    else
        echo "[$timestamp] $line"
    fi
done
