#include "test.h"

#include "keithley2002.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

double test_keithley2002(std::vector<double> vPar) 
{
	meas_croc::instr::keithley2002 multimeter("GPIB::6::INSTR");
	multimeter.initialize();
	std::cout << "keithley2002: initialize." << std::endl;
	std::this_thread::sleep_for (std::chrono::seconds(1));
	std::cout << "keithley2002: read." << std::endl;
	return multimeter.measure();
}