#include <stdint.h>
#include <stdio.h>

uint8_t rom[0x7FFF];
uint8_t video_ram[0x1FFF];
uint8_t external_ram[0x1FFF]; // cartridge
uint8_t working_ram[0x1FFF];
uint8_t working_ram_shadow[0x1FFF]; // Set this = &working_ram!
uint8_t oam[0x00FF]; // Sprite attrib memory
uint8_t zeropage_ram[0x007F];

uint8_t* addressBus(uint16_t address) {
	if (address <= 0x7FFF)
		return &rom[address];

	if (address >= 0x8000 && address <= 0x9FFF)
		return &video_ram[address - 0x8000];

	if (address >= 0xA000 && address <= 0xBFFF)
		return &external_ram[address - 0xA000];

	if (address >= 0xC000 && address <= 0xDFFF)
		return &working_ram[address - 0xC000];

	if (address >= 0xE000 && address <= 0xFDFF)
		return &working_ram_shadow[address - 0xE000];

	if (address >= 0xFE00 && address <= 0xFEFF)
		return &oam[address - 0xFE00];

	if (address >= 0xFF00 && address <= 0xFF7F){}
		//io control handling

	if (address >= 0xFF80 && address <= 0xFFFF)
		return zeropage_ram[address - 0xFF80];

	fprintf(stderr, "adressBus received undefined address: %X, exiting.\n", address);
	exit(1);
}

uint8_t readByte(int address) {
	return *addressBus(address);
}

uint16_t readShort(int address) { // Z80 word size is 8 bits
	return readByte(address) | (readByte(address) << 8);
}
