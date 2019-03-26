#include "measurement.h"

measurement::measurement()
{
}

measurement::~measurement()
{
}

void measurement::program_sr(int nChip, sr sr)
{
	uint8 addrOffset = 0x02;
	for (auto i : sr.get_vsr())
	{
		mainSPI.write(addrOffset, i);
		addrOffset++;
	}

	mainSPI.write(0x00, 0x80 | (static_cast<uint8>(nChip) & 0x03));
}

void measurement::reset_deassert(int nChip)
{
	uint8 curStatus = mainSPI.read(0x0D);
	mainSPI.write(0x0D, curStatus | (0x01 << (nChip)));
}

void measurement::bsd_assert(int nChip)
{
	uint8 read = mainSPI.read(0x0E);
	mainSPI.write(0x0E, read | (0x01 << nChip));
}

void measurement::bsd_deassert(int nChip)
{
	uint8 read = mainSPI.read(0x0E);
	mainSPI.write(0x0E, read & ~(0x01 << nChip));
}

void measurement::clkbuf_enable()
{
	uint8 read = mainSPI.read(0x0E);
	mainSPI.write(0x0E, read | 0x80);
}

void measurement::clkbuf_disable()
{
	uint8 read = mainSPI.read(0x0E);
	mainSPI.write(0x0E, read & ~0x80);
}

void measurement::sel_daq_bs(int nChip, daq_bs daq_bs)
{
	mainSPI.write(0x00, 0x00 | ((static_cast<uint8>(daq_bs) & 0x03) << 2) | (static_cast<uint8>(nChip) & 0x03) );
}

void measurement::reset_assert(int nChip)
{
	uint8 curStatus = mainSPI.read(0x0D);
	mainSPI.write(0x0D, curStatus & (~0x01 << (nChip)));
}