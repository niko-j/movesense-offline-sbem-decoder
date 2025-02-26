#pragma once
#include "wb_types.hpp"
#include "vec.hpp"
#include "../sbem/sbem.hpp"

template<typename T>
struct IMUData : ISbemSerialized
{
    Timestamp timestamp;
    Array<T> measurements;

    virtual inline SbemSize getSerializedSize() const
    {
        return T().getSerializedSize() * measurements.size() + sizeof(Timestamp);
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset)
    {
        int payload = data.size() - sizeof(timestamp);
        uint32_t sampleSize = T().getSerializedSize();
        int samples = payload / sampleSize;
    
        if (payload < 0 || samples <= 0)
            return false;
    
        readValue<Timestamp>(data, offset + 0, timestamp);
        offset += sizeof(Timestamp);
    
        for (auto i = 0; i < samples; i++)
        {
            T sample;
            if (!sample.readFrom(data, offset + i * sampleSize))
                return false;
            measurements.push_back(sample);
        }
        return true;
    }
};

using AccData = IMUData<Vec3_Q12_12>;
using GyroData = IMUData<Vec3_Q12_12>;
using MagnData = IMUData<Vec3_Q10_6>;
