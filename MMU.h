#pragma once
#include <stdint.h>

uint8_t readByte(int address);
uint16_t readShort(int address);
void loadCartridge(char* path);
void initMMU();
