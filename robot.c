/*
Author: ODOTofRVA
Program: Bluetooth Controlled Robot written in Embedded C.
*/



#include <avr/io.h>
#include <util/delay.h>
#include <string.h>


#define F_CPU 16000000UL // This assumes that we are using the 16MHz clock like a 16MHz oscillator.

// Define the motor pins

#define MOTOR_A_FORWARD PORTB0
#define MOTOR_A_BACKWARD PORTB1
#define MOTOR_B_FORWARD PORTB2
#define MOTOR_B_BACKWARD PORTB3


void setup(){

    // setup of motor control pins for OUTPUT
    DDRB |= (1 << MOTOR_A_FORWARD) | (1 << MOTOR_A_BACKWARD) | (1 << MOTOR_B_FORWARD) | (1 << MOTOR_B_BACKWARD);

    // Set UART for Bluetooth Communication

    UBRR0H = 0;
    UBRR0L = 103;
    UCSR0B = (1 << RXENO) | (1 << TXENO);           // Enable receiver and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);         // 8 data bbits, 1 stop bit

}



void uart_send(char data){
    while(!(UCSR0A & (1 << UDRE0)));               // wait for empty trasmit buffer
    UDR0 = data;                                   // Put data into buffer
}


char uart_receive(){
    while(!(UCSR0A & (1 << RXC0)));               // wait for empty trasmit buffer
    return UDR0;                                  // get and return received data from bufffer.
}


void move_forward(){
    PORTB |= (1 << MOTOR_A_FORWARD) | (1 << MOTOR_B_FORWARD);
    PORTB &= ~((1 << MOTOR_A_BACKWARD) | (1 << MOTOR_B_BACKWARD));
}

void move_backward(){
    PORTB |= (1 << MOTOR_A_BACKWARD) | (1 << MOTOR_B_BACKWARD);
    PORTB &= ~((1 << MOTOR_A_FORWARD) | (1 << MOTOR_B_FORWARD));
}

void turn_left(){
    PORTB |= (1 << MOTOR_A_BACKWARD) | (1 << MOTOR_B_FORWARD);
    PORTB &= ~((1 << MOTOR_A_FORWARD) | (1 << MOTOR_B_FORWARD));
}

void turn_right(){
    PORTB |= (1 << MOTOR_A_FORWARD) | (1 << MOTOR_B_BACKWARD);
    PORTB &= ~((1 << MOTOR_A_BACKWARD) | (1 << MOTOR_B_FORWARD));
}

void stop(){
    PORTB &= ~((1 << MOTOR_A_FORWARD) | (1 << MOTOR_A_BACKWARD) | (1 << MOTOR_B_FORWARD) | (1 << MOTOR_B_BACKWARD));
}


int main(void){
    setup();
    char commmand;

    while(1){
        command = uart_receive()                     //Read command from bluetooth

        switch(command){
            case 'F':move_forward(); break;         // Forward
            case 'B':move_backward(); break;        // Backward
            case 'L':turn_left(); break;            // Turn Left
            case 'R':turn_right(); break;           // Turn Right
            case 'S':stop(); break;                 // Stop
            default:stop()                          // Default to Stop
        }
    }
}