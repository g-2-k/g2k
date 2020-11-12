# include "FindLine.h"

extern CodeNode *code;
extern struct ddl *adl;

void findLine(unsigned char *fle, unsigned int x, unsigned int y, unsigned int z, bool one, std::ofstream& out)
{
	unsigned int length;
	struct pld tld;

	//   3   +   4   +   2   +   3   +   3   +   3   +   3   +   4   +   4   +   3   =   32

	for (length = 0; pointValue(fle, x+length+1, y, z); length++);
	tld.handleLine(length, 3);

	for (length = 0; pointValue(fle, x, y+length+1, z); length++);
	tld.handleLine(length, 4);

	for (length = 0; pointValue(fle, x, y, z+length+1) && length+1 < 4; length++);
	tld.handleLine(length, 2);

	for (length = 0; pointValue(fle, x-length+1, y+length+1, z) && length + 1 < 8; length++);
	tld.handleLine(length, 3);

	for (length = 0; pointValue(fle, x+length+1, y+length+1, z); length++);
	tld.handleLine(length, 3);

	for (length = 0; pointValue(fle, x-(length+1), y, z+length+1) && length + 1 < 8; length++);
	tld.handleLine(length, 3);

	for (length = 0; pointValue(fle, x+length+1, y, z+length+1); length++);
	tld.handleLine(length, 3);

	for (length = 0; pointValue(fle, x, y-(length+1), z+length+1) && length + 1 < 16; length++);
	tld.handleLine(length, 4);

	for (length = 0; pointValue(fle, x, y+length+1, z+length+1); length++);
	tld.handleLine(length, 4);

	for (length = 0; pointValue(fle, x+length+1, y+length+1, z+length+1); length++);
	tld.handleLine(length, 3);

	if(one)
		adl[tld.tdr].handleDetail(tld.tdl);
	else {
		unsigned int n = 0;
		for(unsigned int j = 0; j < tld.tdr; j++)
			n += adl[j].num;
		n += adl[tld.tdr].searchDetail(tld.tdl);
		writeData(code[n].code, code[n].bitLength, out);
	}
}
