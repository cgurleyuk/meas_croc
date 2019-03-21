#pragma once
#include <string>

#include "instr.h"

namespace meas_croc {
	namespace instr {
		enum agilent53230_channel {
			ch1 = 1,
			ch2 = 2
		};

		enum agilent53230a_meas {
			frequency,
			period,
			p_duty_cycle,
			n_duty_cycle
		};
		class agilent53230a : public instr
		{
		public:
			agilent53230a();
			agilent53230a(std::string instrResourceName);
			~agilent53230a();
		
			void configureMeas(agilent53230a_meas meas, agilent53230_channel channel = ch1);
			void setGateTime(double gateTime);
			double readMeas();

			std::string channelToString(agilent53230_channel channel);
			std::string measToString(agilent53230a_meas meas);
		};
	}
}

