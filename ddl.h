# ifndef DDL_HEADER
# define DDL_HEADER

# include "..\Utilities\Memory\Mem.h"

# include <memory>
# include <Windows.h>
# include <stdlib.h>

struct ddl
{
	unsigned int num;
	unsigned int length;
	unsigned char* sdt;
	unsigned int* dtl;
	unsigned int* frequency;

	ddl();
	void handleDetail(unsigned int);
	unsigned int searchDetail(unsigned int);
};

# endif