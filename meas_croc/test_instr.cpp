#include <vector>
#include <string>
#include <iostream>

#include "instr.h"

using namespace meas_croc;

double test_instr(std::vector<double> vPar)
{
	instr::instr testInstr;
	testInstr.open("GPIB::3::INSTR");
	testInstr.write("*IDN?\n");

	std::string sRead = testInstr.read(256);

	std::cout << sRead << std::endl;

	return 0;
}