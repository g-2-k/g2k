# include "Dat.h"

unsigned int WhereNode::counter = 0;
unsigned char CodeNode::maxLength = 0;

FrequencyNode::FrequencyNode() {
	frequency = 1;
};

bool FrequencyNode::operator > (FrequencyNode& x) {
	return (frequency > x.frequency);
};

bool FrequencyNode::operator < (FrequencyNode& x) {
	return (frequency < x.frequency);
};

bool FrequencyNode::operator >= (FrequencyNode& x) {
	return (frequency >= x.frequency);
};

bool FrequencyNode::operator <= (FrequencyNode& x) {
	return (frequency <= x.frequency);
};

void FrequencyNode::operator ++ () {
	frequency++;
};

FrequencyNode FrequencyNode::operator + (FrequencyNode& x) {
	FrequencyNode tmp;
	tmp.frequency = frequency + x.frequency;
	return tmp;
};


WhereNode::WhereNode() {
	where = counter++;
};

CodeNode::CodeNode() {
	code = 0;
	bitLength = 0;
};



void CodeNode::setCode(bool bol) {
	code >>= 1;
	bitLength++;
	if(bitLength > maxLength)
		maxLength = bitLength;
	if(bol)
		code |= 0x80000000;
};

void CodeNode::nomCode() {
	code >>= (32-bitLength);
};



NextNode::NextNode() {
	next = 0xffffffff;
};

void NextNode::operator = (WhereNode& x) {
	next = x.where;
};

bool NextNode::operator != (unsigned int x) {
	return (next != x);
};
