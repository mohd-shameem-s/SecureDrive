# 🚗 SecureDrive – Intelligent Vehicle Safety System

SecureDrive is an intelligent and modular safety system designed to enhance vehicle security and accident response. This embedded system leverages sensors and automation to provide accident detection, fire alerting, and anti-theft protection in real-time.

---

## 🔧 Features

- 🔥 **Fire Detection:** Real-time flame and smoke sensors trigger alerts to prevent fire hazards.
- 🚨 **Accident Detection:** Accelerometer and shock sensors detect collisions and sudden impacts.
- 🧠 **Smart Alert System:** Buzzer and display alerts for instant user notifications.
- 🔒 **Anti-Theft Mechanism:** Motion and vibration sensing to detect unauthorized movement.
- 📡 **GSM Integration:** Sends SMS alerts during emergencies (optional/expandable).
- 🌡️ **Environmental Monitoring:** Monitor temperature, gas levels, and more.

---

## 📦 Components Used

| Component            | Description                           |
|----------------------|-------------------------------------|
| Arduino Uno          | Central microcontroller              |
| Flame Sensor         | Fire detection                      |
| MQ2 Gas Sensor       | Smoke/gas leak detection            |
| Shock Sensor         | Detects accidents                   |
| Accelerometer (e.g., ADXL345) | Measures sudden motion       |
| IR Sensor            | Obstacle or presence detection      |
| Buzzer               | Audible alerts                      |
| LEDs                 | Visual indication of status         |
| 16x2 I2C LCD         | Displays system status              |
| GSM Module (Optional)| For SMS alerts                     |
| Power Supply         | 5V regulated power input            |

---

## 🛠️ How It Works

1. **Continuous Monitoring:** The system continuously monitors environmental and vehicular parameters.
2. **Event Trigger:** If fire, smoke, or shock is detected, the system activates the buzzer and notifies the driver via the LCD.
3. **Emergency Alerts:** (Optional) Sends SMS using a GSM module during critical events like crashes or fire.
4. **Visual & Audio Cues:** LEDs and buzzer alert passengers and passers-by in real-time.

---

## 🖼️ System Overview




---

## 🚀 Getting Started

### ✅ Prerequisites

- Arduino IDE
- Libraries for:
  - I2C LCD (`LiquidCrystal_I2C`)
  - ADXL345 or any accelerometer used
  - SoftwareSerial (for GSM)
  
### 🔌 Wiring

Refer to the source code and comments for detailed pin configuration. Ensure all components are correctly powered and grounded.

### 📥 Upload Code

1. Connect your Arduino to your PC.
2. Open the `SecureDrive.ino` file in Arduino IDE.
3. Select the correct COM port and board.
4. Upload the sketch.

---

## 📸 Screenshots

> _(Insert screenshots or system prototype photos here if available)_

---

## 🧠 Future Improvements

- GPS module for location-based alerts.
- Cloud integration for data logging.
- Voice alert system.
- Companion mobile app.

---

## 🎯 Applications

- Smart Cars 🚗  
- School/College Transportation 🚌  
- Emergency Vehicles 🚑  
- Fleet Safety Management 🚛

---

## 🤝 Contributing

Contributions, ideas, and feature suggestions are welcome! Feel free to fork this repo and submit a pull request.

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## 📬 Contact

Developed by [Mohd Shameem S](https://github.com/mohd-shameem-s)  
📧 *Feel free to connect for collaboration or queries!*

---

⭐️ *If you like this project, please give it a star!*
