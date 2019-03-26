#include "measurement.h"
#include "spi.h"

#include "agilent53230a.h"

#include <sstream>
#include <iomanip>

extern spi mainSPI;

double meas_dco(std::vector<double> vPar)
{
	measurement meas;
	sr			sr;

	mainSPI.debug = false;

	meas_croc::instr::agilent53230a agilent53230a("GPIB::3::INSTR");

	sr.clear();
	for (int i = 0; i < 4; i++)
		meas.program_sr(0, sr);

	agilent53230a.reset();
	agilent53230a.configureMeas(meas_croc::instr::agilent53230a_meas::frequency);
	agilent53230a.setGateTime(1.0);

	int nChip = 0;
	double f = 0;

	meas.clkbuf_enable();
	for (int nChip : {3})
	{
		std::cout << "measuring chip " << nChip << std::endl;
		for (int nD = 0; nD < 32; nD++)
		{
			sr.clear();
			sr.dco_enable();
			sr.dco_set_cs(static_cast<uint8>(nD));

			meas.program_sr(nChip, sr);

			for (int nB : {0, 1})
			{
				if (nB == 1)
					meas.bsd_assert(nChip);
				else
					meas.bsd_deassert(nChip);

				f = agilent53230a.readMeas();

				std::cout << "    nd = " << std::hex << std::setw(2) << std::setfill('0') << nD << std::dec << ", bsd = " << nB << ", f = " << f << std::endl;
			}
		}
		sr.clear();
		meas.program_sr(nChip, sr);
	}

	meas.clkbuf_disable();

	return 0;
}
