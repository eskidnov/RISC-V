#include <iostream>
#include "./inc/memory.h"
#include "./inc/core.h"

int main(int argc, char* argv[])
{
	Hart hart;
	uint32_t start = 0x14;
	uint32_t size = 7;
	uint32_t *bytecode = new uint32_t[size] {
		0x04200593,		// addi	x11, x0, 0x42	|	x11 = 66
		0x01000393,		// addi	x7, x0, 0x10	|	x7 = 16		
		0x02B3A823,		// sw	x11, 0x10(x7)	|	mem[x7+16] = x11 (mem[32] = 66)
		0x0043A383,		// lw	x7, 0x4(x7)		|	x7 = mem[x7+16] (x7 = 66)
		0xFE0008E3		// beq x0, x0, -4		|	pc = pc
	};
	hart.init(start, bytecode, size*4);
	std::cout << "INSTRUCTIONS" << std::endl << std::endl;
	cout.unsetf(ios::dec);
	cout.setf(ios::hex | ios::uppercase);
	for (auto i = 0; i < size; i++) {
		Instruction instr;
		hart.cycle(instr);
		cout.fill('0');
		cout.width(8);
		cout << hart.get_pc() - 4 << ": ";
		cout.fill('0');
		cout.width(8);
		cout << instr.code << endl;
	}
	cout.unsetf(ios::hex | ios::uppercase);
	cout.setf(ios::dec);
	hart.print_state();
	return 0;
}