#include "sr.h"

#include <iostream>
#include <algorithm>

double test_sr(std::vector<double> vPar)
{
	sr croc;

	std::cout << "default shift register state: " << std::endl;

	std::vector<uint8> sr_pre = croc.get_vsr();
	std::for_each(sr_pre.begin(), sr_pre.end(), [&](uint8 i) 
	{
		std::cout << std::hex << static_cast<unsigned>(i) << " ";
	});
	std::cout << std::endl;

	std::cout << "modulator enabled register state: " << std::endl;

	croc.mod_enable(sr_mod::sr_mod_pp);
	std::vector<uint8> sr_post = croc.get_vsr();
	std::for_each(sr_post.begin(), sr_post.end(), [&](uint8 i)
	{
		std::cout << std::hex << static_cast<unsigned>(i) << " ";
	});
	std::cout << std::endl;

	return 0;
}