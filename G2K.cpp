# include "G2K.h"

unsigned int dataSize;
unsigned int sze;

struct ddl *adl = new ddl[1024];
char * inFile;
char * ouFile;

FrequencyNode *frequency;
WhereNode *where;
CodeNode *code;
NextNode *next;

INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ INT nCmdShow) {
	Init(FILE_IN, FILE_OP);
}

void Init(LPWSTR inf, LPWSTR ouf) {
	std::ifstream inn(inf, std::ios::binary);
	std::ofstream out;
	if(!inn)
		exit(ERROR_INPUT_FILE);
	else {
		out.open(ouf, std::ios::binary);
		if(!out)
			exit(ERROR_OUTPUT_FILE);
		else {
			Compress(inn, out);
		}
	}
}

void Compress(std::ifstream& inn, std::ofstream& out)
{

	out.write(G2K_FILE_HEADER, 4);
//	flenme(arg);

	{
	inn.seekg(0, std::ios::end);
	dataSize = (UINT)inn.tellg();
	sze = dataSize/16;
	inn.seekg(0, std::ios::beg);
	}

	LPBYTE fle;
	fle = new BYTE[dataSize];
	if(!fle)
		exit(-4);
	inn.read((char *) fle, dataSize);
	//inn.close();

	{
	unsigned int crc = getcrc(fle, dataSize);
	out.write((char *) &crc, sizeof crc);
	}

	out.write((char *) &dataSize, sizeof dataSize);

	buildLine(fle, out);

	unsigned int nNode = buildFrequency();
	code = new CodeNode[nNode];
		if(!code)
			exit(-5);

	next = new NextNode[nNode];
		if(!next)
			exit(-5);
	buildCode(nNode);
	buildX();

	fle = new unsigned char[dataSize];
	if(!fle)
		exit(-4);
	inn.seekg(0, std::ios::beg);
	inn.read((char *) fle, dataSize);
	inn.close();

	build(fle, out);

	writeData(0, 7, out);
	out.close();

}

void buildLine(LPBYTE fle, std::ofstream& out) {
	for(unsigned int z = 0; z <= sze; z++)
		for(unsigned int y = 0; y < 16; y++)
			for(unsigned int x = 0; x < 8; x++)
				if(pointValue(fle, x, y, z))
					findLine(fle, x, y, z, true, out);
	delete fle;
}

unsigned int buildFrequency()
{
	unsigned int nNode = 0;
	for(unsigned int i = 0; i < 1024; i++)
		nNode += adl[i].num;
	frequency = new FrequencyNode[nNode];
		if(!frequency)
			exit(-5);

	for(unsigned int i = 0, j = 0; i < 1024; i++) {
		for(unsigned int k = 0; k < adl[i].num; j++, k++)
			frequency[j].frequency = adl[i].frequency[k];
		delete adl[i].frequency;
	}

	where = new WhereNode[nNode];
		if(!where)
			exit(-5);

	for(unsigned int i = 0; i < nNode; i++)
	{
		if(i && frequency[i] >= frequency[i-1])
			continue;
		for(unsigned int j = 0; j < i; j++)
			if(frequency[j] > frequency[i])
			{
				FrequencyNode ftm = frequency[i];
				WhereNode wtm = where[i];
				for(unsigned int k = i; k > j; k--) {
					frequency[k] = frequency[k-1];
					where[k] = where[k-1];
				}
				frequency[j] = ftm;
				where[j] = wtm;
				break;
			}
	}

	return nNode;
}

void buildCode(unsigned int nNode)
{
	for(unsigned int i = 0; i < nNode-1; i++)
	{
		FrequencyNode ftm = frequency[i] + frequency[i+1];
		WhereNode wtm = where[i];
		unsigned int j = where[i].where;

		while(next[j] != 0xffffffff) {
			code[j].setCode(true);
			j = next[j].next;
		};
		code[j].setCode(true);
		next[j] = where[i+1];

		for(j = where[i+1].where; j != 0xffffffff; j = next[j].next)
			code[j].setCode(false);

		for(j = i+2; ; j++)
			if(ftm <= frequency[j] || j == nNode) {
				for(unsigned int k = i+1; k < j-1; k++) {
					frequency[k] = frequency[k+1];
					where[k] = where[k+1];
				}
				frequency[j-1] = ftm;
				where[j-1] = wtm;
				break;
			}
	}

	delete frequency;
	delete where;
	delete next;
}

void buildX()
{
	for(unsigned int n = 0, i = 0; i < 1024; i++)
	{
		unsigned int *tsl = new unsigned int[adl[i].num];
		memset(tsl, 0xff, adl[i].num* sizeof (unsigned int));
		mem raa(adl[i].sdt);

		for(unsigned int j = 0; j < adl[i].num; j++, n++)
		{
			unsigned int dat = raa.read(adl[i].length);
			unsigned int k = j;
			do
				if(tsl[k] < dat || !k)
				{
					CodeNode tem = code[n];
					for(unsigned int a = j, b = n; a != k; a--, b--) {
						tsl[a] = tsl[a-1];
						code[b] = code[b-1];
					}
					if(tsl[k] < dat) {
						tsl[k+1] = dat;
						code[n-j+k+1] = tem;
					}
					else {
						tsl[0] = dat;
						code[n-j] = tem;
					}
					break;
				}
			while(k--);
		}

		//delete adl[i].sdt;
		adl[i].dtl = tsl;
	}
}

void build(LPBYTE fle, std::ofstream& out)
{
	for(unsigned int z = 0; z <= sze; z++)
		for(unsigned int y = 0; y < 16; y++, writeData(1, 1, out))
			for(unsigned int x = 0; x < 8; x++)
				if(pointValue(fle, x, y, z)) {
					writeData(0, 1, out);
					writeData(x, 3, out);
					findLine(fle, x, y, z, false, out);
				}
	delete fle;
}
