#include "util.h"

#include "measurement.h"
#include "spi.h"
#include "sr.h"

#include "agilent53230a.h"
#include "agilent33622a.h"

#include "tempctrl.h"
#include "meas_log.h"

#include <sstream>
#include <iomanip>

#include <fstream>

extern spi mainSPI;

double meas_tsw(std::vector<double> vPar)
{
	const std::string keithley2002_rsc_name = "GPIB::6::INSTR";
	const std::string agilent53230a_rsc_name = "GPIB::3::INSTR";
	const std::string agilent33622a_rsc_name = "GPIB::10::INSTR";

	const std::string file_path = "D:\\cgurleyuk\\crocodile\\data\\meas_tsw";

	bool has_meas_log = true;
	bool is_fake_run = false;

	unsigned int n_s = pow(2, 21);

	measurement meas;
	sr			sr;
	daq			daq;

	// instruments
	meas_croc::instr::agilent53230a agilent53230a(agilent53230a_rsc_name);
	meas_croc::instr::agilent33622a agilent33622a(agilent33622a_rsc_name);
	meas_croc::tempctrl tempctrl(keithley2002_rsc_name);

	// measurement log file
	meas_croc::meas_log meas_log;

	if (has_meas_log) {
		std::string meas_log_file_path = file_path + "\\meas_tsw.log";
		meas_log.set_file(meas_log_file_path);
	}

	// frequency sweep file
	std::ofstream f_freq;
	f_freq.open(file_path + "\\meas_freq.bin", std::ios::out | std::ios::binary);

	std::vector<double> v_T = linspace(-65.0, 135.0, 21);

	tempctrl.set_debug();
	tempctrl.dT_tgt = 3e-3;
	tempctrl.dT_oven_tgt = 1;
	tempctrl.n_stb_tgt = 300;
	tempctrl.create_log_file(file_path + "\\tempctrl.bin");

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

	// setup frequency counter
	agilent53230a.reset();
	agilent53230a.configureMeas(meas_croc::instr::agilent53230a_meas::frequency);
	agilent53230a.setGateTime(1.0);

	meas_log.write("MEAS: meas_tsw");
	for (unsigned int n_T = 0; n_T < v_T.size(); n_T++)
	{
		double T_tgt = v_T[n_T];

		if (is_fake_run) 
		{
			std::stringstream ss;
			ss << "TEMPCTRL: (FAKE RUN) stabilized to " << T_tgt;
			meas_log.write(ss.str());
		}
		else
		{
			tempctrl.stabilize(T_tgt);
			std::stringstream ss;
			ss << "TEMPCTRL: stabilized to " << T_tgt;
			meas_log.write(ss.str());
		}
		
		
		for (int n_chip : {0}) {
			std::stringstream ss;
			ss << "select chip " << n_chip;
			meas_log.write(ss.str());

			agilent33622a.outputEnable();

			for (int n_mod : {0, 1, 2, 3, 4})
			{
				switch (n_mod)
				{
				case 0:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_pp);
					meas.program_sr(n_chip, sr);
					meas.sel_daq_bs(n_chip, daq_bs::daq_bsa);
					break;
				case 1:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_sp);
					sr.sel_bsa(sr_sel_bsa::sr_sel_bsa_sp);
					meas.program_sr(n_chip, sr);
					meas.sel_daq_bs(n_chip, daq_bs::daq_bsa);
					break;
				case 2:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_nd);
					sr.sel_bsa(sr_sel_bsa::sr_sel_bsa_nd);
					sr.mod_set_ph_ref_1(sr_mod::sr_mod_nd, 0x17);
					sr.mod_set_ph_ref_0(sr_mod::sr_mod_nd, 0x0F);
					meas.program_sr(n_chip, sr);
					meas.sel_daq_bs(n_chip, daq_bs::daq_bsa);
					break;
				case 3:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_hr);
					sr.sel_bsa(sr_sel_bsa::sr_sel_bsa_hr);
					meas.program_sr(n_chip, sr);
					meas.sel_daq_bs(n_chip, daq_bs::daq_bsa);
					break;
				case 4:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_wh);
					sr.sel_bsc(sr_sel_bsc::sr_sel_bsc_wh);
					meas.program_sr(n_chip, sr);
					meas.sel_daq_bs(n_chip, daq_bs::daq_bsc);
					break;
				case 5:
					sr.clear();
					sr.mod_enable(sr_mod::sr_mod_pp);
					sr.sel_bsc(sr_sel_bsc::sr_sel_bsc_pp);
					meas.program_sr(n_chip, sr);
					meas.sel_daq_bs(n_chip, daq_bs::daq_bsc);
				default:
					break;
				}

				double T_begin = tempctrl.get_pt100_temperature();
				std::vector<uint8> bs;
				daq.initialize(n_s);
				bs = daq.read(n_s);
				double T_end = tempctrl.get_pt100_temperature();

				std::stringstream ss_file_name;
				ss_file_name << "\\meas_tsw_chip" << std::setfill('0') << std::setw(2) << n_chip << "_mod" << std::setfill('0') << std::setw(2) << n_mod << "_temp" << std::setw(2) << n_T << ".bin";
				bs_file f(file_path + ss_file_name.str());
				f.write_bs(bs, T_begin, T_end);

				std::stringstream ss_mod;
				ss_mod << "mod = " << n_mod << ", T_begin = " << T_begin << ", T_end = " << T_end << ", mu = " << mean(bs);
				meas_log.write(ss_mod.str());

				daq.clear();
				sr.clear();
				meas.program_sr(n_chip, sr);
			}
			agilent33622a.outputDisable();
			
			meas.clkbuf_enable();

			for (int n_d = 0; n_d < 32; n_d++)
			{
				sr.clear();
				sr.dco_enable();
				sr.dco_set_cs(static_cast<uint8>(n_d));
				meas.program_sr(n_chip, sr);

				for (int n_b : {0, 1})
				{
					if (n_b == 1)
						meas.bsd_assert(n_chip);
					else
						meas.bsd_deassert(n_chip);

					double f = agilent53230a.readMeas();

					std::stringstream ss_dco;
					ss_dco << "n_d = " << std::hex << std::setw(2) << std::setfill('0') << n_d << std::dec << ", bsd = " << n_b << ", f = " << f;
					meas_log.write(ss_dco.str());

					f_freq.write(reinterpret_cast<const char*>(&f), sizeof(f));
					f_freq.flush();
				}

				sr.clear();
				meas.program_sr(n_chip, sr);
			}

			meas.clkbuf_disable();
			
		}
	}

	f_freq.close();

	return 0;
}