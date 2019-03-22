#include "measurement.h"

#include "agilent33622a.h"

#include <sstream>
#include <iomanip>

double computeAverage(std::vector<uint8> &v);

double meas_fsw(std::vector<double> vPar)
{
	unsigned int nS = static_cast<unsigned int>(vPar[0]);;
	const std::string filePath = "D:\\cgurleyuk\\crocodile\\data\\meas_fsw\\";
	
	meas_croc::instr::agilent33622a wfmGen("GPIB::10::INSTR");
	wfmGen.setWaveform(meas_croc::instr::agilent33622a_waveform::square);
	wfmGen.setFrequency(32e6);
	wfmGen.setVoltage(3.3, 1.65);
	wfmGen.setImpedance(meas_croc::instr::agilent33622a_impedance::hiz);
	wfmGen.outputEnable();

	measurement meas;
	sr			sr;
	daq			daq;

	std::vector<uint8> bs;

	std::stringstream ssFilename;

	const double freqMax = 40e6;
	const double freqMin = 24e6;
	const double nFreqSweep = 17;
	std::vector<double> freqList;

	double freqStep = (freqMax - freqMin) / (nFreqSweep - 1);

	sr.clear();
	meas.program_sr(0, sr);
	meas.program_sr(1, sr);
	meas.program_sr(2, sr);
	meas.program_sr(3, sr);
	for (int nFreq = 0; nFreq < nFreqSweep; nFreq++) {
		freqList.push_back(nFreq*freqStep + freqMin);

		std::cout << "setting frequency to " << freqList[nFreq] << std::endl;
		wfmGen.setFrequency(freqList[nFreq]);
		for (int nChip : {0, 1, 2, 3}) {
			std::cout << "select chip " << nChip << std::endl;
			for (int nMod : {0, 1, 2, 3, 4})
			{
				switch (nMod)
				{
				case 0:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_pp);
					meas.program_sr(nChip, sr);
					meas.sel_daq_bs(nChip, daq_bs::daq_bsa);
					break;
				case 1:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_sp);
					sr.sel_bsa(sr_sel_bsa::sr_sel_bsa_sp);
					meas.program_sr(nChip, sr);
					meas.sel_daq_bs(nChip, daq_bs::daq_bsa);
					break;
				case 2:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_nd);
					sr.sel_bsa(sr_sel_bsa::sr_sel_bsa_nd);
					meas.program_sr(nChip, sr);
					meas.sel_daq_bs(nChip, daq_bs::daq_bsa);
					break;
				case 3:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_hr);
					sr.sel_bsa(sr_sel_bsa::sr_sel_bsa_hr);
					meas.program_sr(nChip, sr);
					meas.sel_daq_bs(nChip, daq_bs::daq_bsa);
					break;
				case 4:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_wh);
					sr.sel_bsc(sr_sel_bsc::sr_sel_bsc_wh);
					meas.program_sr(nChip, sr);
					meas.sel_daq_bs(nChip, daq_bs::daq_bsc);
					break;
				default:
					break;
				}

				std::cout << "    capturing modulator " << nMod << std::endl;
				daq.initialize(nS);
				bs = daq.read(nS);
				std::cout << "        mu = " << computeAverage(bs) << std::endl;
				std::stringstream ssFilename;
				ssFilename << "meas_fsw_chip"<< std::setfill('0') << std::setw(2) << nChip << "_mod" << std::setfill('0') << std::setw(2) << nMod << "_freq" << std::setw(2) << nFreq << ".bin";
				bs_file f(filePath + ssFilename.str());
				f.write_bs(bs);
				daq.clear();

				sr.clear();
				meas.program_sr(nChip, sr);
			}
		}
	}

	wfmGen.outputDisable();
	//daq.clear();
	return 0;
}

double computeAverage(std::vector<uint8> &v)
{
	double sum = 0;

	for (uint8 i : v)
	{
		sum = sum + static_cast<double>(i);
	}

	return sum / static_cast<double>(v.size());
}