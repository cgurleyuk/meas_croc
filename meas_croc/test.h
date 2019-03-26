#pragma once

#include <vector>

double test_sr(std::vector<double> vPar);
double test_daq(std::vector<double> vPar);
double test_bs_file(std::vector<double> vPar);
double test_meas(std::vector<double> vPar);
double test_instr(std::vector<double> vPar);

// disconnect all outputs from the instrument before running this test
double test_agilent33622a(std::vector<double> vPar);
// connect channel 1 of 33622a to channel 1 of 53230a
double test_agilent53230a(std::vector<double> vPar);
double test_keithley2002(std::vector<double> vPar);

double test_tempctrl_sw(std::vector<double> vPar);
double test_tempctrl(std::vector<double> vPar);
double test_vt4200(std::vector<double> vPar);
