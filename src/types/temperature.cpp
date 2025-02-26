#include "temperature.hpp"

bool TemperatureData::readFrom(const std::vector<char>& data, size_t offset)
{
    return (
        readValue<int8>(data, offset, measurement) &&
        readValue<Timestamp>(data, offset + sizeof(int8), timestamp)
        );
}