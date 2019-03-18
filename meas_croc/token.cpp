#include "token.h"


token::token(int type, double value) : type(type), value(value), oper()
{
}

token::token(int type, struct operation oper) : type(type), oper(oper), value(0)
{
}

token::~token()
{
}