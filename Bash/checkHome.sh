#!/bin/bash
#Root user check home

cd /home
#create a list of files in home

ls -l /home > /root/home
du -s /home/r00t >> /root/home
#append the date
date >> /root/home