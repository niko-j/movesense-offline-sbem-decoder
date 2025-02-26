#pragma once
#include "wb_types.hpp"
#include "../sbem/sbem.hpp"

template<typename T, uint8_t Bits, uint8_t Q>
struct FixedPoint : ISbemSerialized
{
    static_assert(Bits % 8 == 0 && "Number of bits has to be byte-aligned");
    T value;

    inline float toFloat() const
    {
        return ((double)value / (double)(1 << Q));
    }

    virtual inline SbemSize getSerializedSize() const
    {
        return Bits / 8;
    }

    virtual bool readFrom(const std::vector<char>& data, size_t offset)
    {
        const int bytes = getSerializedSize();
        bool result = true;
        value = 0;

        for (int i = 0; i < bytes; i++)
        {
            uint8_t byte = 0x00;
            if (!readValue(data, offset + i, byte))
                return false;

            if ((i + 1) == bytes) // Last byte, treat as signed!
                value |= (((int8_t)byte) << (i * 8));
            else
                value |= (byte << (i * 8));
        }

        return true;
    }
};

using Q16_8 = FixedPoint<int32_t, 24, 8>;
using Q12_12 = FixedPoint<int32_t, 24, 12>;
using Q10_6 = FixedPoint<int16_t, 16, 6>;
