#include "daq.h"

#include <memory>
#include <iostream>
#include <string>

const double daq::sampleRate = 5e5;

daq::daq()
{
}

daq::~daq()
{
}

void daq::initialize(unsigned int nSamples)
{
	int err;
	err = DAQmxCreateTask("readbs", &taskHandle);
	if (err) std::cout << "daq error: " << error(err) << std::endl;
	err = DAQmxCreateDIChan(taskHandle, "Dev1/port0/line0", "d0", DAQmx_Val_ChanForAllLines);
	if (err) std::cout << "daq error: " << error(err) << std::endl;
	err = DAQmxCfgSampClkTiming(taskHandle, "PFI5", sampleRate, DAQmx_Val_Falling, DAQmx_Val_FiniteSamps, nSamples);
	if (err) std::cout << "daq error: " << error(err) << std::endl;
	DAQmxTaskControl(taskHandle, DAQmx_Val_Task_Commit);
	if (err) std::cout << "daq error: " << error(err) << std::endl;
}

std::vector<uint8> daq::read(unsigned int nSamples)
{
	std::unique_ptr<uInt8[]> data{ new uInt8[nSamples] };

	int32 nSamplesRead = 0;
	int32 nBits = 0;

	DAQmxStartTask(taskHandle);
	DAQmxReadDigitalLines(taskHandle, nSamples, nSamples/sampleRate*2, DAQmx_Val_GroupByChannel, data.get(), nSamples * sizeof(uInt8), &nSamplesRead, &nBits, nullptr);
	DAQmxStopTask(taskHandle);

	std::vector<uint8> vData{ data.get(), data.get() + sizeof(uInt8)*nSamples };

	return vData;
}


void daq::clear()
{
	DAQmxClearTask(taskHandle);
}

std::string daq::error(int errorCode)
{
	int nChars = DAQmxGetErrorString(errorCode, nullptr, 0);
	std::unique_ptr<char[]> errorString{new char[nChars]};

	DAQmxGetErrorString(errorCode, errorString.get(), nChars);

	return std::string(errorString.get());
}