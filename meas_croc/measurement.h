#pragma once
#include "daq.h"
#include "spi.h"
#include "sr.h"
#include "bs_file.h"

extern spi mainSPI;

enum daq_bs
{
	daq_bsa,
	daq_bsb,
	daq_bsc
};

class measurement
{
public:
	measurement();
	~measurement();

	void fpga_verify_and_reset();

	void program_sr(int nChip, sr i_sr);
	void reset_assert(int nChip);
	void reset_deassert(int nChip);

	void bsd_assert(int nChip);
	void bsd_deassert(int nChip);

	void clkbuf_enable();
	void clkbuf_disable();

	void sel_daq_bs(int nChip, daq_bs daq_bs);
};

