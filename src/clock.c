#include "clock.h"

void Clock_Init() {

	/// #warning "Clock functionality does not account for fuses"

	// no need to calibrate OSCCAL
	
	// reset the prescaler bits
	CLKPR = CLKPR & ~(0b1111);

	// enable the prescaler change
	CLKPR |= (1 << 7);

}
