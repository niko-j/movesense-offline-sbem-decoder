#pragma once
#include "wb_types.hpp"
#include "../sbem/sbem.hpp"

struct TapGestureData : ISbemSerialized
{
    Timestamp timestamp;
    uint8 count;

    virtual inline SbemSize getSerializedSize() const
    {
        return sizeof(timestamp) + sizeof(count);
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset);
};

struct ShakeGestureData : ISbemSerialized
{
    Timestamp timestamp;
    uint32 duration;

    virtual inline SbemSize getSerializedSize() const
    {
        return sizeof(timestamp) + sizeof(duration);
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset);
};