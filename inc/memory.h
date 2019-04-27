#pragma once

#include <cstdint>
#include <iostream>

#define MEMORY_SIZE	256

class Memory {
	uint32_t size;
	union {
		int32_t* word;
		int16_t* hword;
		int8_t* byte;
	};
public:
	Memory();
	Memory(uint32_t bytecode[], uint32_t start, uint32_t size);
	~Memory();
	void init(uint32_t bytecode[], uint32_t start, uint32_t size);
	void reset();
	void store_word(uint32_t address, int32_t data);
	void store_hword(uint32_t address, int16_t data);
	void store_byte(uint32_t address, int8_t data);
	int32_t load_word(uint32_t address);
	int32_t load_hword(uint32_t address);
	int32_t load_byte(uint32_t address);
	uint32_t get_size();
};