# ifndef G2K_HEADER
# define G2K_HEADER

# include <Windows.h>

# include <fstream>
# include <ios>
# include <stdlib.h>
# include <memory>
# include <algorithm>
# include <vector>

# include "..\Utilities\Files\FileName.h"
# include "..\Utilities\CRC\Getcrc.h"
# include "..\Utilities\Data\WriteData.h"
# include "..\Utilities\Memory\mem.h"
# include "pointValue.h"
# include "pld.h"
# include "ddl.h"
# include "dat.h"
# include "FindLine.h"

# define FILE_IN			L"MOC.bmp"
# define FILE_OP			L"MOC.g2k"

# define ERROR_INPUT_FILE	-2
# define ERROR_OUTPUT_FILE	-3

# define G2K_FILE_HEADER	"G2Kn"

inline void flenme(char *[]);
inline unsigned int getcrc(unsigned char *, unsigned int);
inline bool pointValue(unsigned char *, unsigned int, unsigned int, unsigned int);
inline void wrtdat(unsigned int, signed int);
inline void findLine(unsigned char *, unsigned int, unsigned int, unsigned int, bool);
void Init(LPWSTR inf, LPWSTR ouf);
void Compress(std::ifstream& inn, std::ofstream& out);
void buildLine(LPBYTE fle, std::ofstream& out);
unsigned int buildFrequency();
void buildCode(unsigned int non);
void buildX();
void build(LPBYTE fle, std::ofstream& out);

# endif