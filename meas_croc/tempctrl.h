#pragma once

#include "test.h"

#include "keithley2002.h"
#include "vt4200.h"

#include <vector>
#include <fstream>

namespace meas_croc
{
	class tempctrl
	{
	public:
		//tempctrl();
		tempctrl(std::string keithley2002_rsc_name);
		~tempctrl();

		double	get_oven_temperature();
		double	get_pt100_temperature();

		void	create_log_file(std::string file_name);

		void	stabilize(double T);

		void	set_debug();

		bool	debug;
		int		n_stb_tgt;

		double	dT_tgt;
		double  dT_oven_tgt;
	private:
		instr::keithley2002 keithley2002;
		instr::vt4200		vt4200;
		
		bool				has_log;

		std::vector<double> v_coef;

		std::fstream		log_file;
	};
}

