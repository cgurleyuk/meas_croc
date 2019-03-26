#include "tempctrl.h"

#include <iostream>

#include "vt4200.h"

double test_vt4200(std::vector<double> vPar)
{
	double t = vPar[0];
	meas_croc::instr::vt4200 vt4200;

	std::cout << "TEST: oven control" << std::endl;
	vt4200.set_temperature(t);

	return 0;
}