#pragma once
#include "wb_types.hpp"
#include "../sbem/sbem.hpp"

struct ActivityData : ISbemSerialized
{
    Timestamp timestamp;
    uint16 activity;

    virtual inline SbemSize getSerializedSize() const
    {
        return sizeof(timestamp) + sizeof(activity);
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset);
};
