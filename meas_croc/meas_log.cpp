#include "meas_log.h"

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

meas_croc::meas_log::meas_log()
{
	has_file = false;
}


meas_croc::meas_log::~meas_log()
{
	if (has_file)
		f.close();
}

void meas_croc::meas_log::set_file(std::string file_name)
{
	f.open(file_name, std::ios::out);
	has_file = true;
}

void meas_croc::meas_log::write(std::string text)
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::stringstream ss;
	ss << "[" << std::put_time(std::localtime(&t), "%Y%m%d %X") << "] "  << text << std::endl;

	std::string str = ss.str();
	std::cout << ss.str();
	if (has_file) {
		f.write(str.c_str(), str.size());
		f.flush();
	}
}

