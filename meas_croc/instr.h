#pragma once

#include <string>

namespace meas_croc {
	namespace instr {

#include "visa.h"

		class instr
		{
		public:
			instr();
			~instr();

			bool open(std::string instrResourceName);
			void close();

			int write(std::string instrCommand);

			std::string read(int nBytes);

		private:
			ViSession viResourceManagerSession;
			ViSession viInstrumentSession;

			std::string instrResourceName;
			bool bOpen;
		};
	}
}

