#include "samples.hpp"
#include "sample_utils.hpp"
#include "../sbem/sbem_loader.hpp"

Samples::Samples(const SbemDocument& sbem)
{
    for (const auto& chunk : sbem.getChunks())
    {
        auto* desc = sbem_loader::get_first_item_descriptor(sbem, chunk);
        if (!desc)
        {
            printf("Missing descriptor for chunk type %u\n", chunk.header.id);
            continue;
        }
        auto measurement = desc->getName().value_or("");

        if (measurement.find("OfflineMeasAcc.") != std::string::npos)
        {
            AccData data;
            if (chunk.tryRead(data))
                acc.push_back(data);
        }
        else if (measurement.find("OfflineMeasGyro.") != std::string::npos)
        {
            GyroData data;
            if (chunk.tryRead(data))
                gyro.push_back(data);
        }
        else if (measurement.find("OfflineMeasMagn.") != std::string::npos)
        {
            MagnData data;
            if (chunk.tryRead(data))
                magn.push_back(data);
        }
        else if (measurement.find("OfflineMeasHR.") != std::string::npos)
        {
            HRData data;
            if (chunk.tryRead(data))
                hr.push_back(data);
        }
        else if (measurement.find("OfflineMeasRR.") != std::string::npos)
        {
            RRData data;
            if (chunk.tryRead(data))
                rr.push_back(data);
        }
        else if (measurement.find("OfflineMeasECG.") != std::string::npos)
        {
            ECGData data;
            if (chunk.tryRead(data))
                ecg.push_back(data);
        }
        else if (measurement.find("OfflineMeasECGCompressed.") != std::string::npos)
        {
            ECGCompressedData<32> data;
            if (chunk.tryRead(data))
            {
                if (!ecg.empty() && data.timestamp == ecg.back().timestamp)
                {
                    for (const auto& s : data.samples)
                        ecg.back().samples.push_back(s);
                }
                else
                {
                    ecg.push_back(data);
                }
            }
        }
        else if (measurement.find("OfflineMeasTemp.") != std::string::npos)
        {
            TemperatureData data;
            if (chunk.tryRead(data))
                temp.push_back(data);
        }
        else if (measurement.find("OfflineMeasActivity.") != std::string::npos)
        {
            ActivityData data;
            if (chunk.tryRead(data))
                activity.push_back(data);
        }
        else if (measurement.find("GestureTap.") != std::string::npos)
        {
            TapGestureData data;
            if (chunk.tryRead(data))
                tapGestures.push_back(data);
        }
        else if (measurement.find("GestureShake.") != std::string::npos)
        {
            ShakeGestureData data;
            if (chunk.tryRead(data))
                shakeGestures.push_back(data);
        }
        else
        {
            printf("Unknown measurement: %s\n", measurement.c_str());
        }
    }
}
