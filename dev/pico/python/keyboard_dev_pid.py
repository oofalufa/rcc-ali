from pynput import keyboard
from pynput.keyboard import Key
from comms.messages import Twist
from comms.controller import WirelessController, WirelessInterface

c = WirelessController(WirelessInterface)
c.start_inbound()
c.start_outbound()

from input.Gamepad import Gamepad
import time


gamepadType = Gamepad.PS3
buttonHappy = 'CROSS'
buttonBeep = 'CIRCLE'
buttonExit = 'PS'
joystickSpeed = 'LEFT-Y'
joystickSteering = 'RIGHT-X'
pollInterval = 0.1


speed = 0.0
steering = 0.0

gamepad = gamepadType()
gamepad.startBackgroundUpdates()



try:
        while gamepad.isConnected():
            # Check for the exit button
            if gamepad.beenPressed(buttonExit):
                print('EXIT')
                break

            # Check for happy button changes
            if gamepad.beenPressed(buttonHappy):
                print(':)')
            if gamepad.beenReleased(buttonHappy):
                print(':(')

            # Check if the beep button is held
            if gamepad.isPressed(buttonBeep):
                print('BEEP')

            # Update the joystick positions
            # Speed control (inverted)
            speed = -gamepad.axis(joystickSpeed)
            # Steering control (not inverted)
            steering = gamepad.axis(joystickSteering)
            print('%+.1f %% speed, %+.1f %% steering' % (speed * 100, steering * 100))
           # print(speed)
            time.sleep(pollInterval)

            f = Twist((speed * 100, steering *100))
            pout = f.pack()
            c.outbound.put(pout)   



            # Sleep for our polling interval

finally:  
        # Ensure the background thread is always terminated when we are done
        gamepad.disconnect()



def on_press(key):
    try:
        print('alphanumeric key {0} pressed'.format(
            key.char))
    except AttributeError:
        print('special key {0} pressed'.format(
            key))
        
    if key.char  == 'w':
        t = Twist((95, 100))
        pout = t.pack()
        c.outbound.put(pout)     

    if key.char == 's':
        g = Twist((-100, -100))
        pout = g.pack()
        c.outbound.put(pout)  

    if key.char == 'q':
        g = Twist((0, 0))
        pout = g.pack()
        c.outbound.put(pout)  

    if key.char == 'a':
        g = Twist((70, 0))
        pout = g.pack()
        c.outbound.put(pout)  

    if key.char == 'd':
        g = Twist((0, 70))
        pout = g.pack()
        c.outbound.put(pout)  

def on_release(key):
    print('{0} released'.format(
        key))
    if key == keyboard.Key.esc:
        # Stop listener
        return False

listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

while True:
    pass