#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iostream>

#include "interp.h"
#include "spi.h"

#include "test.h"

spi mainSPI;

int main(int argc, char* argv[]) {
	//spi			mySPI;
	interp	interp;

	interp.register_func("spi_w", &main_spi_write);
	interp.register_func("spi_r", &main_spi_read);
	interp.register_func("spi_dump_fpga", &main_spi_dump_fpga);

	interp.register_func("test_crocodile", &test_crocodile);

	interp.loop();
	return 0;
}