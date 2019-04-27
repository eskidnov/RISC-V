#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
#include "./core.h"

typedef std::unordered_map<uint32_t, std::function<void(Hart*, Instruction&)>> exec_t;

void lui(Hart* hart, Instruction& instr);
void auipc(Hart* hart, Instruction& instr);
void jal(Hart* hart, Instruction& instr);
void jalr(Hart* hart, Instruction& instr);
void beq(Hart* hart, Instruction& instr);
void bne(Hart* hart, Instruction& instr);
void blt(Hart* hart, Instruction& instr);
void bge(Hart* hart, Instruction& instr);
void bltu(Hart* hart, Instruction& instr);
void bgeu(Hart* hart, Instruction& instr);
void lb(Hart* hart, Instruction& instr);
void lh(Hart* hart, Instruction& instr);
void lw(Hart* hart, Instruction& instr);
void lbu(Hart* hart, Instruction& instr);
void lhu(Hart* hart, Instruction& instr);
void sb(Hart* hart, Instruction& instr);
void sh(Hart* hart, Instruction& instr);
void sw(Hart* hart, Instruction& instr);
void addi(Hart* hart, Instruction& instr);
void slti(Hart* hart, Instruction& instr);
void sltiu(Hart* hart, Instruction& instr);
void xori(Hart* hart, Instruction& instr);
void ori(Hart* hart, Instruction& instr);
void andi(Hart* hart, Instruction& instr);
void slli(Hart* hart, Instruction& instr);
void srli(Hart* hart, Instruction& instr);
void srai(Hart* hart, Instruction& instr);
void add(Hart* hart, Instruction& instr);
void sub(Hart* hart, Instruction& instr);
void sll(Hart* hart, Instruction& instr);
void slt(Hart* hart, Instruction& instr);
void sltu(Hart* hart, Instruction& instr);
void xor_(Hart* hart, Instruction& instr);
void srl(Hart* hart, Instruction& instr);
void sra(Hart* hart, Instruction& instr);
void or_(Hart* hart, Instruction& instr);
void and_(Hart* hart, Instruction& instr);
void fence(Hart* hart, Instruction& instr);
void fence_i(Hart* hart, Instruction& instr);
void ecall(Hart* hart, Instruction& instr);
void ebreak(Hart* hart, Instruction& instr);
void csrrw(Hart* hart, Instruction& instr);
void csrrs(Hart* hart, Instruction& instr);
void csrrc(Hart* hart, Instruction& instr);
void csrrwi(Hart* hart, Instruction& instr);
void csrrsi(Hart* hart, Instruction& instr);
void csrrci(Hart* hart, Instruction& instr);