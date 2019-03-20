#include "daq.h"

#include <iostream>

double test_daq(std::vector<double> vPar) 
{
	int nSamples = static_cast<int>(vPar[0]);

	daq daq_bs;
	daq_bs.initialize(nSamples);
	std::vector<uint8> bs = daq_bs.read(nSamples);
	std::cout << bs.size() << " samples captured:" << std::endl;

	for (auto b : bs) {
		std::cout << static_cast<unsigned>(b);
	}
	std::cout << std::endl;
	daq_bs.clear();

	return 0;
}