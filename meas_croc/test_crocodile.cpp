#include "crocodile.h"

#include <iostream>
#include <algorithm>

double test_crocodile(std::vector<double> vPar)
{
	crocodile croc;

	std::vector<uint8> sr_pre = croc.get_sr();
	std::for_each(sr_pre.begin(), sr_pre.end(), [&](uint8 i) 
	{
		std::cout << std::hex << static_cast<unsigned>(i) << " ";
	});
	std::cout << std::endl;

	croc.mod_enable(croc_mod::croc_mod_pp);
	std::vector<uint8> sr_post = croc.get_sr();
	std::for_each(sr_post.begin(), sr_post.end(), [&](uint8 i)
	{
		std::cout << std::hex << static_cast<unsigned>(i) << " ";
	});
	std::cout << std::endl;

	return 0;
}