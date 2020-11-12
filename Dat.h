# ifndef DAT_HEADER
# define DAT_HEADER

struct FrequencyNode
{
	unsigned int frequency;

	FrequencyNode();
	bool operator > (FrequencyNode&);
	bool operator < (FrequencyNode&);
	bool operator >= (FrequencyNode&);
	bool operator <= (FrequencyNode&);
	void operator ++ ();
	FrequencyNode operator + (FrequencyNode&);
};

struct WhereNode
{
	unsigned int where;
	static unsigned int counter;
	WhereNode();
};

struct CodeNode
{
	unsigned int code;
	unsigned char bitLength;
	static unsigned char maxLength;
	CodeNode();
	void setCode(bool);
	void nomCode();
};

struct NextNode
{
	unsigned int next;
	NextNode();
	void operator = (WhereNode&);
	bool operator != (unsigned int);
};

# endif