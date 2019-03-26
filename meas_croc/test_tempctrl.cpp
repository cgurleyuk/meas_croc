#include "tempctrl.h"

#include <iostream>

double test_tempctrl(std::vector<double> vPar)
{
	const std::string keithley_rsc_name = "GPIB::6::INSTR";
	const std::string log_file_path = "D:\\cgurleyuk\\crocodile\\data\\test_tempctrl\\tmpctrl.bin";
	double T_tgt = 0;
	
	if (vPar.size() < 1)
		return -1;
	else
		T_tgt = vPar[0];

	meas_croc::tempctrl tempctrl(keithley_rsc_name);
	std::cout << "TEST: temperature control, target T = " << T_tgt << std::endl;

	tempctrl.debug		= true;

	tempctrl.dT_tgt			= 5e-3;
	tempctrl.dT_oven_tgt	= 1;
	tempctrl.n_stb_tgt		= 50;

	tempctrl.create_log_file(log_file_path);
	tempctrl.stabilize(T_tgt);

	return 0;
}