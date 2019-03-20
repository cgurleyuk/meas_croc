#include "bs_file.h"
#include "daq.h"

double test_bs_file(std::vector<double> vPar) 
{
	int nSamples = static_cast<int>(vPar[0]);

	const std::string fileName = "D:\\cgurleyuk\\data\\mar2019\\test_bs_file.bin";

	daq daq_bs;
	bs_file file_bs(fileName);

	daq_bs.initialize(nSamples);
	std::vector<uint8> bs = daq_bs.read(nSamples);
	std::cout << bs.size() << " samples captured." << std::endl;

	std::cout << "Writing to " << fileName << std::endl;
	file_bs.write_bs(bs);

	daq_bs.clear();
	file_bs.close();

	return 0;
}