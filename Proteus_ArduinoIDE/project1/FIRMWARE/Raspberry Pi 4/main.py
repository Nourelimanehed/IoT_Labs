import RPi.GPIO as GPIO
import time

LED_PIN = 12
PUSH_BUTTON = 20
VALUE_PUSH_BUTTON = 0

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.setup(PUSH_BUTTON, GPIO.IN)  # set the button as an input

try:
    while True:
        # Read the button state
        VALUE_PUSH_BUTTON = GPIO.input(PUSH_BUTTON)
        if VALUE_PUSH_BUTTON == GPIO.HIGH:
            GPIO.output(LED_PIN, GPIO.HIGH)
        else:
            GPIO.output(LED_PIN, GPIO.LOW)

except KeyboardInterrupt:
    GPIO.cleanup()