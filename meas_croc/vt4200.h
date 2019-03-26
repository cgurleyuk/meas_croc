#pragma once

#include <windows.h>

#include <string>

namespace meas_croc
{
	namespace instr {
		class vt4200
		{
		public:
			vt4200();
			~vt4200();

			void set_temperature(double t);

			bool debug;
		private:
			void write_string(std::string s);

			HANDLE hPort;
		};
	}
}

