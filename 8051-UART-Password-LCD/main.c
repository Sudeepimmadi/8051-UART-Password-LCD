// An 8051 microcontroller project to receive UART data, compare passwords, and display results on an LCD.

#include <reg51.h>        // Include 8051 register definitions
#include <string.h>       // Include string functions for strcmp()

// Define LCD control pins connected to Port 2
sbit RS = P2^0;           // Register Select pin
sbit RW = P2^1;           // Read/Write pin (always write = 0)
sbit EN = P2^2;           // Enable pin

// Function prototypes
void delay(unsigned int ms);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_string(char *str);
void uart_receive(char *buf);

void main() {
    char uart_data[13];          // Buffer to store received UART data (12 chars + '\0')
    unsigned char i;
    bit match_found = 0;         // Flag to check if password matched

    // List of valid passwords
    char passwords[][13] = {
        "840085AE6BC4",          // Password 1
        "6B00298CBD73"           // Password 2
    };
    unsigned char password_count = sizeof(passwords) / sizeof(passwords[0]);

    // LCD initialization command sequence
    unsigned char cmd[] = {
        0x38,  // Function Set: 8-bit, 2 lines, 5x7 font
        0x0E,  // Display ON, cursor ON
        0x06,  // Entry Mode: cursor moves right
        0x01   // Clear Display
    };

    // UART Initialization
    TMOD = 0x21;     // Timer1 Mode2 (8-bit auto-reload) for UART, Timer0 Mode1 for delay
    TH1 = 0xFD;      // Load value for 9600 baud rate
    SCON = 0x50;     // Serial mode 1, 8-bit data, REN enabled
    TR1 = 1;         // Start Timer1

    // Initialize LCD with the command sequence
    for(i = 0; i < sizeof(cmd); i++) {
        lcd_command(cmd[i]);    // Send command to LCD
        delay(5);               // Small delay after each command
    }

    // Display default message on Line 1
    lcd_command(0x80);          // Move cursor to Line 1, position 0
    lcd_string("Waiting...");   // Print default message

    // Main loop
    while(1) {
        match_found = 0;            // Reset match flag

        uart_receive(uart_data);    // Receive 12 characters from UART

        // Show received data on LCD
        lcd_command(0x01);          // Clear display
        delay(5);
        lcd_command(0x80);          // Line 1
        lcd_string("Received:");    // Display label
        lcd_command(0xC0);          // Line 2
        lcd_string(uart_data);      // Display received string
        delay(2000);                // Delay for 2 seconds

        // Compare received data with each stored password
        for(i = 0; i < password_count; i++) {
            if(strcmp(uart_data, passwords[i]) == 0) {
                match_found = 1;    // Match found
                break;
            }
        }

        // Clear screen and display result
        lcd_command(0x01); delay(5);
        lcd_command(0x80);          // Move to Line 1

        if(match_found) {
            lcd_string("Access Allowed");  // Success message
        } else {
            lcd_string("Not Allowed");     // Failure message
        }

        delay(3000);                // Show result for 3 seconds

        // Reset to default waiting screen
        lcd_command(0x01); delay(5);
        lcd_command(0x80);
        lcd_string("Waiting...");
    }
}

// Function to receive 12 characters via UART
void uart_receive(char *buf) {
    unsigned int i = 0;
    while(i < 12) {
        while(RI == 0);     // Wait for character to arrive
        buf[i] = SBUF;      // Store received character
        RI = 0;             // Clear receive interrupt flag
        i++;
    }
    buf[i] = '\0';          // Null-terminate the string
}

// Function to send command to LCD
void lcd_command(unsigned char cmd) {
    P1 = cmd;       // Send command byte to data pins
    RS = 0;         // Select Command Register
    RW = 0;         // Write mode
    EN = 1;         // Enable high
    delay(1);
    EN = 0;         // Enable low (latch the command)
    delay(1);

    // Extra delay for commands that take longer
    if(cmd == 0x01 || cmd == 0x02) {
        delay(5);
    }
}

// Function to send data (character) to LCD
void lcd_data(unsigned char dat) {
    P1 = dat;       // Send data byte to data pins
    RS = 1;         // Select Data Register
    RW = 0;         // Write mode
    EN = 1;         // Enable high
    delay(1);
    EN = 0;         // Enable low
    delay(1);
}

// Function to send a full string to LCD
void lcd_string(char *str) {
    while(*str != '\0') {
        lcd_data(*str++);   // Send each character one by one
    }
}

// Function to generate approximate millisecond delay using Timer0
void delay(unsigned int ms) {
    while(ms) {
        TL0 = 0x67;     // Load low byte (calculated for ~1ms)
        TH0 = 0xFC;     // Load high byte
        TR0 = 1;        // Start Timer0
        while(TF0 == 0); // Wait for overflow
        TR0 = 0;        // Stop Timer0
        TF0 = 0;        // Clear overflow flag
        ms--;           // Decrease ms count
    }
}
