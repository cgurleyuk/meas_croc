#pragma once
#include "token.h"

#include <unordered_map>
#include <functional>

class interp
{
public:
	interp();
	~interp();

	void loop();

	void register_func(std::string name, double (*func)(std::vector<double>) );

	std::string eval();
	token		nextToken();
	double		getNum();
private:
	bool bExit;

	std::unordered_map<std::string, double (*)(std::vector<double>)> funcMap;

	std::string cmd;
	int pos;
};

