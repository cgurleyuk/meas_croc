#pragma once

#include <string>

enum tokenType {
	T_NUM, // number
	T_OP,  // operation
	T_STR,
	T_LBR, // left bracket
	T_RBR, // right bracket
	T_END,
	T_FUNC, // function
	T_FAS,	// function argument seperator
	T_ERR
};

struct operation { char op, pre; bool assoc; };

class token
{
public:
	token(int type, double value);
	token(int type, struct operation oper);
	token(int type, std::string str) : type(type), str(str), oper(), value(0) {};
	token(int type) : type(type), oper(), value(0) {};
	~token();

	int getType() { return type; };
	double getValue() { return value; };
	struct operation getOper() { return oper; };
	std::string getString() { return str; }

	void setType(int type) { this->type = type; };
private:
	double				value;
	struct operation	oper;
	int					type;
	std::string			str;
};

class numToken : public token {
public:
	double value() { return val; };
private:
	double val;
};

