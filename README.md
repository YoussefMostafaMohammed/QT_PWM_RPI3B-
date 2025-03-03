# Qt6 Car Headlight PWM Control Application for Raspberry Pi 3B+ using buildroot systemv 

## Project Discreption
This application combines PWM (Pulse Width Modulation) control with GIF playback to create an interactive interface. It uses QML for the frontend and c++ for the backend to provide a graphical interface for controlling PWM signal that is connected to an LED and playing a GIF with frame-specific actions.

## Features
- PWM Control:

    - Control PWM0 channel.

    - Adjust the duty cycle and period of the PWM signals.

    - Toggle PWM signals on and off.

- GPIO Control:

    - Control GPIO pins (e.g., turn LEDs on and off).

- GIF Playback:

    - Play, pause, and resume a GIF.

    - Perform actions when specific frames of the GIF are reached (toggle PWM signals to turn on the LED).

- Cross-Platform (buildroot):

    - Designed to run on embedded Linux system (Raspberry Pi 3B+) with Qt6 support using buildroot systemV.

---

## Project Structure

```
├── qt-pwm-app
│   ├── CMakeLists.txt
│   ├── Config.in
│   ├── Main.qml
│   ├── qt-pwm-app.mk
│   ├── resources.qrc
│   └── src
│       ├── pwmController.cpp
│       ├── pwmController.h
│       └── main.cpp
└── resources
    ├── audi.gif
    ├── reverseaudi.png
    ├── itilogo.png
```

### Final Video Demo 

