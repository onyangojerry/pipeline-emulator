#include "components/decoder.hh"
#include <cassert>
#include <iostream>

int
main(int argc, char **argv)
{
	Decoder d = {};
	string operation;
	int destination;
	int source_register1;
	int source_register2;
	int imm;

	// test case 1
	std::cout << "Test case 1: ldi r5, 1234" << std::endl;
	d.decode("ldi r5, 1234", operation, destination, source_register1, source_register2, imm);
	assert(operation == "ldi");
	assert(destination == 5);
	assert(source_register1 == 0);
	assert(source_register2 == 0);
	assert(imm == 1234);
	std::cout << "Test passed!" << std::endl;

	// test case 2
	std::cout << "Test case 2: end" << std::endl;
	d.decode("end", operation, destination, source_register1, source_register2, imm);
	assert(operation == "end");
	assert(destination == 0);
	assert(source_register1 == 0);
	assert(source_register2 == 0);
	assert(imm == 0);
	std::cout << "Test passed!" << std::endl;

	// test case 3
	std::cout << "Test case 3: div r3, r2, r1" << std::endl;
	d.decode("div r3, r2, r1", operation, destination, source_register1, source_register2, imm);
	assert(operation == "div");
	assert(destination == 3);
	assert(source_register1 == 2);
	assert(source_register2 == 1);
	assert(imm == 0);
	std::cout << "Test passed!" << std::endl;

	// TODO: add more!

	return 0;
}
