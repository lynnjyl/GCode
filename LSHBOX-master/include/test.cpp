#include <iostream>
#include <fstream>
#include <random>
#include <ctime>


void load(const std::string &path)
{
    std::cout << "in load function" << std::endl;
    std::ifstream is(path.c_str(), std::ios::binary);
    unsigned header[3];
    //assert(sizeof header == 3 * 4);
    is.read((char *)header, sizeof header);
    std::cout << header[0] << " " << header[1] << " " << header[2] << std::endl;
    //reset(header[2], header[1]);
    int *dims;
    int dim,N;
    size_t sz = sizeof(int) * dim * N;
    is.read((char *)dims, sz);
    std::cout << "finished " << " " << std::endl;
    std::cout << dims[80] << " " << dims[81] << " " << dims[82] << std::endl;
    return;
}
int main()
{
/*
	std::mt19937 rng(unsigned (std::time(0)));
	//std::cout << rng << std::endl;
	std::uniform_int_distribution<unsigned> usBits(0,9);
	unsigned target = usBits(rng);
	std::cout << target << std::endl;
	target = usBits(rng);
	std::cout << target << std::endl;*/

    load("unsigned.data");
    std::cout << "ok " << std::endl;

	return 0;
}
