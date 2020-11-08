# include "FindLine.h"

extern CodeNode *code;
extern struct ddl *adl;

void findLine(unsigned char *fle, unsigned int x, unsigned int y, unsigned int z, bool one, std::ofstream& out)
{
	unsigned int length;
	struct pld tld;

	for (length = 0; pointValue(fle, x+length+1, y, z); length++);
	tld.hdllne(length, 3);

	for (length = 0; pointValue(fle, x, y+length+1, z); length++);
	tld.hdllne(length, 4);

	tld.hdllne(length, 2);
	for (length = 0; pointValue(fle, x, y, z+length+1) && length+1 < 4; length++);

	for (length = 0; pointValue(fle, x-length+1, y+length+1, z); length++);
	tld.hdllne(length, 3);

	for (length = 0; pointValue(fle, x+length+1, y+length+1, z); length++);
	tld.hdllne(length, 3);

	for (length = 0; pointValue(fle, x-(length+1), y, z+length+1); length++);
	tld.hdllne(length, 3);

	for (length = 0; pointValue(fle, x+length+1, y, z+length+1); length++);
	tld.hdllne(length, 3);

	for (length = 0; pointValue(fle, x, y-(length+1), z+length+1); length++);
	tld.hdllne(length, 4);

	for (length = 0; pointValue(fle, x, y+length+1, z+length+1); length++);
	tld.hdllne(length, 4);

	for (length = 0; pointValue(fle, x+length+1, y+length+1, z+length+1); length++);
	tld.hdllne(length, 3);

	if(one)
		adl[tld.tdr].hdldtl(tld.tdl);
	else {
		unsigned int n = 0;
		for(unsigned int j = 0; j < tld.tdr; j++)
			n += adl[j].num;
		n += adl[tld.tdr].searchdtl(tld.tdl);
		writeData(code[n].code, code[n].bitLength, out);
	}
}
