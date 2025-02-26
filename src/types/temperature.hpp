#pragma once
#include "wb_types.hpp"
#include "../sbem/sbem.hpp"

struct TemperatureData : ISbemSerialized
{
    Timestamp timestamp;
    int8 measurement;

    virtual inline SbemSize getSerializedSize() const
    {
        return sizeof(timestamp) + sizeof(measurement);
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset);
};