#include "hr.hpp"
#include "../compression/bit_pack.hpp"

bool HRData::readFrom(const std::vector<char>& data, size_t offset)
{
    return (
        readValue<Timestamp>(data, offset + 0, timestamp) &&
        readValue<uint8>(data, offset + sizeof(timestamp), average)
        );
}

bool RRData::readFrom(const std::vector<char>& data, size_t offset)
{
    int payload = data.size() - sizeof(timestamp);
    int sampleDataSizeInBits = payload * 8;
    constexpr uint32_t sampleSizeInBits = 12; // 12-bit samples bit-packed
    int samples = sampleDataSizeInBits / sampleSizeInBits;

    if (sampleDataSizeInBits < 0 || samples <= 0 || sampleDataSizeInBits % 12)
        return false;

    readValue<Timestamp>(data, offset + 0, timestamp);
    offset += sizeof(Timestamp);

    std::vector<uint8_t> packedData((size_t)payload);
    memcpy(packedData.data(), data.data() + offset, payload);

    intervals = bit_pack::unpack<uint16_t, 12>(packedData);
    return true;
}
