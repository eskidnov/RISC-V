#include <iostream>
#include "../inc/memory.h"

Memory::Memory()
{
	uint32_t mem_size = (MEMORY_SIZE >> 2);
	this->size = mem_size;
	word = new int32_t[mem_size];
}
Memory::Memory(uint32_t bytecode[], uint32_t start, uint32_t size)
{
	uint32_t mem_size = (MEMORY_SIZE >> 2);
	this->size = mem_size;
	word = new int32_t[mem_size];
	init(bytecode, start, size);
}
Memory::~Memory()
{
	delete[] word;
}
void Memory::init(uint32_t bytecode[], uint32_t start, uint32_t size)
{
	uint32_t start_word = (start >> 2);
	uint32_t size_words = (size >> 2);
	if ((start_word << 2) != start) {
		std::cout << "Warning (memory initialization): start address is not aligned" << std::endl;
	}
	if ((size_words << 2) != size) {
		std::cout << "Warning (memory initialization): size is not aligned" << std::endl;
	}
	if (start_word + size_words >= this->size) {
		//throw MemoryOverflow();
		std::cout << "Error: Memory overflow" << std::endl;
	}
	for (auto i = 0; i < size_words; i++) {
		word[i + start_word] = (int32_t)bytecode[i];
	}
}
void Memory::reset()
{
	for (auto i = 0; i < size; i++) {
		word[i] = 0;
	}
}
void Memory::store_word(uint32_t address, int32_t data)
{
	if (address >= MEMORY_SIZE) {
		//throw MemoryOverflow();
		std::cout << "Error: Memory overflow" << std::endl;
	}
	*((uint32_t*)(byte + address)) = data;
}
void Memory::store_hword(uint32_t address, int16_t data)
{
	if (address >= MEMORY_SIZE) {
		//throw MemoryOverflow();
		std::cout << "Error: Memory overflow" << std::endl;
	}
	*((uint16_t*)(byte + address)) = data;
}
void Memory::store_byte(uint32_t address, int8_t data)
{
	if (address >= MEMORY_SIZE) {
		//throw MemoryOverflow();
		std::cout << "Error: Memory overflow" << std::endl;
	}
	*(byte + address) = data;
}
int32_t Memory::load_word(uint32_t address)
{
	if (address >= MEMORY_SIZE) {
		//throw MemoryOverflow();
		std::cout << "Error: Memory overflow" << std::endl;
	}
	return *((uint32_t*)(byte + address));
}
int32_t Memory::load_hword(uint32_t address)
{
	if (address >= MEMORY_SIZE) {
		//throw MemoryOverflow();
		std::cout << "Error: Memory overflow" << std::endl;
	}
	return *((uint16_t*)(byte + address));
}
int32_t Memory::load_byte(uint32_t address)
{
	if (address >= MEMORY_SIZE) {
		//throw MemoryOverflow();
		std::cout << "Error: Memory overflow" << std::endl;
	}
	return *(byte + address);
}
uint32_t Memory::get_size()
{
	return size;
}