#pragma once

#include <cstdint>
#include <string>
#include "memory.h"

#define RVG_LOAD		0b0000011
#define RVG_MISC_MEM	0b0001111
#define RVG_OP_IMM		0b0010011
#define RVG_AUIPC		0b0010111
#define RVG_STORE		0b0100011
#define RVG_AMO			0b0101111
#define RVG_OP			0b0110011
#define RVG_LUI			0b0110111
#define RVG_BRANCH		0b1100011
#define RVG_JALR		0b1100111
#define RVG_JAL			0b1101111
#define RVG_SYSTEM		0b1110011

using namespace std;

typedef struct {
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t rs2 : 5;
	uint32_t funct7 : 7;
} RType_t;

typedef struct {
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t imm : 12;
} IType_t;

typedef struct {
	uint32_t opcode : 7;
	uint32_t imm0_4 : 5;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t rs2 : 5;
	uint32_t imm5_11 : 7;
} SType_t;

typedef struct {
	uint32_t opcode : 7;
	uint32_t imm11 : 1;
	uint32_t imm1_4 : 4;
	uint32_t funct3 : 3;
	uint32_t rs1 : 5;
	uint32_t rs2 : 5;
	uint32_t imm5_10 : 6;
	uint32_t imm12 : 1;
} BType_t;

typedef struct {
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t imm : 20;
} UType_t;

typedef struct {
	uint32_t opcode : 7;
	uint32_t rd : 5;
	uint32_t imm12_19 : 8;
	uint32_t imm11 : 1;
	uint32_t imm1_10 : 10;
	uint32_t imm20 : 1;
} JType_t;

struct Instruction {
	union {
		uint32_t code;
		RType_t RType;
		IType_t IType;
		SType_t SType;
		BType_t BType;
		UType_t UType;
		JType_t JType;
	};
	int32_t get_IType_imm();
	int32_t get_SType_imm();
	int32_t get_BType_imm();
	int32_t get_UType_imm();
	int32_t get_JType_imm();
};

#define REGISTERS_NUM	32

class Hart {
	int32_t reg[REGISTERS_NUM];
	uint32_t pc = 0;
public:
	Memory mem;
	Hart() {}
	void init(uint32_t pc, uint32_t bytecode[], uint32_t size);
	uint32_t get_pc();
	void set_pc(uint32_t new_pc);
	uint32_t get_reg(uint8_t num);
	void set_reg(uint8_t num, int32_t data);
	void cycle(Instruction& instr);
	void print_state();
};