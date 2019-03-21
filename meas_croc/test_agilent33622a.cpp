#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "agilent33622a.h"

double test_agilent33622a(std::vector<double> vPar)
{
	meas_croc::instr::agilent33622a wfmGen("GPIB::10::INSTR");
	std::cout << "agilent33622a: reset." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	wfmGen.setWaveform(meas_croc::instr::agilent33622a_waveform::square);
	wfmGen.setFrequency(32e6);
	wfmGen.setVoltage(3.3, 1.65);
	wfmGen.setImpedance(meas_croc::instr::agilent33622a_impedance::hiz);

	std::cout << "agilent33622a: enabled output." << std::endl;
	wfmGen.outputEnable();
	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "agilent33622a: disabled output." << std::endl;
	wfmGen.outputDisable();
	return 0;
}