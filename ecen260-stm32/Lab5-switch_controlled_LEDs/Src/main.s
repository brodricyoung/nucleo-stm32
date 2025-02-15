	.text
	.global main
	.cpu cortex-m4
	.syntax unified

main:
	// base address of Port A = 0x48000000
	MOV R4, #0x0000
	MOVT R4, #0x4800

	// base address of Port C = 0x48000800
	MOV R5, #0x0800
	MOVT R5, #0x4800

	// Address of Reset/Clock control advanced high performace bus 2 enable register
	// RCC AHB2 ENR = 0x4002104C
	MOV R6, #0x104C
	MOVT R6, #0x4002

	// Enable the I/O port clocks with RCC AHB2 ENR (R6)
	MOV R0, #0b00000101
	STR R0, [R6]

	// ******* Configure LED2 (PA5) as output ***********
	// Create bitmask to reset bit 11 of PA MODER (bit 10 already initializes to 1)
	MOV R1, #0x0800 // 0000 1000 0000 0000
	MVN R1, R1 // flip the bits, mask = 1111 0111 1111 1111
	// read PA MODER value, reset bit 11 and write back to PA MODER
	LDR R0, [R4] // load PA MODER
	AND R0, R1 // bitmask to reset bit 11
	STR R0, [R4] // store PA MODER

	// ************ Configure Button 1 (PC13) as input *********
	// Create bitmask to reset bits 26 and 27 of PC MODER
	MOV R1, #0x0000
	MOVT R1, #0x0C00 // 0000 1100 0000 0000 0000 0000 0000 0000
	MVN R1, R1 // flip the bits, mask = 1111 0011 1111 1111 1111 1111 1111 1111
	// read PC MODER value, reset bits 26 and 27 and write back to PC MODER
	LDR R0, [R5] // load PC MODER
	AND R0, R1 // bitmask to reset bits 26 and 27
	STR R0, [R5] // store PC MODER

	// ************ Configure button 3 (PA1) as input with pull up resistor ************
	// MODER
	MOV R1, #0xC // 0000 0000 0000 0000 0000 0000 0000 1100
	MVN R1, R1   // 1111 1111 1111 1111 1111 1111 1111 0011
	LDR R0, [R4] // load in Port A MODER
	AND R0, R1 // bit mask to reset bits 3 and 4
	STR R0, [R4] // store PA MODER

	LDR R0, [R4, #0xC] // load in PA PUPDR

	// set bit 2
	MOV R1, #0x4 // 0000 0000 0000 0000 0000 0000 0000 0100
	ORR R0, R1

	STR R0, [R4, #0xC] // store PA PUPDR


	// ************ Configure LED4 (PA0) as output **************
	// Create bitmask to reset bit 1 of PA MODER (bit 0 already initializes to 1)
	MOV R1, #0x2 // 0000 0000 0000 0010
	MVN R1, R1      // 1111 1111 1111 1101
	// read PA MODER value, reset bit 1 and write back to PA MODER
	LDR R0, [R4] // load PA MODER
	AND R0, R1 // bitmask to reset bit 1
	STR R0, [R4] // store PA MODER


loop:
	// *********** Read status of button 1 (PC13)
	// creat bitmask to read bit 13 pf PC IDR
	MOV R1, #0x2000
	// read PC IDR value, reset all bits except bit 13
	LDRH R0, [R5, #0x10] // load PC IDR
	AND R0, R1 // bitmask to reset all bits excpet bit 13

	// check value. Zero = button pushed. NonZero = button not pushed
	CMP R0, #0
	BNE elseLED2 // if not pushed, go to "elseLED2" otherwise continue to "if"

if:
	// ************** Read status of button 3 **************
	MOV R1, #0x2 // bitmask to reset all bits but bit 1
	LDRH R0, [R4, #0x10] // load PA IDR
	AND R0, R1 // reset all bits but bit 1

	CMP R0, #0 // 0 = button pushed, nonzero = not pushed
	BNE ifLED2andelseLED4 // if not pushed, branch to turn on LED4 and off LED2
	BL turnonLED2 // both button 1 and 3 pushed
	BL turnoffLED4
	B loop

// this function is called if button 1 is not pressed.
// It reads the status on button 3 and if it is pressed, turns on LED4
// and LED2 off. otherwise branches to turn off both
elseLED2:
	// ************** Read status of button 3 **************
	MOV R1, #0x2 // bitmask to reset all bits but bit 1
	LDRH R0, [R4, #0x10] // load PA IDR
	AND R0, R1 // reset all bits but bit 1

	CMP R0, #0 // 0 = button pushed, nonzero = not pushed
	BNE elseLED2and4
	BL turnonLED4
	BL turnoffLED2
	B loop

// this function turns of both LEDs
// called when no button is pressed
elseLED2and4:
	BL turnoffLED2
	BL turnoffLED4
	B loop

// this function turns on LED4 and turns off LED2
// called when exactly one button is pressed
ifLED2andelseLED4:
	BL turnoffLED2
	BL turnonLED4
	B loop

// This function turns off LED2
// it assumes R4 still has PA base address
turnoffLED2:
	// creat bitmask to reset bit 5
	MOV R1, #0x0020 // 0000 0000 0010 0000
	MVN R1, R1 // flip the bits (MOVE NOT), mask = 1111 1111 1101 1111

	// read PA ODR value, reset bit 5, and write back to PA ODR
	LDRH R0, [R4, #0x14] // load PA ODR (PA base + 0x14)
	AND R0, R1 // reset bit 5 using mask
	STRH R0, [R4, #0x14] //store PA ODR
	BX LR

// This function turns on LED2
// it assumes R4 still has PA base address
turnonLED2:
	// creat bitmask to set bit 5
	MOV R1, #0x0020 // 0000 0000 0010 0000

	// read PA ODR value, reset bit 5, and write back to PA ODR
	LDRH R0, [R4, #0x14] // load PA ODR (PA base + 0x14)
	ORR R0, R1 // set bit 5 using mask
	STRH R0, [R4, #0x14] //store PA ODR
	BX LR

// This function turns off LED4
// it assumes R4 still has PA base address
turnoffLED4:
	// creat bitmask to reset bit 0
	MOV R1, #0x1 // 0000 0000 0000 0001
	MVN R1, R1   // 1111 1111 1111 1110

	// read PA ODR value, reset bit 0, and write back to PA ODR
	LDRH R0, [R4, #0x14] // load PA ODR (PA base + 0x14)
	AND R0, R1 // reset bit 0 using mask
	STRH R0, [R4, #0x14] //store PA ODR
	BX LR

// This function turns on LED4
// it assumes R4 still has PA base address
turnonLED4:
	// creat bitmask to set bit 0
	MOV R1, #0x1 // 0000 0000 0000 0001

	// read PA ODR value, reset bit 0, and write back to PA ODR
	LDRH R0, [R4, #0x14] // load PA ODR (PA base + 0x14)
	ORR R0, R1 // set bit 0 using mask
	STRH R0, [R4, #0x14] //store PA ODR
	BX LR

	.end
