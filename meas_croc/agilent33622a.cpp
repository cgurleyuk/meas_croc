#include "agilent33622a.h"

#include <sstream>

meas_croc::instr::agilent33622a::agilent33622a()
{
}

meas_croc::instr::agilent33622a::agilent33622a(std::string instrResourceName)
{
	this->instrResourceName = instrResourceName;
	open(this->instrResourceName);
}


meas_croc::instr::agilent33622a::~agilent33622a()
{
}

void meas_croc::instr::agilent33622a::outputEnable(agilent33622a_channel channel)
{
	std::stringstream ss;
	ss << ":OUTP" << channel << " 1" << std::endl;
	write(ss.str());
}

void meas_croc::instr::agilent33622a::outputDisable(agilent33622a_channel channel)
{
	std::stringstream ss;
	ss << ":OUTP" << channel << " 0" << std::endl;
	write(ss.str());
}

void meas_croc::instr::agilent33622a::setImpedance(agilent33622a_impedance impedance, agilent33622a_channel channel)
{
	std::stringstream ss;
	ss << ":OUTP" << channel << ":LOAD " << impedanceToString(impedance) << std::endl;
	write(ss.str());
}

void meas_croc::instr::agilent33622a::setWaveform(agilent33622a_waveform waveform, agilent33622a_channel channel)
{
	std::stringstream ss;
	ss << ":SOUR" << channel << ":FUNC " << waveformToString(waveform) << std::endl;
	write(ss.str());
}

void meas_croc::instr::agilent33622a::setVoltage(double vpp, double voff, agilent33622a_channel channel)
{
	std::stringstream ss;
	ss << ":SOUR" << channel << ":VOLT " << std::scientific << vpp << std::endl;
	write(ss.str());

	ss.clear();
	ss << ":SOUR" << channel << ":VOLT:OFFSET " << std::scientific << voff << std::endl;
	write(ss.str());
}

void meas_croc::instr::agilent33622a::setFrequency(double freq, agilent33622a_channel channel)
{
	std::stringstream ss;
	ss << ":SOUR" << channel << ":FREQ " << std::scientific << freq << std::endl;
	write(ss.str());
}

std::string meas_croc::instr::agilent33622a::waveformToString(agilent33622a_waveform waveform)
{
	switch (waveform)
	{
	case meas_croc::instr::square:
		return std::string("SQU");
		break;
	case meas_croc::instr::sine:
		return std::string("SIN");
		break;
	default:
		return std::string("SQU");
		break;
	}
}

std::string meas_croc::instr::agilent33622a::impedanceToString(agilent33622a_impedance impedance)
{
	switch (impedance)
	{
	case meas_croc::instr::hiz:
		return std::string("INF");
		break;
	case meas_croc::instr::ohm50:
		return std::string("50");
		break;
	default:
		return std::string("INF");
		break;
	}
}
