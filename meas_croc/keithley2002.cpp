#include "keithley2002.h"



meas_croc::instr::keithley2002::keithley2002()
{
}

meas_croc::instr::keithley2002::keithley2002(std::string instrResourceName)
{
	this->instrResourceName = instrResourceName;
	open(instrResourceName);
}


meas_croc::instr::keithley2002::~keithley2002()
{
}

void meas_croc::instr::keithley2002::initialize()
{
	reset();
	write(":INIT:CONT OFF;\n");
	write(":ROUT:OPEN:ALL;\n");
	write(":ROUT:CLOS (@2);\n");
	//write(":FRES:NPLC 20;\n");
	write(":FRES:DIG 8.5;\n");
	write(":FRES:OCOM ON;\n");
	write(":FUNC 'FRES';");
}

double meas_croc::instr::keithley2002::read()
{
	write(":READ?;\n");
	std::string s = read(32);
	return atof(s.c_str());
}
