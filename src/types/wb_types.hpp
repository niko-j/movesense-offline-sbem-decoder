#pragma once
#include <cstdint>
#include <vector>

#define int32 int32_t
#define uint32 uint32_t
#define int16 int16_t
#define uint16 uint16_t
#define int8 int8_t
#define uint8 uint8_t
#define Timestamp uint32_t

template<typename T>
using Array = std::vector<T>;

template<typename T>
bool readValue(const std::vector<char>& data, size_t offset, T& out)
{
	if (offset + sizeof(T) > data.size())
		return false;
	out = *reinterpret_cast<const T*>(data.data() + offset);
	return true;
}
