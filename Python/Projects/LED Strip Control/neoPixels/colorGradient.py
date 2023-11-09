# code.py for fire1 -- demonstrate using the "fire_leds" library
# 10 Oct 2022 - @todbot / Tod Kurt
# Drop this code.py and fire_leds.py into your CIRCUITPY drive
# part of https://github.com/todbot/circuitpython_led_effects

import time, board, neopixel, rainbowio, random
from ulab import numpy as np


import fire_leds

YELLOW = (255, 150, 0)
GREEN = (0, 255, 0)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
PURPLE = (180, 0, 255)
fire_color = 0xff5500
fire_fade = (-2,-2,-2)  # how much to fade R,G,B each udpate

num_leds = 64 * 1
led_pin = board.GP0
fade_by = -3
fire_color = 0xff6600

leds = neopixel.NeoPixel(led_pin, num_leds, brightness=0.4, auto_write=True)
leds_np = np.array(leds, dtype=np.int16)  # numpy working copy of LED data

fade_by = np.array( (-3,-3,-3), dtype=np.int16 )


# make up our fire
#fire_leds = fire_leds.FireLEDs(leds, fade_by=fire_fade, fire_rate=0.1 )
fire_leds = fire_leds.FireLEDs(leds, fade_by=fire_fade)

def color_chase(color, wait):
    for i in range(num_leds):
        leds[i] = color
        time.sleep(wait)
        leds.show()
    time.sleep(0.5)

def fadeInOut(color, initialBrightness, targetBrightness, wait):
    for x in range(num_leds):
        leds[x] = color
        leds.brightness = initialBrightness
        time.sleep(wait)
        leds.show()
    # time.sleep(0.6)
    
    for y in range(num_leds, 0, -1):
        for z in range(initialBrightness, targetBrightness, -1):
            leds.brightness = z
            time.sleep(wait)
            leds.show()


OFF = (0,0,0)
colorDict = {
"Crimson": (255,24,76),
"SalmonPink": (255,87,125),
"LightPink": (255,205,220),
"CerlueanBlue": (10, 156, 245),
"DarkBlue": (0, 48, 98),
"DarkRed": (139, 0, 0),
"Red": (255, 0, 0),
"OrangeRed": (255, 69, 0),
"DarkOrange": (255, 140, 0),
"Orange": (255, 165, 0),
"LightSkyBlue": (135, 206, 250),
"DeepSkyBlue": (0, 191, 255),
"Cyan": (0, 255, 255),
"DarkCyan": (0, 139, 139),
"DodgerBlue": (30, 144, 255),
"Teal": (0, 128, 128),
"Blue": (0, 0, 255),
"BlueViolet": (138, 43, 226),
"DarkOrchid": (153, 50, 204),
"DarkViolet": (148, 0, 211)
}

color_index = 0

while True:
    color_name = list(colorDict.keys())[color_index]
    color_index = (color_index + 1) % len(colorDict)
    
    for x in range(num_leds):
        leds_np[x] = colorDict.get(color_name)
        leds_np += fade_by         # fade down the working numpy array
        leds_np = np.clip(leds_np, 0,255)  # constrain everyting to 0-255
        leds[:] = leds_np.tolist()  
        time.sleep(0.05)
        leds.show()