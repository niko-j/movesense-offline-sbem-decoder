#include "ecg.hpp"

bool ECGData::readFrom(const std::vector<char>& data, size_t offset)
{
    int payload = data.size() - sizeof(timestamp);
    constexpr uint32_t sampleSize = sizeof(int16_t); // 16-bit signed values
    int count = payload / sampleSize;

    if (payload < 0 || count <= 0)
        return false;

    readValue<Timestamp>(data, offset + 0, timestamp);
    offset += sizeof(Timestamp);

    for (auto i = 0; i < count; i++)
    {
        int16_t sample;
        if (!readValue(data, offset + i * sampleSize, sample))
            return false;
        samples.push_back(sample);
    }

    return true;
}
