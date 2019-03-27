#include <vector>

#include <sstream>
#include <iomanip>

#include "measurement.h"
#include "spi.h"
#include "sr.h"
#include "meas_log.h"

#include "agilent33622a.h"

#include "util.h"

double meas_whb_trim(std::vector<double> vPar)
{
	const std::string agilent33622a_rsc_name = "GPIB::10::INSTR";
	const std::string file_path = "D:\\cgurleyuk\\crocodile\\data\\meas_whb_trim";

	int n_s = pow(2, 21);

	bool has_meas_log = true;

	measurement meas;
	sr			sr;
	daq			daq;
	meas_croc::meas_log meas_log;

	meas_croc::instr::agilent33622a agilent33622a(agilent33622a_rsc_name);


	if (has_meas_log) {
		std::string meas_log_file_path = file_path + "\\meas_whb_trim.log";
		meas_log.set_file(meas_log_file_path);
	}

	// shut everything down to begin
	for (int n_chip : {0, 1, 2, 3})
	{
		sr.clear();
		meas.program_sr(n_chip, sr);
	}

	// setup frequency reference
	agilent33622a.setWaveform(meas_croc::instr::agilent33622a_waveform::square);
	agilent33622a.setFrequency(32e6);
	agilent33622a.setVoltage(3.3, 1.65);
	agilent33622a.setImpedance(meas_croc::instr::agilent33622a_impedance::hiz);

	std::vector<int> v_d = linspace(0, 15, 16);

	for (int n_chip : {0, 1, 2, 3})
	{
		std::stringstream ss;
		ss << "select chip " << n_chip;
		meas_log.write(ss.str());

		agilent33622a.outputEnable();

		for (int d : v_d)
		{
			sr.clear();
			sr.mod_enable(sr_mod::sr_mod_wh);
			sr.sel_bsc(sr_sel_bsc::sr_sel_bsc_wh);
			sr.mod_set_wh_trim(static_cast<uint8>(d));
			meas.program_sr(n_chip, sr);
			meas.sel_daq_bs(n_chip, daq_bs::daq_bsc);

			std::vector<uint8> bs;
			daq.initialize(n_s);
			bs = daq.read(n_s);

			std::stringstream ss_file_name;
			ss_file_name << "\\meas_whb_trim_chip" << std::setfill('0') << std::setw(2) << n_chip << "_d" << std::setw(2) << d << ".bin";
			bs_file f(file_path + ss_file_name.str());
			
			std::stringstream ss_d;
			ss_d << "d = " << d << ", mu = " << mean(bs);
			meas_log.write(ss_d.str());

			daq.clear();
			sr.clear();
			meas.program_sr(n_chip, sr);
		}

		agilent33622a.outputDisable();
	}

	return 0;
}