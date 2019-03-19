#pragma once

#include <vector>

#include "ftd2xx.h"
#include "LibFT4222.h"

class spi
{
	FT_HANDLE ftHandle;
	FT_STATUS ftStatus;

	std::vector< FT_DEVICE_LIST_INFO_NODE > ftDevList;
public:
	spi();
	~spi();

	void listDevices(void);
	std::string devFlagToString(DWORD flags);

	void initialize();

	void write(uint8 addr, uint8 val);
	uint8 read(uint8 addr);
};

extern spi mainSPI;

double main_spi_write(std::vector<double> vPar);
double main_spi_read(std::vector<double> vPar);
double dump_spim(std::vector<double> vPar);