#pragma once

#include <vector>

#include "NIDAQmx.h"

typedef unsigned char uint8;

class daq
{
public:
	daq();
	~daq();

	void initialize(unsigned int nSamples);
	std::vector<uint8> read(unsigned int nSamples);
	void clear();
	std::string error(int errorCode);

private:
	TaskHandle taskHandle;
	static const double sampleRate;
};

