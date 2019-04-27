#include "../inc/core.h"
#include "../inc/exec.h"

extern exec_t exec;

int32_t Instruction::get_IType_imm()
{
	uint32_t imm = this->IType.imm;
	uint8_t sign = imm >> 11;
	return (int32_t)(sign ? imm ^ 0xFFFFF000 : imm);
}
int32_t Instruction::get_SType_imm()
{
	uint32_t imm = (this->SType.imm5_11 << 5) ^ this->SType.imm0_4;
	uint8_t sign = imm >> 11;
	return (int32_t)(sign ? imm ^ 0xFFFFF000 : imm);
}
int32_t Instruction::get_BType_imm()
{
	uint32_t imm = (this->BType.imm11 << 11) ^ (this->BType.imm1_4 << 1) ^ \
				   (this->BType.imm5_10 << 5) ^ (this->BType.imm12 << 12);
	uint8_t sign = this->BType.imm12;
	return (int32_t)(sign ? imm ^ 0xFFFFE000 : imm);
}
int32_t Instruction::get_UType_imm()
{
	return (int32_t)(this->UType.imm << 12);
}
int32_t Instruction::get_JType_imm()
{
	uint32_t imm = (this->JType.imm12_19 << 12) ^ (this->JType.imm11 << 11) ^ \
				   (this->JType.imm1_10 << 1) ^ (this->JType.imm20 << 20);
	uint8_t sign = this->JType.imm20;
	return (int32_t)(sign ? imm ^ 0xFFE00000 : imm);
}

void Hart::init(uint32_t pc, uint32_t bytecode[], uint32_t size)
{
	for (auto i = 0; i < REGISTERS_NUM; ++i) {
		reg[i] = 0;
	}
	this->pc = pc;
	mem.init(bytecode, pc, size);
}
uint32_t Hart::get_pc()
{
	return pc;
}
void Hart::set_pc(uint32_t pc)
{
	this->pc = pc;
}
uint32_t Hart::get_reg(uint8_t num)
{
	return reg[num];
}
void Hart::set_reg(uint8_t num, int32_t data)
{
	reg[num] = data;
}
void Hart::cycle(Instruction& instr)
{
	instr.code = mem.load_word(pc);
	uint32_t opcode = instr.RType.opcode;
	uint32_t funct3 = instr.RType.funct3 << 7;
	uint32_t funct7 = instr.RType.funct7 << 10;
	switch (opcode) {
	case RVG_LOAD:
		exec.at(opcode ^ funct3)(this, instr);
		pc += 4;
		break;
	case RVG_MISC_MEM:
		break;
	case RVG_OP_IMM:
		exec.at(opcode ^ funct3)(this, instr);
		pc += 4;
		break;
	case RVG_AUIPC:
		exec.at(opcode)(this, instr);
		break;
	case RVG_STORE:
		exec.at(opcode ^ funct3)(this, instr);
		pc += 4;
		break;
	case RVG_AMO:
		break;
	case RVG_OP:
		exec.at(opcode ^ funct3 ^ funct7)(this, instr);
		pc += 4;
		break;
	case RVG_LUI:
		exec.at(opcode ^ funct3)(this, instr);
		pc += 4;
		break;
	case RVG_BRANCH:
		exec.at(opcode ^ funct3)(this, instr);
		pc += 4;
		break;
	case RVG_JALR:
		exec.at(opcode ^ funct3)(this, instr);
		break;
	case RVG_JAL:
		exec.at(opcode)(this, instr);
		break;
	case RVG_SYSTEM:
		break;
	default:
		std::cout << "Decode error " << (opcode ^ funct3) << std::endl;
		break;
	}
}
void Hart::print_state()
{
	cout << endl << "REGISTERS" << endl << endl;
	uint32_t height = 8;
	uint32_t width = REGISTERS_NUM / height;
	for (auto i = 0; i < height; i++) {
		for (auto j = 0; j < width; j++) {
			uint32_t index = j + i * width;
			cout << "x" << index << "\t" << reg[index] << "\t";
		}
		cout << endl;
	}
	cout << endl << "MEMORY" << endl << endl;
	uint32_t size = mem.get_size();
	height = 8;
	width = size / height;
	for (auto i = 0; i < (height << 2); i+=4) {
		for (auto j = 0; j < (width << 2); j+=4) {
			cout.unsetf(ios::dec);
			cout.setf(ios::hex | ios::uppercase);
			cout.fill('0');
			cout.width(8);
			cout << mem.load_word(j + i * width) << " ";
			cout.unsetf(ios::hex | ios::uppercase);
			cout.setf(ios::dec);
			cout.width(0);
		}
		cout << endl;
	}
}