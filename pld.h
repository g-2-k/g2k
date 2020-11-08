# ifndef PLD_HEADER
# define PLD_HEADER

struct pld
{
	unsigned int tdr; // Type of Shape - Series of bits per direction
	unsigned int tdl; // length of lines // could reuse for offs // 32 bits total

	pld();
	void handleLine(unsigned int length, unsigned int nBit); // Push presence bit & length
};

# endif