#include "measurement.h"

#include <sstream>
#include <iomanip>

double test_meas(std::vector<double> vPar)
{
	unsigned int nS = static_cast<unsigned int>(vPar[0]);
	const std::string filePath = "D:\\cgurleyuk\\crocodile\\data\\test_meas\\";

	std::vector<uint8> bs;

	measurement meas;
	sr			sr;
	daq			daq;
	
	daq.initialize(nS);

	// turn off everything
	sr.clear();
	meas.program_sr(0, sr);

	std::string chStr;
	for (int nCh = 0; nCh < 3; nCh = nCh + 1)
	{
		for (int nMod = 0; nMod < 4; nMod = nMod + 1)
		{
			sr.clear();
			if ((nCh == 2) && (nMod == 2))
				sr.mod_enable(sr_mod::sr_mod_wh);
			else
				sr.mod_enable(static_cast<sr_mod>(nMod));

			switch (nCh)
			{
			case 0:
				sr.sel_bsa(static_cast<sr_sel_bsa>(nMod));
				chStr = "bsa";
				break;
			case 1:
				sr.sel_bsb(static_cast<sr_sel_bsb>(nMod));
				chStr = "bsb";
				break;
			case 2:
				sr.sel_bsc(static_cast<sr_sel_bsc>(nMod));
				chStr = "bsc";
				break;
			}

			meas.program_sr(0, sr);
			meas.sel_daq_bs(0, static_cast<daq_bs>(nCh));
			
			bs = daq.read(nS);
			std::stringstream ss;
			ss << "test_meas_"<< chStr << "_chip" << std::setfill('0') << std::setw(2) << 0 << "_mod" << std::setfill('0') << std::setw(2) << nMod << ".bin";
			bs_file f(filePath + ss.str());
			f.write_bs(bs);

			std::cout << "captured " << static_cast<unsigned>(bs.size()) << " samples, wrote to " << ss.str() << std::endl;
		}
	}

	daq.clear();
	return 0;
}