/* 
 * File:   defines.h
 * Author: Mike Mogenson
 *
 * Created on December 24, 2014, 9:02 PM
 */

#ifndef DEFINES_H
#define	DEFINES_H

// INCLUDES --------------------------------------------------------------------

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "usb.h"
#include "usb_config.h"
#include "usb_ch9.h"
#include "usb_cdc.h"

// CONFIGURATION BITS ----------------------------------------------------------

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = NOCLKDIV// CPU System Clock Selection Bit (NO CPU system divide)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x     // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = ENABLED  // PLL Enable Bit (3x or 4x PLL Enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = ON       // Low-Power Brown Out Reset (Low-Power BOR is enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// DEFINES ---------------------------------------------------------------------

#define _XTAL_FREQ  48000000

#define OUTPUT      0
#define INPUT       1

#define true        1
#define false       0

// LED defines for PICkit 2 Low Pin Count Demo Board
#define DS1_TRIS    TRISCbits.TRISC0
#define DS1_LAT     LATCbits.LATC0
#define DS1         PORTCbits.RC0

#define DS2_TRIS    TRISCbits.TRISC1
#define DS2_LAT     LATCbits.LATC1
#define DS2         PORTCbits.RC1

#define DS3_TRIS    TRISCbits.TRISC2
#define DS3_LAT     LATCbits.LATC2
#define DS3         PORTCbits.RC2

#define DS4_TRIS    TRISCbits.TRISC3
#define DS4_LAT     LATCbits.LATC3
#define DS4         PORTCbits.RC3

#endif	/* DEFINES_H */

