#pragma once
#include <stdint.h>

uint8_t readByte(uint16_t address);
uint16_t readShort(uint16_t address);
void writeByte(uint16_t address, uint8_t byte);
void loadROM(char* path);
void initMMU();
