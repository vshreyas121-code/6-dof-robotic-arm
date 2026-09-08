

# DIY 6-DOF Robotic Arm

## 📌 Project Overview

This project documents the design, CAD modeling, assembly, wiring, and programming of a custom 6-DOF robotic arm. The robotic arm is controlled using an Arduino Mega 2560, a PCA9685 16-channel servo driver, and six positional servo motors. The mechanical components were designed in Onshape and assembled using 3D-printed parts, servo horns, screws, and hardware.

The arm is powered by a LiPo battery, fuse, switch, and 5V buck converter system. Servo angles are controlled through serial commands sent from a computer through the Arduino Serial Monitor.

The project provided practical experience in robotics, CAD design, embedded systems, servo control, electrical wiring, hardware-software integration, and mechanical troubleshooting.

---

## 🚀 Features

 -  6-DOF robotic arm movement
 - Individual servo motor control
 - Serial angle control through a computer
 - Arduino Mega 2560 control system
 - PCA9685 16-channel PWM servo driver
 - Custom robotic arm components designed in Onshape
 - 3D-printed mechanical assembly
 - External LiPo battery and 5V buck-converter power system
 - Servo angle constraints for safe operation
 - Modular and easy-to-understand Arduino code
 - Planned future autonomous pick-and-place and leader-follower control features

---

## 🛠 Hardware Components

 - Arduino Mega 2560
 - PCA9685 16-Channel Servo Driver
 - 4 MG995 Positional Servo Motors
 - 2 MG90S Positional Servo Motors
 - Custom 3D-Printed Robotic Arm Mechanical Assembly
 - LiPo Battery
 - Fuse and Fuse Holder
 - Power Switch
 - 5V Buck Converter
 - Jumper Wires
 - Servo Extension Wires
 - Screws, Nuts, and Servo Horns

---

## 💻 Software & Tools

 - Onshape
 - VS Code
 - Arduino Framework / Arduino Libraries
 - GitHub

---

## ⚙️ Technologies Used

 - Arduino Mega 2560
 - PCA9685 I2C PWM Servo Control
 - Onshape CAD Design
 - 3D Printing
 - Robotics & Automation
 - Hardware-Software Integration


---

## 📂 Project Structure

```
├── 📁cad/
│   ├── 📁step/
│   │   ├── 6-dof-robotic-arm.step
│   │   └── assembled-gripper.step
│   ├── 📁STL/
│   │   ├── 📁base/
│   │   │   ├── base-wall.stl
│   │   │   └── base.stl
│   │   ├── 📁elbow/
│   │   │   └── elbow.stl
│   │   ├── 📁gripper/
│   │   │   ├── 📁claw/
│   │   │   │   ├── left-claw.stl
│   │   │   │   └── right-claw.stl
│   │   │   ├── 📁gears/
│   │   │   │   ├── 2x-small-gear.stl
│   │   │   │   ├── big-gear-left.stl
│   │   │   │   └── big-gear-right.stl
│   │   │   ├── 2x-linkage.stl
│   │   │   └── palm.stl
│   │   ├── 📁shoulder/
│   │   │   └── shoulder.stl
│   │   ├── 📁waist/
│   │   │   └── waist.stl
│   │   └── 📁wrist/
│   │       └── wrist.stl
│   └── Onshape-Link.md
├── 📁docs/
│   ├── assembly-guide.pdf
│   └── wiring-diagram.png
├── 📁electronics/
│   ├── parts-list.pdf
│   └── wiring-diagram.png
├── 📁images/
│   ├── Robotic_Arm.mov
│   ├── finished-arm-cad.png
│   ├── finished-arm.jpeg
│   └── gripper.png
├── LICENSE
└── README.md

```

---

## 🔄 Working Principle

1. The LiPo battery provides power to the system through a fuse and power switch.
2. The battery voltage is sent to a buck converter, which supplies regulated 5V power to the Arduino Mega 2560, PCA9685 servo driver logic, and PCA9685 servo power rail.
3. The Arduino Mega communicates with the PCA9685 using I2C communication through the SDA and SCL pins.
4. The PCA9685 generates PWM signals for each servo motor.
5. Six positional servos are connected to PCA9685 channels 0 through 5.
6. The user enters six requested servo angles through the computer Serial Monitor.
7. The Arduino reads the serial command, applies safe angle limits, and commands each servo to move to its requested position.
8. The robotic arm performs the requested movement in real time.

---

## 🎯 Skills Demonstrated

 - Robotics
 - Arduino Development
 - Servo Motor Control
 - Serial Communication
 - CAD Design
 - 3D Printing
 - Electrical Wiring and Power Distribution
 - Hardware Integration
---

## 👨‍💻 My Contribution

 - Designed the complete robotic arm in Onshape.

 - Created CAD models for the mechanical arm components and exported files for fabrication.

 - Assembled the robotic arm using custom 3D-printed components, positional servos, servo horns, screws, nuts, and washers.

 - Designed and documented the power-distribution system using a LiPo battery, fuse, switch, and 5V buck converter.

 - Wired the Arduino Mega 2560, PCA9685 servo driver, and six servo motors.

 - Programmed the Arduino using VS Code.

 - Created serial-based servo-angle control for all six arm joints.

 - Tested, calibrated, and optimized servo motor movement and mechanical alignment.

 - Performed complete hardware-software integration and system testing.

---
## 🎥 Video***



https://github.com/user-attachments/assets/5076b947-41e4-44dd-bf85-272afc0f2e92




---
## 📚 Author

**Shreyas Venkatachalam**

High School student interested in robotics, mechanical design, and embedded systems.

I designed, modeled, assembled, and programmed this 6-DOF robotic arm using Onshape, 3D-printed components, an Arduino Mega 2560, a PCA9685 servo driver, and six servo motors. This project allowed me to explore robotic motion, CAD design, 3D printing, electrical wiring, serial communication, and iterative troubleshooting.

 - Email: [VShreyas121@gmail.com](mailto:VShreyas121@gmail.com)
