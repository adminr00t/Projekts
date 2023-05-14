#!/usr/bin/env python3
import requests

url = "https://jp.translink.com.au/plan-your-journey/stops/roma-street-station"
page = requests.get(url)
source = page.content

with open("trainSchedule.html", "w")  as f:
    print(, file=f)
f.close()
