#pragma once
#include "../sbem/sbem.hpp"
#include "wb_types.hpp"
#include "fixed_point.hpp"

template<typename T, size_t ComponentSize>
struct Vec3 : ISbemSerialized
{
    T x;
    T y;
    T z;

    virtual inline SbemSize getSerializedSize() const
    {
        return ComponentSize * 3;
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset)
    {
        return (
            x.readFrom(data, offset + 0 * ComponentSize) &&
            y.readFrom(data, offset + 1 * ComponentSize) &&
            z.readFrom(data, offset + 2 * ComponentSize)
            );
    }
};

using Vec3_Q16_8 = Vec3<Q16_8, 3>;
using Vec3_Q12_12 = Vec3<Q12_12, 3>;
using Vec3_Q10_6 = Vec3<Q10_6, 2>;
