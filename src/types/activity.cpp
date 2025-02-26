#include "activity.hpp"

bool ActivityData::readFrom(const std::vector<char>& data, size_t offset)
{
    return (
        readValue<uint16_t>(data, offset, activity) &&
        readValue<Timestamp>(data, offset + sizeof(activity), timestamp)
        );
}
