#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iostream>

//#include "spi.h"
#include "interp.h"

#include "spi.h"

int main(int argc, char* argv[]) {
	//spi			mySPI;
	interp	interp;
	spi		spi;

	interp.register_func("spi_w", &spi::write);
	interp.loop();
	return 0;
}