# ESP32-R2D2-Robot
ESP32 R2D2 Robot

This 3D printed robot contains two Microcontrollers,
one ESP32 D1 Mini and one ESP8266.   It can be controlled with
an iPhone and WiFi, or with a cheap NEC style IR remote.

Both Leg Motors are driven by N20 mini gear motors with an L298N Dual
Motor Driver Module (Amazon) and the Dome rotates using a 28BYJ-48 Geared 
Stepper Motor and a TMC2209 Stepper Motor Driver Stepstick.

# WiFi iPhone screen example:

![iPhone WiFi](https://github.com/user-attachments/assets/3e39ff1c-73ce-46de-83af-77a5930da8cc)


A 7.4V 1300mA LiPo battery is used for power.

YouTube Video:  https://www.youtube.com/shorts/CUwUT40_uZA

![schematic](https://github.com/user-attachments/assets/d01ee7aa-0c09-4023-ab8c-ede40e2cf35f)



Modified 28BYJ-48 Stepper from Unipolar to Bipolar.

![28bjy-48 cut](https://github.com/user-attachments/assets/99e91354-46ef-4642-9acc-ec05613d5742)



See stepper motor wiring order on schematic.


# Using your own IR Remote

Use this setup to read and map your own IR Remote codes.
Works with OLED or Serial Port Monitor.
When you have mapped out your buttons, insert the new codes into the "IRCodes.h" file,
following the format i have used.  "remoteButtonName[num_of_buttons]"  is used to keep
the buttons organized.


![wemos d1 ir receiver schematic](https://github.com/user-attachments/assets/25665d95-e1cf-40cf-94db-9320b0f8b185)

