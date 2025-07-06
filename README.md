This project demonstrates how to use an 8051 microcontroller to:

* Receive 12-character strings over UART (serial communication)

* Compare received strings to predefined passwords

* Display the received string and the verification result (Access Allowed / Not Allowed) on a 16x2 LCD.

The code uses C language with the Keil compiler (or similar) and includes:

* UART initialization at 9600 baud

* LCD 8-bit mode control and data functions

* Delay functions via Timer0

* Password matching logic
