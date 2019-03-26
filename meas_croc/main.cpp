#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iostream>

#include "interp.h"
#include "spi.h"

#include "test.h"
#include "meas.h"

spi mainSPI;

int main(int argc, char* argv []) {
	interp	interp;

	interp.register_func("spi_w", &main_spi_write);
	interp.register_func("spi_r", &main_spi_read);
	interp.register_func("spi_dump_fpga", &main_spi_dump_fpga);

	interp.register_func("test_sr", &test_sr);
	interp.register_func("test_daq", &test_daq);
	interp.register_func("test_bs_file", &test_bs_file);
	interp.register_func("test_meas", &test_meas);
	interp.register_func("test_instr", &test_instr);

	interp.register_func("test_instr_wfmgen", &test_agilent33622a);
	interp.register_func("test_instr_freqcnt", &test_agilent53230a);
	interp.register_func("test_instr_mm", &test_keithley2002);

	interp.register_func("test_tempctrl", &test_tempctrl);
	interp.register_func("test_tempctrl_sw", &test_tempctrl_sw);
	interp.register_func("test_oven", &test_vt4200);

	interp.register_func("meas_fsw", &meas_fsw);
	interp.register_func("meas_dco", &meas_dco);
	interp.register_func("meas_tsw", &meas_tsw);

	interp.loop();
	return 0;
}