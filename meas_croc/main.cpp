#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iostream>

//#include "spi.h"
#include "interp.h"

#include "spi.h"

spi mainSPI;

int main(int argc, char* argv[]) {
	//spi			mySPI;
	interp	interp;

	interp.register_func("spi_w", &main_spi_write);
	interp.register_func("spi_r", &main_spi_read);
	interp.register_func("dump_spim", &dump_spim);

	interp.loop();
	return 0;
}