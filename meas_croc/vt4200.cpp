#include "vt4200.h"

#include <iostream>

#include <sstream>
#include <iomanip>

#include <iostream>

meas_croc::instr::vt4200::vt4200()
{
	hPort = CreateFile("\\COM1", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DCB dcb;
	dcb.DCBlength	= sizeof(dcb);
	dcb.BaudRate	= CBR_9600;
	dcb.ByteSize	= 8;
	dcb.Parity		= NOPARITY;
	dcb.StopBits	= ONESTOPBIT;
	SetCommState(hPort, &dcb);
}


meas_croc::instr::vt4200::~vt4200()
{
	CloseHandle(hPort);
}

void meas_croc::instr::vt4200::set_temperature(double t)
{
	std::stringstream ss;

	ss << "$00E ";

	if (t < 0)
		ss << "-";
		
	ss<< std::fixed << std::setw(6) << std::setfill('0')  << std::setprecision(1) << abs(t) << " 0000.0 0000.0 0000.0 0000.0 0000.0 0000.0 " << "11111111111111111111111111111111\r\n";
	
	if (debug)
		std::cout << ss.str() << std::endl;

	write_string(ss.str());
}

void meas_croc::instr::vt4200::write_string(std::string s)
{
	DWORD nWritten;
	WriteFile(hPort, s.c_str(), s.size(), &nWritten, NULL);
}
