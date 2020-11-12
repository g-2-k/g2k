# include "ddl.h"

ddl::ddl()
{
	static unsigned int ctr;
	num = 0;
	length = 0;
	if(ctr & 512)
		length += 3;
	if(ctr & 256)
		length += 4;
	if(ctr & 128)
		length += 2;
	if(ctr & 64)
		length += 3;
	if(ctr & 32)
		length += 3;
	if(ctr & 16)
		length += 3;
	if(ctr & 8)
		length += 3;
	if(ctr & 4)
		length += 4;
	if(ctr & 2)
		length += 4;
	if(ctr & 1)
		length += 3;
	sdt = new unsigned char[3000];
		if(!sdt)
			exit(-5);
		memset(sdt, 0, 3000);
	frequency = new unsigned int[3000];
		if(!frequency)
			exit(-5);
		memset(frequency, 0, 3000);
	ctr++;
};

void ddl::handleDetail(unsigned int tdl)
{
	mem sdl(sdt);
	bool flg = true;
	for(unsigned int i = 0; i < num; i++) {
		unsigned int dat = sdl.read(length);
		if(dat == tdl) {
			flg = false;
			frequency[i]++;
			break;
		}
	}
	if(flg) {
		sdl.read_flush();
		sdl.write(tdl, length);
		sdl.write_flush();
		frequency[num]++;
		num++;
	}
};

unsigned int ddl::searchDetail(unsigned int tdl)
{
	for(unsigned int q = 0; q < num; q++)
		if(dtl[q] == tdl)
			return q;
	exit(0xBAD);
	for(unsigned int lwr = 0, upr = num;;)
	{
		unsigned int i = (upr+lwr)/2;
		if(dtl[i] == tdl)
			return i;
		else if(tdl > dtl[i])
			lwr = i;
		else
			upr = i;
# ifdef _DEBUG
		if(!(upr | lwr)) {
			LPSTR buf = new CHAR[1024];
			sprintf_s(buf, 1024, "%d", tdl);
			OutputDebugStringA(buf);
			exit(-5555);
		}
# endif
	}
}
