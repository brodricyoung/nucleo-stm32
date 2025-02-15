
// each line has offset of 4 bytes (integer type)
typedef struct {
	unsigned int MODER;		// offset: 0x00
	unsigned int OTYPER;	// offset: 0x04
	unsigned int OSPEEDR;	// offset: 0x08
	unsigned int PUPDR;		// offset: 0x0C
	unsigned int IDR;		// offset: 0x10
	unsigned int ODR;		// offset: 0x14
} Port;


// address of AHB2ENR
unsigned int* AHB2ENR = (unsigned int*) 0x4002104C;

// base addresses of the GPIO Port SFRs (I/O control registers)
Port* GPIOA = (Port*) 0x48000000;
Port* GPIOC = (Port*) 0x48000800;

// Macros
#define B1PIN 13
#define LD2PIN 5

int main(void) {
	// turn of the GPIO clocks for PA (bit 0) and PC (bit 2)
	*AHB2ENR |= 0b101; // set bits 0 and 2

	// configure B1 (PC13) as input (bits 26 and 27)
	GPIOC->MODER &= ~(0b11 << (B1PIN * 2)); // reset bits 26 and 27

	// configure LD2 (PA5) as output (bits 11 and 10)
	GPIOA->MODER &= ~(1 << (LD2PIN * 2)); // reset bit 11
	GPIOA->MODER |= (2 << (LD2PIN * 2)); // set bit 10

	while(1){
		// check status of button
		if((GPIOC->IDR & (1 << B1PIN)) == 0) { // if button pushed
			// turn on LD2 (PA5)
			GPIOA->ODR |= (1 << LD2PIN); // set bit 5
		}
		else { // if button not pushed
			// turn off LD2 (PA5)
			GPIOA->ODR &= ~(1 << LD2PIN); // reset bit 5
		}
	}
}
