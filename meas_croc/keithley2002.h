#pragma once

#include "instr.h"

#include <string>

namespace meas_croc {
	namespace instr {
		class keithley2002 : public instr
		{
		public:
			keithley2002();
			keithley2002(std::string instrResourceName);
			~keithley2002();

			void initialize();
			double measure();
		};
	}
}