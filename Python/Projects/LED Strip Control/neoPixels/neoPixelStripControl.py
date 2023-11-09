import time
import board
from rainbowio import colorwheel
from adafruit_led_animation.animation.blink import Blink
from adafruit_led_animation.animation.comet import Comet
from adafruit_led_animation.animation.chase import Chase
from adafruit_led_animation.sequence import AnimationSequence
from adafruit_led_animation.color import RED, PURPLE, AMBER, JADE
from adafruit_led_animation.animation.sparkle import Sparkle
from adafruit_led_animation.animation.sparklepulse import SparklePulse
from adafruit_led_animation.animation.rainbowcomet import RainbowComet
from adafruit_led_animation.animation.rainbowsparkle import RainbowSparkle
import neopixel

pixel_pin = board.GP0
num_pixels = 75

pixels = neopixel.NeoPixel(pixel_pin, num_pixels, brightness=0.3, auto_write=False)


def color_chase(color, wait):
    for i in range(num_pixels):
        pixels[i] = color
        time.sleep(wait)
        pixels.show()
    time.sleep(0.5)


def rainbow_cycle(wait):
    for j in range(255):
        for i in range(num_pixels):
            rc_index = (i * 256 // num_pixels) + j
            pixels[i] = colorwheel(rc_index & 255)
        pixels.show()
        time.sleep(wait)


# COLOR DEFINITIONS
YELLOW = (255, 150, 0)
GREEN = (0, 255, 0)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
PURPLE = (180, 0, 255)
COLOR1 = (0,255,24,76)
COLOR2 = (100,255,87,125)
COLOR3 = (175,255,205,220)
COLOR4 = (200, 10, 156, 245)
COLOR5 = (255, 0, 48, 98)

comet = Comet(pixels, speed=0.5, color=PURPLE, tail_length=30, bounce=True)
sparkle = Sparkle(pixels, speed=0.05, color=AMBER, num_sparkles=10)
sparkle_pulse = SparklePulse(pixels, speed=0.05, period=3, color=JADE)
rainbow_comet = RainbowComet(pixels, speed=0.1, tail_length=25, bounce=True)
rainbow_sparkle = RainbowSparkle(pixels, speed=0.1, num_sparkles=15)
animations = AnimationSequence(rainbow_comet, auto_clear=True)

while True:
    # pixels.fill(RED)
    # pixels.show()
    # Increase or decrease to change the speed of the solid color change.
    # time.sleep(1)
    # pixels.fill(GREEN)
    # pixels.show()
    # time.sleep(1)
    # pixels.fill(BLUE)
    # pixels.show()
    # time.sleep(1)
    

    # color_chase(RED, 0.1)  # Increase the number to slow down the color chase
    # color_chase(YELLOW, 0.1)
    # color_chase(GREEN, 0.1)
    # color_chase(CYAN, 0.1)
    # color_chase(BLUE, 0.1)
    # color_chase(PURPLE, 0.1)

    # rainbow_cycle(0)  # Increase the number to slow down the rainbow
    animations.animate()