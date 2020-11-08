# include "pointValue.h"

bool pointValue(unsigned char *buf, unsigned int x, unsigned int y, unsigned int z)
{
	if(x > 7)
		return false;
	else if(y > 15)
		return false;
	else if(z > max_z)
		return false;

	if(z == max_z)
		if(y >= (dataSize-max_z*16))
			return false;

	buf += (z*16+y);

	switch(x)
	{
		case 0: if((*buf | 127) == 255) {
					*buf ^= 128;
					return true;
				}	break;
		case 1: if((*buf | 191) == 255) {
					*buf ^= 64;
					return true;
				}	break;
		case 2: if((*buf | 223) == 255) {
					*buf ^= 32;
					return true;
				}	break;
		case 3: if((*buf | 239) == 255) {
					*buf ^= 16;
					return true;
				}	break;
		case 4: if((*buf | 247) == 255) {
					*buf ^= 8;
					return true;
				}	break;
		case 5: if((*buf | 251) == 255) {
					*buf ^= 4;
					return true;
				}	break;
		case 6: if((*buf | 253) == 255) {
					*buf ^= 2;
					return true;
				}	break;
		case 7: if((*buf | 254) == 255) {
					*buf ^= 1;
					return true;
				}
	}
	return false;
}
