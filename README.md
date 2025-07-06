# 📟 UART Password Verification on 8051 Microcontroller

This project demonstrates how to use an **8051 microcontroller** (e.g., AT89C51 or AT89S52) to:

✅ Receive 12-character strings over UART (serial communication)  
✅ Compare them to pre-defined passwords stored in flash memory  
✅ Display the received string and the verification result on a **16x2 LCD**  

It’s a simple embedded authentication example suitable for learning **UART interfacing, LCD control, and string comparison**.

---

## 🛠 Features

- **UART Communication**  
  - Baud Rate: 9600
  - Receives 12 characters
- **Password Matching**  
  - Supports multiple predefined passwords
- **LCD Display**
  - Displays “Received” string
  - Shows whether access is *Allowed* or *Not Allowed*
- **Non-blocking Loop**
  - Waits for new input automatically

---

## ⚙️ Hardware Requirements

- 8051-compatible microcontroller (AT89C51 or equivalent)
- 16x2 LCD Display
- USB-to-Serial converter (or MAX232 + RS232 port)
- 12 MHz crystal oscillator
- Capacitors, resistor, push button for reset circuit
- 5V power supply

---

## 🧩 Circuit Connections (Summary)

- **LCD Data Pins**: Port 1 (P1.0 - P1.7)
- **LCD Control Pins**:
  - RS → P2.0
  - RW → P2.1
  - EN → P2.2
- **UART Pins**:
  - TXD (P3.1) → USB Serial RX
  - RXD (P3.0) → USB Serial TX

---

## 💾 How It Works

1. Initializes UART at 9600 baud.
2. Configures LCD in 8-bit mode.
3. Waits for 12-character input over UART.
4. Compares received string to stored passwords:
   - If **match found**, displays `Access Allowed`.
   - If **no match**, displays `Not Allowed`.
5. Loops back to wait for the next input.

---

## 📂 Files

- `main.c` – Complete C source code with detailed comments
- `README.md` – This documentation

---

## 🚀 Getting Started

1. Flash the HEX file to your 8051 microcontroller.
2. Connect your serial terminal (e.g., PuTTY) to the UART interface at 9600 baud.
3. Power the board and reset if needed.
4. Send a 12-character password string.
5. Observe the result on the LCD.

---

## ✏️ Example Passwords

These passwords are hard-coded:

"840085AE6BC4"
"6B00298CBD73"


Modify them in `char passwords[][13]` in the C code as needed.

---

## 📜 License

This project is provided for educational purposes. Feel free to modify and adapt for your learning or prototyping.

---
