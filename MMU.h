#pragma once
#include <stdint.h>

uint8_t readByte(uint16_t address);
uint16_t readShort(uint16_t address);
void loadCartridge(char* path);
void initMMU();
