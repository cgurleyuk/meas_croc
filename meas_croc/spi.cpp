#include "spi.h"

#include <iostream>

spi::spi()
{
}


spi::~spi()
{
}

double spi::write(double addr, double val) {
	std::cout << "Writing to " << addr << "value" << val << std::endl;

	return 1;
}

double spi::write(std::vector<double> vPar) {
	if (vPar.size() != 2) {
		std::cout << "ERR: Invalid number of parameters!" << std::endl;
		return -1;
	}

	double addr = vPar[1];
	double val	= vPar[0];
	return write(addr, val);
}