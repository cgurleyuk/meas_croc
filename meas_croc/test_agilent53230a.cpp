#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "agilent53230a.h"
#include "agilent33622a.h"

double test_agilent53230a(std::vector<double> vPar)
{
	meas_croc::instr::agilent33622a wfmGen("GPIB::10::INSTR");
	meas_croc::instr::agilent53230a freqCounter("GPIB::3::INSTR");

	wfmGen.reset();
	std::cout << "agilent33622a: reset." << std::endl;
	freqCounter.reset();
	std::cout << "agilent53230a: reset." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	freqCounter.configureMeas(meas_croc::instr::agilent53230a_meas::frequency);
	freqCounter.setGateTime(1.0);
	std::cout << "agilent53230a: configured." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	wfmGen.setWaveform(meas_croc::instr::agilent33622a_waveform::square);
	wfmGen.setFrequency(32e6);
	wfmGen.setVoltage(3.3/2, 1.65/2);
	wfmGen.setImpedance(meas_croc::instr::agilent33622a_impedance::hiz);
	wfmGen.outputEnable();
	std::cout << "agilent33622a: enabled output." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	double freq = freqCounter.readMeas();
	std::cout << "agilent53230a: measurement read." << std::endl;

	return freq;
}