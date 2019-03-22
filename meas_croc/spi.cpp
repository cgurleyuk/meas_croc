#include "spi.h"

#include <iostream>

spi::spi()
{
	ftHandle = NULL;

	listDevices();
	initialize();
}


spi::~spi()
{
	FT4222_UnInitialize(ftHandle);
	FT_Close(ftHandle);
}

void spi::listDevices(void)
{
	FT_STATUS ftStatus = 0;

	DWORD numOfDevices = 0;
	ftStatus = FT_CreateDeviceInfoList(&numOfDevices);

	for (DWORD iDev = 0; iDev < numOfDevices; ++iDev)
	{
		FT_DEVICE_LIST_INFO_NODE devInfo;
		memset(&devInfo, 0, sizeof(devInfo));

		ftStatus = FT_GetDeviceInfoDetail(iDev, &devInfo.Flags, &devInfo.Type, &devInfo.ID, &devInfo.LocId,
			devInfo.SerialNumber,
			devInfo.Description,
			&devInfo.ftHandle);

		// TODO: remove printing to console here
		if (FT_OK == ftStatus)
		{
			printf("Dev %d:\n", iDev);
			printf("  Flags= 0x%x, (%s)\n", devInfo.Flags, devFlagToString(devInfo.Flags).c_str());
			printf("  Type= 0x%x\n", devInfo.Type);
			printf("  ID= 0x%x\n", devInfo.ID);
			printf("  LocId= 0x%x\n", devInfo.LocId);
			printf("  SerialNumber= %s\n", devInfo.SerialNumber);
			printf("  Description= %s\n", devInfo.Description);
			printf("  ftHandle= 0x%x\n", devInfo.ftHandle);

			const std::string desc = devInfo.Description;
			if (desc == "FT4222" || desc == "FT4222 A")
			{
				ftDevList.push_back(devInfo);
			}
		}
	}
}

std::string spi::devFlagToString(DWORD flags)
{
	return std::string();
}

void spi::initialize()
{
	ftStatus = FT_OpenEx((PVOID)ftDevList[0].LocId, FT_OPEN_BY_LOCATION, &ftHandle);
	ftStatus = FT4222_SPIMaster_Init(ftHandle, SPI_IO_SINGLE, CLK_DIV_128, CLK_IDLE_LOW, CLK_LEADING, 0x01);
}

void spi::write(uint8 addr, uint8 val) {
	uint8 writeBuffer[2] = { (uint8)addr, (uint8)val };
	uint8 readBuffer[2] = { 0x00, 0x00 };
	uint16 sizeTransfer;
	FT4222_SPIMaster_SingleReadWrite(ftHandle, readBuffer, writeBuffer, 2, &sizeTransfer, false);
	//std::cout << "spi_w, addr -> " << std::hex << static_cast<unsigned>(addr) << ", data -> " << static_cast<unsigned>(val) << std::dec << std::endl;
}

uint8 spi::read(uint8 addr) {
	uint8 writeBuffer[2] = { (static_cast<uint8>(addr))|0x80, 0x00 };
	uint8 readBuffer[2] = { 0x00, 0x00 };
	uint16 sizeTransfer;

	FT4222_SPIMaster_SingleReadWrite(ftHandle, readBuffer, writeBuffer, 2, &sizeTransfer, false);
	//std::cout << "spi_r, addr -> " << std::hex << static_cast<unsigned>(writeBuffer[0]) << ", read -> " << static_cast<unsigned>(readBuffer[1]) << std::dec << std::endl;

	return readBuffer[1];
}

double main_spi_write(std::vector<double> vPar)
{
	if (vPar.size() != 2) {
		std::cout << "ERR: Invalid number of parameters!" << std::endl;
		return -1;
	}

	uint8 addr = static_cast<uint8>(vPar[1]);	
	uint8 val = static_cast<uint8>(vPar[0]);
	mainSPI.write(addr, val);
	return 1.0;
}


double main_spi_read(std::vector<double> vPar)
{
	if (vPar.size() != 1) {
		std::cout << "ERR: Invalid number of parameters!" << std::endl;
		return -1;
	}

	uint8 addr = (uint8)vPar[0];
	uint8 read = mainSPI.read(addr);

	return (double)read;
}

double main_spi_dump_fpga(std::vector<double> vPar)
{
	if (vPar.size() != 0) {
		std::cout << "ERR: Invalid number of parameters!" << std::endl;
		return -1;
	}

	uint8 addr = 0x00;
	for (addr = 0x00; addr <= 0x0D; addr = addr + 1) {
		mainSPI.read(addr);
	}

	return 0;
}