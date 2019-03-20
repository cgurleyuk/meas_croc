#pragma once

#include <vector>
#include <string>

#include <iostream>
#include <fstream>

typedef unsigned char uint8;

class bs_file
{
public:
	bs_file();
	bs_file(const std::string fileName);
	~bs_file();

	void open(const std::string fileName);
	void write_bs(const std::vector<uint8> &bs);
	void close();
private:
	std::ofstream fStream;
};

