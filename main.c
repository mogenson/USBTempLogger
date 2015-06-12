/*
 * File:   main.c
 * Author: Mike Mogenson
 *
 * Created on December 24, 2014, 9:00 PM
 */

// INCLUDES --------------------------------------------------------------------

#include "defines.h"

// GLOBAL VARIABLES ------------------------------------------------------------

//volatile float temperature;
volatile uint16_t tempADC;
volatile uint32_t millis; // counter that increments every millisecond


// FUNCTION PROTOTYPES ---------------------------------------------------------

void oscillator_init();
void timer_init();
void gpio_init();
void thermometer_init();
void putch(char);

// INTERRUPT ROUTINE -----------------------------------------------------------

void interrupt isr() {
    if (PIR1bits.TMR2IF) { // timer 2 interrupt at 1000 Hz
        millis++;
        PIR1bits.TMR2IF = 0; // reset flag
        return;
    }

    usb_service(); // service usb
}

// MAIN FUNCTION ---------------------------------------------------------------

void main() {
    oscillator_init();
    gpio_init();
    thermometer_init();
    timer_init();
    usb_init();


    while (1) {
 
        if ((millis % 1000) == 0) { // TODO: make this more efficient
            __delay_ms(1);  // dont trigger multiple times within one ms
            //DS4_LAT ^= 1;     // toggle LED 4
            //DS3_LAT ^= 1;     // toggle LED 3
            //printf("Temperature = %d (ADC counts)\r", tempADC);
            printf("%d\r", tempADC);    // print just the ADC count
        }
        
        // temperature measurement
        ADCON0bits.ADGO = 1; // start ADC measurement
        while (ADCON0bits.ADGO != 0); // wait for conversion
        tempADC = (ADRESH << 8) + ADRESL;
        // conversion to degrees celsius based on sample calibration from AN1333
        //temperature = 0.925679 * tempADC - 487.727;
        // could be done faster with a lookup table
    }
}

// FUNCTION IMPLEMENTATIONS ----------------------------------------------------

void putch(char data) {
    static int index = 0;
    char *printBuf = usb_get_in_buffer(2);

    printBuf[index] = data;
    index++;

    if (data == '\r' || data == '\n' || index == EP_2_LEN) { // end of line or full buffer
        // send data
        if (usb_is_configured() && !usb_in_endpoint_halted(2)) {
            while (usb_in_endpoint_busy(2));
            usb_send_in_buffer(2, index);

            if (index == EP_2_LEN) {
                while (usb_in_endpoint_busy(2));
                usb_send_in_buffer(2, 0); // send zero-length packet
            }
 
        }
        index = 0;
    }
}

void thermometer_init() {
    FVRCONbits.TSEN = 1; // enable thermometer
    FVRCONbits.TSRNG = 1; // high range: Vout = Vdd - 4*Vt

    ADCON0bits.CHS = 0b11101; // select temp sensor channel

    ADCON1bits.ADFM = 1; // adc output right justified
    ADCON1bits.ADCS = 0b111; // use internal Frc oscillator
    ADCON1bits.ADPREF = 0b00; // Vref internally connected to Vdd

    ADCON0bits.ADON = 1; // enable ADC
    __delay_ms(1); // give adc time to charge
}

void oscillator_init() {
    OSCCONbits.IRCF = 0b1111; // 48 MHz internal clock

    // enable clock tuning from USB
    ACTCONbits.ACTSRC = 1;
    ACTCONbits.ACTEN = 1;
}

void timer_init() {
    //Timer2 Registers Prescaler= 4 - TMR2 PostScaler = 12 - PR2 = 250 - Freq = 1000.00 Hz - Period = 0.001000 seconds
    T2CON |= 88; // bits 6-3 Post scaler 1:1 thru 1:16
    T2CONbits.T2CKPS1 = 0; // bits 1-0  Prescaler Rate Select bits
    T2CONbits.T2CKPS0 = 1;
    PR2 = 250; // PR2 (Timer2 Match value)

    INTCONbits.GIE = 1; // global interrupts enabled
    INTCONbits.PEIE = 1; // peripheral interrupts enabled
    PIE1bits.TMR2IE = 1; // timer 2 interrupt enabled

    T2CONbits.TMR2ON = 1; // turn timer 2 on
}

void gpio_init() {
    // disable adc pins
    ANSELA = 0x00;
    ANSELC = 0x00;

    // LEDs as outputs
    //DS1_TRIS = OUTPUT;
    //DS2_TRIS = OUTPUT;  // RC0 and RC1 are tied to RA0 (D+) and RA1 (D-) on low pin count board
    //DS3_TRIS = OUTPUT;
    //DS4_TRIS = OUTPUT;

    //DS1 = 0;
    //DS2 = 0;
    //DS3 = 1;
    //DS4 = 0;
}
