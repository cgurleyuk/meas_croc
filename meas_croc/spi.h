#pragma once

#include <vector>

class spi
{
public:
	spi();
	~spi();

	static double write(void/*unsigned char addr, unsigned char val*/);
	static double write(std::vector<double> vParams);
};

