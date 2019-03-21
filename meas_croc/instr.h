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

			void reset();
		protected:
			std::string instrResourceName;
			bool bOpen;
		private:
			ViSession viResourceManagerSession;
			ViSession viInstrumentSession;			
		};
	}
}

