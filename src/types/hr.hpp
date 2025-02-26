#pragma once
#include "wb_types.hpp"
#include "../sbem/sbem.hpp"

struct HRData : ISbemSerialized
{
    Timestamp timestamp;
    uint8 average;

    virtual inline SbemSize getSerializedSize() const
    {
        return sizeof(timestamp) + sizeof(average);
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset);
};

struct RRData : ISbemSerialized
{
    Timestamp timestamp;
    Array<uint16_t> intervals;

    virtual inline SbemSize getSerializedSize() const
    {
        return sizeof(timestamp) + sizeof(uint16_t) * intervals.size();
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset);
};
