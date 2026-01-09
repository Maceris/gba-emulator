#pragma once

#include <cstdint>

using Wire1 = uint8_t;
using Wire2 = uint8_t;
using Wire32 = uint32_t;

void set_bit(Wire1* wire, bool on);
void set_bit(Wire2* wire, int bit, bool on);
void set_bit(Wire32* wire, int bit, bool on);

bool get_bit(Wire1* wire);
bool get_bit(Wire2* wire, int bit);
bool get_bit(Wire32* wire, int bit);

#define INCOMING
#define OUTGOING
#define INTERNAL
