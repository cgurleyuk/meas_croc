#pragma once

#include <fstream>
namespace meas_croc {
	class meas_log
	{
	public:
		meas_log();
		~meas_log();

		void set_file(std::string file_name);
		void write(std::string t);

	private:
		bool has_file;

		std::fstream f;
	};
}

