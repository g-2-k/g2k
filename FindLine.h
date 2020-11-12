# ifndef FIND_LINE_HEADER
# define FIND_LINE_HEADER

# include <fstream>
# include "pld.h"
# include "..\Utilities\Data\WriteData.h"
# include "G2K.h"

extern inline bool bolval(unsigned char*, unsigned int, unsigned int, unsigned int);
extern struct ddl* adl;

void findLine(unsigned char* fle, unsigned int x, unsigned int y, unsigned int z, bool one, std::ofstream& out);

# endif