#pragma once

#include "instr.h"

#include <string>

namespace meas_croc {
	namespace instr {

		enum agilent33622a_waveform {
			square,
			sine
		};

		enum agilent33622a_channel {
			agilent33622a_ch1 = 1,
			agilent33622a_ch2 = 2
		};

		enum agilent33622a_impedance {
			hiz,
			ohm50
		};

		class agilent33622a : public instr
		{
		public:
			agilent33622a();
			agilent33622a(std::string instrResourceName);
			~agilent33622a();

			void outputEnable(agilent33622a_channel channel = agilent33622a_channel::agilent33622a_ch1);
			void outputDisable(agilent33622a_channel channel = agilent33622a_channel::agilent33622a_ch1);

			void setImpedance(agilent33622a_impedance impedance, agilent33622a_channel channel = agilent33622a_channel::agilent33622a_ch1);
			void setWaveform(agilent33622a_waveform waveform, agilent33622a_channel channel = agilent33622a_channel::agilent33622a_ch1);
			void setVoltage(double vpp, double voff, agilent33622a_channel channel = agilent33622a_channel::agilent33622a_ch1);
			void setFrequency(double freq, agilent33622a_channel channel = agilent33622a_channel::agilent33622a_ch1);

			std::string waveformToString(agilent33622a_waveform waveform);
			std::string impedanceToString(agilent33622a_impedance impedance);
		};
	} 
}

