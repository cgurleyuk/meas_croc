#include "agilent53230a.h"

#include <sstream>

#include <iostream>

meas_croc::instr::agilent53230a::agilent53230a()
{
}

meas_croc::instr::agilent53230a::agilent53230a(std::string instrResourceName)
{
	this->instrResourceName = instrResourceName;
	open(instrResourceName);
}


meas_croc::instr::agilent53230a::~agilent53230a()
{
}

void meas_croc::instr::agilent53230a::configureMeas(agilent53230a_meas meas, agilent53230_channel channel)
{
	std::stringstream ss;
	ss << ":CONF:" << measToString(meas) /*<< " ," << channelToString(channel)*/ << ";" << std::endl;

	write(ss.str());
}

void meas_croc::instr::agilent53230a::setGateTime(double gateTime)
{
	write(":FREQ:GATE:SOUR TIME;\n");
	std::stringstream ss;
	ss << ":FREQ:GATE:TIME " << std::scientific << gateTime << ";" << std::endl;
	write(ss.str());
}

double meas_croc::instr::agilent53230a::readMeas()
{
	write(":READ?;\n");
	std::string s = read(32);

	std::cout << "agilent53230a sent: " << s << std::endl;
	return atof(s.c_str());
}

std::string meas_croc::instr::agilent53230a::channelToString(agilent53230_channel channel)
{
	switch (channel)
	{
	case meas_croc::instr::ch1:
		return std::string("@1");
		break;
	case meas_croc::instr::ch2:
		return std::string("@2");
		break;
	default:
		return std::string("@1");
		break;
	}
}

std::string meas_croc::instr::agilent53230a::measToString(agilent53230a_meas meas)
{
	switch (meas)
	{
	case meas_croc::instr::frequency:
		return std::string("FREQ");
		break;
	case meas_croc::instr::period:
		return std::string("PER");
		break;
	case meas_croc::instr::p_duty_cycle:
		return std::string("PDUT");
		break;
	case meas_croc::instr::n_duty_cycle:
		return std::string("NDUT");
		break;
	default:
		break;
	}
	return std::string();
}
