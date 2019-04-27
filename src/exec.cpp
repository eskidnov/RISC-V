#include "../inc/exec.h"
#include "../inc/core.h"

exec_t exec = {
{55, lui},
{23, auipc},
{111, jal},
{103, jalr},
{99, beq},
{227, bne},
{611, blt},
{739, bge},
{867, bltu},
{995, bgeu},
{3, lb},
{131, lh},
{259, lw},
{515, lbu},
{643, lhu},
{35, sb},
{163, sh},
{291, sw},
{19, addi},
{275, slti},
{403, sltiu},
{531, xori},
{787, ori},
{915, andi},
{147, slli},
{659, srli},
{1683, srai},
{51, add},
{1075, sub},
{179, sll},
{307, slt},
{435, sltu},
{563, xor_},
{691, srl},
{1715, sra},
{819, or_},
{947, and_},
};

void lui(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.UType.rd, instr.get_UType_imm());
}
void auipc(Hart* hart, Instruction& instr)
{
	int32_t res = hart->get_pc() + instr.get_UType_imm();
	hart->set_pc(res);
	hart->set_reg(instr.UType.rd, res);
}
void jal(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.JType.rd, hart->get_pc() + 4);
	hart->set_pc(hart->get_pc() + instr.get_JType_imm());
}
void jalr(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, hart->get_pc() + 4);
	hart->set_pc((hart->get_reg(instr.IType.rs1) + instr.get_JType_imm()) ^ 0xFFFFFFFE);
}
void beq(Hart* hart, Instruction& instr)
{
	if (hart->get_reg(instr.BType.rs1) == hart->get_reg(instr.BType.rs2)) {
		hart->set_pc(hart->get_pc() + instr.get_BType_imm());
	}
}
void bne(Hart* hart, Instruction& instr)
{
	if (hart->get_reg(instr.BType.rs1) != hart->get_reg(instr.BType.rs2)) {
		hart->set_pc(hart->get_pc() + instr.get_BType_imm());
	}
}
void blt(Hart* hart, Instruction& instr)
{
	if (hart->get_reg(instr.BType.rs1) < hart->get_reg(instr.BType.rs2)) {
		hart->set_pc(hart->get_pc() + instr.get_BType_imm());
	}
}
void bge(Hart* hart, Instruction& instr)
{
	if (hart->get_reg(instr.BType.rs1) > hart->get_reg(instr.BType.rs2)) {
		hart->set_pc(hart->get_pc() + instr.get_BType_imm());
	}
}
void bltu(Hart* hart, Instruction& instr)
{
	if ((uint32_t)hart->get_reg(instr.BType.rs1) < (uint32_t)hart->get_reg(instr.BType.rs2)) {
		hart->set_pc(hart->get_pc() + instr.get_BType_imm());
	}
}
void bgeu(Hart* hart, Instruction& instr)
{
	if ((uint32_t)hart->get_reg(instr.BType.rs1) > (uint32_t)hart->get_reg(instr.BType.rs2)) {
		hart->set_pc(hart->get_pc() + instr.get_BType_imm());
	}
}
void lb(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, (int32_t)hart->mem.load_byte(hart->get_reg(instr.IType.rs1) + instr.get_IType_imm()));
}
void lh(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, (int32_t)hart->mem.load_hword(hart->get_reg(instr.IType.rs1) + instr.get_IType_imm()));
}
void lw(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, hart->mem.load_word(hart->get_reg(instr.IType.rs1) + instr.get_IType_imm()));
}
void lbu(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, (uint32_t)(uint8_t)hart->mem.load_byte(hart->get_reg(instr.IType.rs1) + instr.get_IType_imm()));
}
void lhu(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, (uint32_t)(uint16_t)hart->mem.load_byte(hart->get_reg(instr.IType.rs1) + instr.get_IType_imm()));
}
void sb(Hart* hart, Instruction& instr)
{
	hart->mem.store_byte(hart->get_reg(instr.SType.rs1) + instr.get_SType_imm(), (int8_t)hart->get_reg(instr.SType.rs2));
}
void sh(Hart* hart, Instruction& instr)
{
	hart->mem.store_hword(hart->get_reg(instr.SType.rs1) + instr.get_SType_imm(), (int16_t)hart->get_reg(instr.SType.rs2));
}
void sw(Hart* hart, Instruction& instr)
{
	hart->mem.store_word(hart->get_reg(instr.SType.rs1) + instr.get_SType_imm(), hart->get_reg(instr.SType.rs2));
}
void addi(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, hart->get_reg(instr.IType.rs1) + instr.get_IType_imm());
}
void slti(Hart* hart, Instruction& instr)
{
	if (hart->get_reg(instr.IType.rs1) < instr.get_IType_imm()) {
		hart->set_reg(instr.IType.rd, 1);
	}
	else {
		hart->set_reg(instr.IType.rd, 0);
	}
}
void sltiu(Hart* hart, Instruction& instr)
{
	if ((uint32_t)hart->get_reg(instr.IType.rs1) < (uint32_t)instr.get_IType_imm()) {
		hart->set_reg(instr.IType.rd, 1);
	}
	else {
		hart->set_reg(instr.IType.rd, 0);
	}
}
void xori(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, hart->get_reg(instr.IType.rs1) ^ instr.get_IType_imm());
}
void ori(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, hart->get_reg(instr.IType.rs1) | instr.get_IType_imm());
}
void andi(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.IType.rd, hart->get_reg(instr.IType.rs1) & instr.get_IType_imm());
}
void slli(Hart* hart, Instruction& instr)
{
	uint32_t imm = (uint32_t)instr.get_IType_imm();
	if (imm >> 5) {
		std::cout << "Error in SLLI instruction" << std::endl;
	}
	else {
		hart->set_reg(instr.IType.rd, hart->get_reg(instr.IType.rs1) << imm);
	}
}
void srli(Hart* hart, Instruction& instr)
{
	uint32_t imm = (uint32_t)instr.get_IType_imm();
	if (imm >> 5) {
		std::cout << "Error in SLLI instruction" << std::endl;
	}
	else {
		hart->set_reg(instr.IType.rd, (uint32_t)hart->get_reg(instr.IType.rs1) >> imm);
	}
}
void srai(Hart* hart, Instruction& instr)
{
	uint32_t imm = (uint32_t)instr.get_IType_imm();
	if ((imm >> 5) ^ 0x20) {
		std::cout << "Error in SLLI instruction" << std::endl;
	}
	else {
		hart->set_reg(instr.IType.rd, hart->get_reg(instr.IType.rs1) >> imm);
	}
}
void add(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.RType.rd, hart->get_reg(instr.RType.rs1) + hart->get_reg(instr.RType.rs2));
}
void sub(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.RType.rd, hart->get_reg(instr.RType.rs1) - hart->get_reg(instr.RType.rs2));
}
void sll(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.RType.rd, hart->get_reg(instr.RType.rs1) << (hart->get_reg(instr.RType.rs2) & 0x1F));
}
void slt(Hart* hart, Instruction& instr)
{
	if (hart->get_reg(instr.RType.rs1) < hart->get_reg(instr.RType.rs2)) {
		hart->set_reg(instr.RType.rd, 1);
	}
	else {
		hart->set_reg(instr.RType.rd, 0);
	}
}
void sltu(Hart* hart, Instruction& instr)
{
	if ((uint32_t)hart->get_reg(instr.RType.rs1) < (uint32_t)hart->get_reg(instr.RType.rs2)) {
		hart->set_reg(instr.RType.rd, 1);
	}
	else {
		hart->set_reg(instr.RType.rd, 0);
	}
}
void xor_(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.RType.rd, hart->get_reg(instr.RType.rs1) ^ hart->get_reg(instr.RType.rs2));
}
void srl(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.RType.rd, (uint32_t)hart->get_reg(instr.RType.rs1) >> (hart->get_reg(instr.RType.rs2) & 0x1F));
}
void sra(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.RType.rd, hart->get_reg(instr.RType.rs1) >> (hart->get_reg(instr.RType.rs2) & 0x1F));
}
void or_(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.RType.rd, hart->get_reg(instr.RType.rs1) | hart->get_reg(instr.RType.rs2));
}
void and_(Hart* hart, Instruction& instr)
{
	hart->set_reg(instr.RType.rd, hart->get_reg(instr.RType.rs1) & hart->get_reg(instr.RType.rs2));
}
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