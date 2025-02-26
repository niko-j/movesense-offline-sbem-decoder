#include "gesture.hpp"

bool TapGestureData::readFrom(const std::vector<char>& data, size_t offset)
{
    return (
        readValue<uint8>(data, offset + 0, count) &&
        readValue<Timestamp>(data, offset + sizeof(count), timestamp)
        );
}

bool ShakeGestureData::readFrom(const std::vector<char>& data, size_t offset)
{
    return (
        readValue<uint32>(data, offset + 0, duration) &&
        readValue<Timestamp>(data, offset + sizeof(duration), timestamp)
        );
}
