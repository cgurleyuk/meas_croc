#include "measurement.h"
#include "meas.h"

#include <iostream>

double meas_reset_fpga(std::vector<double> vPar)
{
	measurement meas;

	mainSPI.reset();
	std::cout << "FPGA reset" << std::endl;
	//mainSPI.write(0x00, 0x00);
	//mainSPI.write(0x01, 0x80);
	//mainSPI.write(0x0e, 0x1f);


	return 0;
}