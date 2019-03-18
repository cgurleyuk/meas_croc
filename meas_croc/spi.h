#pragma once

#include <vector>

class spi
{
public:
	spi();
	~spi();

	static double write(double addr, double val);
	static double write(std::vector<double> vParams);
};

