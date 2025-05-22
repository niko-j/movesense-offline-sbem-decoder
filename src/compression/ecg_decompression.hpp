#pragma once
#include <cstdlib>
#include <vector>

template<size_t BlockSize, typename TSample, typename TDiff>
class ECGDecompressor
{
private:
    static size_t count_leading_zeros(uint8_t b)
    {
        for (size_t i = 0; i < 8; i++)
        {
            if ((b << i) & 128)
                return i;
        }
        return 8;
    }

    // Calculate values based on diffs
    static TSample calculate_values(TSample init, const TDiff* deltas, size_t deltaCount, TSample* outSamples)
    {
        TSample value = init;
        for (size_t i = 0; i < deltaCount; i++)
        {
            outSamples[i] = value + deltas[i];
            value = outSamples[i];
        }
        return value;
    }

    // Elias Gamme w/ bijection decode
    static bool decode_value(const uint8_t* data, size_t dataLen, TDiff& valueOut, size_t& bitOffset)
    {
        size_t n = 0;
        size_t pos = bitOffset / 8;
        size_t offset = bitOffset % 8;
        int read_bits = 0;
        size_t max_bits = sizeof(TDiff) * 8;
        uint64_t temp = 0;
        valueOut = 0;

        while (pos < dataLen)
        {
            if (!read_bits)
            {
                uint8_t b = data[pos] << offset;
                size_t leadingZeros = count_leading_zeros(b);

                if (leadingZeros == 8)
                {
                    n += (8 - offset);
                    pos += 1;
                    offset = 0; // Start next byte from start
                    continue;
                }
                else
                {
                    n += leadingZeros;
                    if (n > max_bits)
                        return false; // Too many bits

                    offset = offset + leadingZeros % 8; // Start reading bits from this offset

                    pos += offset / 8;
                    offset %= 8;

                    read_bits = n + 1;
                    // pos stays, read byte again on next iter
                }
            }
            else
            {
                uint8_t b = data[pos];

                // Read value bits from the byte, start after zeros (if any)
                for (int i = 7 - offset; i >= 0 && read_bits > 0; i--)
                {
                    read_bits -= 1;
                    bool bit = (b >> i) & 0b1;

                    if (bit)
                        temp += std::pow(2.0, read_bits);
                }

                if (read_bits > 0)
                {
                    pos += 1; // move to next byte and
                    offset = 0; // start from the beginning of the next byte
                }
                else
                {
                    if (temp & 0b1)
                        temp = (temp >> 1);
                    else
                        temp = (temp >> 1) * -1;

                    valueOut = (TSample) temp;

                    bitOffset += 2 * n + 1; // new offset for the next value
                    return true;
                }
            }
        }

        return false;
    }

public:
    static std::vector<TSample> decompress_block(const uint8_t* data)
    {
        std::vector<TSample> samples;
        size_t sampleCount = data[0];

        TSample init = 0;
        memcpy(&init, &data[1], sizeof(init));
        samples.push_back(init);

        size_t bitOffset = 0;
        size_t deltasOffset = sizeof(init) + 1;
        size_t deltasLen = BlockSize - deltasOffset;
        while (samples.size() < sampleCount)
        {
            TDiff diff;
            if (decode_value(data + deltasOffset, deltasLen, diff, bitOffset))
            {
                TSample sample;
                init = calculate_values(init, &diff, 1, &sample);
                samples.push_back(sample);
            }
            else
            {
                break;
            }
        }
        return samples;
    }
};


