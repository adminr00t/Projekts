#!/bin/bash
i=o
until [ $i -eq 10 ]; do
    (( i = i + 1))
    echo -n "$i"
done
echo " "
exit 0