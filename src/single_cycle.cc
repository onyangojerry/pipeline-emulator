#include "processors/single_cycle.hh"
#include <cassert>
#include <iostream>

int
main(int argc, char **argv)
{
	std::cout << "Running test-progs/test0" << std::endl;
	SingleCycleProcessor cpu0 = {"test-progs/test0" };
	cpu0.executeProgram();

	std::cout << "\n\nRunning test-progs/test1" << std::endl;
	SingleCycleProcessor cpu1 = {"test-progs/test1" };
	cpu1.executeProgram();

	std::cout << "\n\nRunning test-progs/test2" << std::endl;
	SingleCycleProcessor cpu2 = {"test-progs/test2" };
	cpu2.executeProgram();

	return 0;
}
