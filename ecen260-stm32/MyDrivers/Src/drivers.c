/*
 * drivers.c
 *
 *  Created on: Feb 18, 2025
 *      Author: young
 */

////////////////////// function definitions /////////////////////////////

#include "drivers.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// enables the clock for GPIOA, GPIOB, and GPIOC
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GPIOA_ClkEnable(void) {
	*AHB2ENR |= 0b001; // set bit 0 for Port A
}

void GPIOB_ClkEnable(void) {
	*AHB2ENR |= 0b010; // set bit 1 for Port B
}

void GPIOC_ClkEnable(void) {
	*AHB2ENR |= 0b100; // set bit 2 for Port C
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// configure MODER of a given port for a given pin as an input or output
// - mode: GPIO_MODE_INPUT, GPIO_MODE_OUTPUT
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GPIO_Mode(Port* GPIOx, uint32_t pin, uint32_t mode) {
	switch (mode) {
		case GPIO_MODE_INPUT: // 00
			GPIOx->MODER &= ~BITPAIR(pin); // reset both bits
			break;

		case GPIO_MODE_OUTPUT: // 01
			uint32_t temp = GPIOx->MODER;	// read the MODER
			temp &= ~UBIT(pin); 			// reset upper bit
			temp |= LBIT(pin); 				// set lower bit
			GPIOx->MODER = temp; 			// clock in entire configuration in 1 clock cycle to avoid glitches
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// toggle the value of a given output pin of given port
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GPIO_Toggle(Port* GPIOx, uint32_t pin) {
	GPIOx->ODR ^= (BIT(pin)); // toggle the bit
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// write a given state value to a given pin of a given port
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GPIO_WritePin(Port* GPIOx, uint32_t pin, uint32_t state) {
	// if state != 0, set the bit
	if (state) {
		GPIOx->ODR |= BIT(pin); // set bit
	}
	// if state = 0, reset the bit
	else {
		GPIOx->ODR &= ~BIT(pin); // reset bit
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// configure pull resistors for a given pin on a given port
// - pull: GPIO_NOPULL, GPIO_PULLUP, GPIO_PULLDOWN
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GPIO_Pull(Port* GPIOx, uint32_t pin, uint32_t pull) {
	uint32_t temp; // temporary storage to clock in all changes at once

	switch(pull) {
		case GPIO_NOPULL: // 00
			GPIOx->PUPDR &= ~BITPAIR(pin); // reset both bits
			break;

		case GPIO_PULLUP: // 01
			temp = GPIOx->PUPDR; // read the PUPDR
			temp &= ~UBIT(pin);  // reset upper bit
			temp |= LBIT(pin);   // set lower bit
			GPIOx->PUPDR = temp; // clock in entire configuration in 1 clock cycle to avoid glitches
			break;

		case GPIO_PULLDOWN: // 10
			temp = GPIOx->PUPDR; // read the PUPDR
			temp |= UBIT(pin); 	 // set upper bit
			temp &= ~LBIT(pin);  // reset lower bit
			GPIOx->PUPDR = temp; // clock in entire configuration in 1 clock cycle to avoid glitches
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// read and then return the value of a pin as either a "1" or a "0"
// Example:
// 			Assume the IDR = 0001 0010 1101 1010, and you are reading pin 4.
// 			Returns 0000 0000 0000 0001
// 			if reading pin 3, returns 0000 0000 0000 0000
////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t GPIO_ReadPin(Port* GPIOx, uint32_t pin) {
	return ((GPIOx->IDR & BIT(pin)) >> pin); // get the bit by itself and shift to bit 0 place
}
