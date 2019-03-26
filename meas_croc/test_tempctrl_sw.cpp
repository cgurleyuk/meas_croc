#include "tempctrl.h"

#include <iostream>

template <typename T>
std::vector<T> linspace(T a, T b, size_t n) {
	T h = (b - a) / static_cast<T>(n - 1);
	std::vector<T> xs(n);
	typename std::vector<T>::iterator x;
	T val;
	for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h)
		*x = val;
	return xs;
}

double test_tempctrl_sw(std::vector<double> vPar)
{
	const std::string keithley_rsc_name = "GPIB::6::INSTR";
	const std::string log_file_path = "D:\\cgurleyuk\\crocodile\\data\\test_tempctrl_sw\\tmpctrl.bin";

	std::vector<double> v_T = linspace(25.0, 35.0, 2);

	meas_croc::tempctrl tempctrl(keithley_rsc_name);
	std::cout << "TEST: temperature control sweep" << std::endl;

	tempctrl.set_debug();
	tempctrl.dT_tgt = 5e-3;
	tempctrl.dT_oven_tgt = 1;
	tempctrl.n_stb_tgt = 100;
	tempctrl.create_log_file(log_file_path);

	for (double T_tgt : v_T)
	{
		tempctrl.stabilize(T_tgt);
	}

	return 0;
}