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
	close();
}

void meas_croc::instr::keithley2002::initialize()
{
	reset();
	write(":INIT:CONT OFF;");
	write(":ROUT:OPEN:ALL;");
	write(":ROUT:CLOS (@1);");
	write(":FRES:NPLC 20;");
	write(":FRES:DIG 8.5;");
	write(":FRES:OCOM ON;");
	write(":FUNC 'FRES';");
}

double meas_croc::instr::keithley2002::measure()
{
	write(":INIT;");

	bool measStatus = false;
	while (!measStatus) {
		write(":STAT:MEAS?");
		std::string statusString = read(3);
		int status = atoi(statusString.c_str());

		if (((status & 0x20) >> 5 == 1))
			measStatus = true;
	}

	write(":FETCH?");
	std::string s = read(32);
	return atof(s.c_str());
}
