# include "G2K.h"

# define MIN_ARGS					2
# define MAX_ARGS					2

# define MAX_PATH_LEN			256

unsigned int dataSize;
unsigned int max_z;

struct ddl *adl = new ddl[1024];
char * inFile;
char * ouFile;

FrequencyNode *frequency;
WhereNode *where;
CodeNode *code;
NextNode *next;

INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ INT nCmdShow) {
	INT nArgs;
	LPWSTR* szArgs;
	szArgs = CommandLineToArgvW(lpCmdLine, &nArgs);
	if (nArgs < MIN_ARGS)
		exit(-0xA1);
	else if (nArgs > MAX_ARGS)
		exit(-0xA2);

	Init(szArgs[0], szArgs[1]);
}

void Init(LPWSTR inFilePath, LPWSTR outFilePath) {
	std::ifstream inFile(inFilePath, std::ios::binary);
	std::ofstream outFile;
	if(!inFile)
		exit(ERROR_INPUT_FILE);
	else {
		outFile.open(outFilePath, std::ios::binary);
		if(!outFile)
			exit(ERROR_OUTPUT_FILE);
		else {
			Compress(inFile, outFile);
		}
	}
}

void Compress(std::ifstream& inFile, std::ofstream& outFile)
{

	outFile.write(G2K_FILE_HEADER, 4);
//	flenme(arg);

	{
	inFile.seekg(0, std::ios::end);
	dataSize = (UINT)inFile.tellg();
	max_z = dataSize/16;
	inFile.seekg(0, std::ios::beg);
	}

	LPBYTE inData;
	inData = new BYTE[dataSize];
	if(!inData)
		exit(-4);
	inFile.read((char *) inData, dataSize);
	//inn.close();

	{
	unsigned int crc = getcrc(inData, dataSize);
	outFile.write((char *) &crc, sizeof crc);
	}

	outFile.write((char *) &dataSize, sizeof dataSize);

	buildLines(inData, outFile);

	unsigned int nNode = buildFrequency();
	code = new CodeNode[nNode];
		if(!code)
			exit(-5);

	next = new NextNode[nNode];
		if(!next)
			exit(-5);
	buildCode(nNode);
	buildX();

	inData = new unsigned char[dataSize];
	if(!inData)
		exit(-4);
	inFile.seekg(0, std::ios::beg);
	inFile.read((char *) inData, dataSize);
	inFile.close();

	build(inData, outFile);

	writeData(0, 7, outFile);
	outFile.flush();
	outFile.close();

}
#define MAX_Y 16
#define MAX_X 8

void buildLines(LPBYTE fle, std::ofstream& out) {
	for(unsigned int z = 0; z <= max_z; z++)
		for(unsigned int y = 0; y < MAX_Y; y++)
			for(unsigned int x = 0; x < MAX_X; x++)
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
	for(unsigned int z = 0; z <= max_z; z++)
		for(unsigned int y = 0; y < MAX_Y; y++, writeData(1, 1, out))
			for(unsigned int x = 0; x < MAX_X; x++)
				if(pointValue(fle, x, y, z)) {
					writeData(0, 1, out);
					writeData(x, 3, out);
					findLine(fle, x, y, z, false, out);
				}
	delete fle;
}
