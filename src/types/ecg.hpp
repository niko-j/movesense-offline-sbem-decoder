#pragma once
#include "wb_types.hpp"
#include "../sbem/sbem.hpp"
#include "../compression/delta_compression.hpp"

struct ECGData : ISbemSerialized
{
    Timestamp timestamp;
    Array<int16> samples;

    virtual inline SbemSize getSerializedSize() const
    {
        return sizeof(timestamp) + sizeof(int16) * samples.size();
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset);
};

template<size_t BlockSize>
struct ECGCompressedData : ECGData
{
    virtual inline SbemSize getSerializedSize() const
    {
        return BlockSize;
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset)
    {
        int payload = data.size() - sizeof(timestamp);
        if (payload != BlockSize)
            return false;

        readValue<Timestamp>(data, offset, timestamp);
        offset += sizeof(Timestamp);

        DeltaCompression<int16, BlockSize> dc;
        samples = dc.decompress_block(data.data() + offset);
        return true;
    }
};
