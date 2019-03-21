#include "instr.h"

using namespace meas_croc::instr;

instr::instr()
{
	ViStatus viStatus;
	viStatus = viOpenDefaultRM(&viResourceManagerSession);
}


instr::~instr()
{
	if (bOpen)
		close();

	viClose(viResourceManagerSession);
}

bool instr::open(std::string instrResourceName) 
{
	this->instrResourceName = instrResourceName;
	ViStatus viStatus;
	viStatus = viOpen(viResourceManagerSession, (ViRsrc)(instrResourceName.c_str()), VI_NULL, VI_NULL, &viInstrumentSession);
	if (viStatus < VI_SUCCESS) 
		return false;

	this->bOpen = true;
	return true;
}

void instr::close() 
{
	if (bOpen) {
		viClose(viInstrumentSession);
		bOpen = false;
	}
}

int instr::write(std::string instrCommand)
{
	ViUInt32 nTransferred;
	ViStatus viStatus;
	viStatus = viWrite(viInstrumentSession, (ViBuf)(instrCommand.c_str()), instrCommand.size(), &nTransferred);
	return nTransferred;
}

std::string instr::read(int nBytes)
{
	std::unique_ptr<ViChar> pBuf{ new ViChar[nBytes] };
	ViUInt32 nTransferred;

	ViStatus viStatus;
	viStatus = viRead(viInstrumentSession, (ViBuf)pBuf.get(), nBytes, &nTransferred);

	return std::string{ pBuf.get(), nTransferred };
}

void meas_croc::instr::instr::reset()
{
	write("*RST\n");
}
