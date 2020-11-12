# include "pld.h"

pld::pld() {
	tdr = 0;
	tdl = 0;
};

void pld::handleLine(unsigned int length, unsigned int nBit) {
	if (length) {
		tdr = (tdr << 1) | 0x1;
		tdl = (tdl << nBit) | length;
	}
	else
		tdr <<= 1;
};
