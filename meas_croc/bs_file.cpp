#include "bs_file.h"



bs_file::bs_file()
{
}

bs_file::bs_file(const std::string fileName)
{
	open(fileName);
}


bs_file::~bs_file()
{
}

void bs_file::open(const std::string fileName)
{
	fStream.open(fileName.c_str(), std::ios::out | std::ios::binary);
}

void bs_file::write_bs(const std::vector<uint8>& bs)
{
	fStream.write(reinterpret_cast<const char*>(&bs[0]), bs.size() * sizeof(uint8));
}

void bs_file::write_bs(const std::vector<uint8>& bs, const double T_begin, const double T_end)
{
	fStream.write(reinterpret_cast<const char*>(&T_begin), sizeof(T_begin));
	fStream.write(reinterpret_cast<const char*>(&T_end), sizeof(T_end));
	fStream.write(reinterpret_cast<const char*>(&bs[0]), bs.size() * sizeof(uint8));
}

void bs_file::close()
{
	fStream.close();
}


