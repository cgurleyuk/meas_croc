#include "tempctrl.h"

#include <thread>
#include <chrono>

#include <iostream>
#include <iomanip>

#include <chrono>

meas_croc::tempctrl::tempctrl(std::string keithley_rsc_name = "GPIB::6::INSTR")
	: keithley2002(keithley_rsc_name), vt4200(), has_log(false)
{
	v_coef.push_back(-2.463409E+2);
	v_coef.push_back(2.381250E+0);
	v_coef.push_back(7.457609E-4);
	v_coef.push_back(8.028406E-7);

	keithley2002.initialize();
	std::this_thread::sleep_for(std::chrono::seconds(1));

	n_stb_tgt	= 300;
	dT_tgt		= 5e-3;
	dT_oven_tgt = 1;
}

meas_croc::tempctrl::~tempctrl()
{
	if (has_log)
		log_file.close();
}

double meas_croc::tempctrl::get_pt100_temperature()
{
	double r = keithley2002.measure(); 
	return v_coef[0] + v_coef[1]*r + v_coef[2]*pow(r, 2) + v_coef[3]*pow(r, 3);
}

void meas_croc::tempctrl::create_log_file(std::string file_name)
{
	log_file.open(file_name.c_str(), std::ios::out | std::ios::binary);
	has_log = true;
}

void meas_croc::tempctrl::stabilize(double T)
{
	int		n_stb	= 0;
	double	T_prev	= 0;

	vt4200.set_temperature(T);

	if (debug)
		std::cout << "oven set to " << T << std::endl;

	while (n_stb < n_stb_tgt)
	{
		double T_cur = get_pt100_temperature();

		double dT		= T_cur - T_prev;
		double dT_oven	= T_cur - T;

		if (has_log) {
			std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			log_file.write(reinterpret_cast<char*>(&t), sizeof(t));
			log_file.write(reinterpret_cast<char*>(&T_cur), sizeof(T_cur));
		}
			

		T_prev = T_cur;

		if ((abs(dT) < dT_tgt) && (abs(dT_oven) < dT_oven_tgt))
			n_stb++;
		else
			n_stb = 0;

		if (debug)
			std::cout << "T_cur = " << std::fixed << std::setw(4) << std::setfill('0') << T_cur << ", dT = " << std::scientific << std::setprecision(4) << dT << ", n_stb = " << std::dec << n_stb << std::endl;
	}

	if (debug)
		std::cout << "oven stable!" << std::endl;

	if (has_log)
		log_file.flush();
}

void meas_croc::tempctrl::set_debug()
{
	debug = true;
	// vt4200.debug = true;
}
