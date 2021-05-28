#!/bin/bash

if [ $# -ne 2 ]; then
    echo "this script takes 2 arguments"
    exit 1;
    fi
if [ -e $1 ]; then
    STRING=$( ls -1 $1)
    echo "$STRING is valid!"
fi

echo "hmm..."
exit 0

