#include "interp.h"

#include <iostream>
#include <algorithm>

#include <queue>
#include <stack>

#include <string>
#include <sstream>

#include <cctype>

struct operation operations[] = {	{'+', 2, false},
									{'-', 2, false},
									{'*', 3, false},
									{'/', 3, false},
									{'^', 4, true },
									{'%', 3, false }
};

interp::interp()
{
	bExit = false;
}

interp::~interp()
{
}

void interp::register_func(std::string name, double (*func)(std::vector<double>)) {
	funcMap.emplace(name, func);
}

void interp::loop() {
	while (!bExit) {
		std::cout << ">> ";
		std::getline(std::cin, cmd);

		pos = 0;
		std::cout << eval() << std::endl;
	}
}

std::string interp::eval()
{
	std::stack<token> opStack, evalStack;
	std::queue<token> outQueue;

	while (true) {
		token curTok = nextToken();
		if (curTok.getType() == T_ERR)
			return "ERR: syntax error";
		if (curTok.getType() == T_END)
			break;

		switch (curTok.getType())
		{
		case T_NUM:
			outQueue.push(curTok);
			break;
		case T_STR:
		{
			std::unordered_map<std::string, double (*)(std::vector<double>)>::const_iterator curFunc = funcMap.find(curTok.getString());
			if (curFunc == funcMap.end())
				return "ERR: function not found";
			
			curTok.setType(T_FUNC);
			opStack.push(curTok);
			break;
		}
		case T_FAS:
		{
			while(opStack.top().getType() != T_LBR) {
				outQueue.push(opStack.top());
				opStack.pop();
			}
			break;
		}
		case T_OP:
			while (!opStack.empty()) {
				if ((!opStack.top().getOper().assoc && (opStack.top().getOper().pre >= curTok.getOper().pre)) || (opStack.top().getOper().assoc && (opStack.top().getOper().pre > curTok.getOper().pre))) {
					outQueue.push(opStack.top());
					opStack.pop();
				}
				else
					break;
			}
			opStack.push(curTok);
			break;
		case T_LBR:
			opStack.push(curTok);
			break;
		case T_RBR:
			while (!opStack.empty()) {
				if (opStack.top().getType() == T_OP) {
					outQueue.push(opStack.top());
					opStack.pop();
				}
				if (opStack.top().getType() == T_FUNC) {
					outQueue.push(opStack.top());
				}
				else {
					break;
				}
			}

			if (opStack.empty())
				return "ERR: mismatched paranthesis";
			else
				opStack.pop();

			break;
		default:
			break;
		}
	}

	while (!opStack.empty()) {
		if (opStack.top().getType() != T_LBR) {
			outQueue.push(opStack.top());
			opStack.pop();
		}
		else
			return "ERR: mismatched paranthesis";
	}

	while (!outQueue.empty())
	{
		token curTok = outQueue.front();
		outQueue.pop();

		switch (curTok.getType())
		{
		case T_NUM:
			evalStack.push(curTok);
			break;
		case T_OP:
			struct operation curOp = curTok.getOper();
			double a, b, r;
			b = evalStack.top().getValue();
			evalStack.pop();
			a = evalStack.top().getValue();
			evalStack.pop();
			switch (curOp.op)
			{
			case '+': r = a + b; break;
			case '-': r = a - b; break;
			case '*': r = a * b; break;
			case '/': r = a / b; break;
			case '^': r = pow(a, b); break;
			case '%': r = fmod(a, b); break;
			default:break;
			}
			evalStack.push(token(T_NUM, r));
			break;
		case T_FUNC:
		{
			std::vector<double> p;
			while (!evalStack.empty()) {
				p.push_back(evalStack.top().getValue());
				evalStack.pop();
			}

			std::unordered_map < std::string, double (*)(std::vector<double>) > ::const_iterator curFunc = funcMap.find(curTok.getString());
			evalStack.push(token(T_NUM, curFunc->second(p)));
			break;
		}
		default:
			break;
		}
	}

	if (evalStack.size() != 1)
		return "ERR: syntax error";

	return std::to_string(evalStack.top().getValue());
}

token interp::nextToken() {
	if (isdigit(cmd[pos]) || cmd[pos] == '.') {
		return token(T_NUM, getNum());
	}
	else if (cmd[pos] == '(') {
		pos++;
		return token(T_LBR);
	}
	else if (cmd[pos] == ')') {
		pos++;
		return token(T_RBR);
	}
	else if (std::find_if(std::begin(operations), std::end(operations), [&](auto o) {return o.op == cmd[pos]; }) != std::end(operations)) {
		// TODO: this is super ugly
		struct operation* curOp = std::find_if(std::begin(operations), std::end(operations), [&](auto o) {return o.op == cmd[pos]; });
		pos++;
		return token(T_OP, *curOp);
	}
	else if (std::isalpha(cmd[pos]) || cmd[pos] == '_') {
		int start, count;
		count = 0;
		start = pos;

		while (std::isalpha(cmd[pos]) || cmd[pos] == '_') {
			pos += 1;
			count += 1;
		}

		return token(T_STR, cmd.substr(start, count));
	}
	else if (cmd[pos] == ',') {
		pos++;
		return token(T_FAS);
	}
	else if (pos == cmd.length()) {
		return token(T_END);
	}

	return token(T_ERR);
}

double interp::getNum() {
	std::string sNum;
	// regular number
	while (isdigit(cmd[pos]) || cmd[pos] == '.') {
		sNum += cmd[pos];
		pos++;
	}
	// scientific number
	if (cmd[pos] == 'e' || cmd[pos] == 'E') {
		pos++;
		std::string sExp;

		while (isdigit(cmd[pos])) {
			sExp += cmd[pos];
			pos++;
		}

		return atof(sNum.c_str())*pow(10, atof(sExp.c_str()));
	}
	// hexadecimal number
	if ((sNum.size() == 1) && (sNum[0] == '0') && (cmd[pos] == 'x' || cmd[pos] == 'X')) {
		pos++;
		std::string sHex;
		while (isxdigit(cmd[pos])) {
			sHex += cmd[pos];
			pos++;
		}
		return strtol(sHex.c_str(), nullptr, 16);
	}
	return atof(sNum.c_str());
}