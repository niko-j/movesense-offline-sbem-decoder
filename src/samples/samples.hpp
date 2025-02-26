#pragma once
#include "../types/offline_measurements.hpp"
#include <vector>

struct Samples
{
    std::vector<AccData> acc;
    std::vector<GyroData> gyro;
    std::vector<MagnData> magn;
    std::vector<HRData> hr;
    std::vector<RRData> rr;
    std::vector<ECGData> ecg;
    std::vector<TemperatureData> temp;
    std::vector<ActivityData> activity;

    std::vector<TapGestureData> tapGestures;
    std::vector<ShakeGestureData> shakeGestures;
    
    Samples(const SbemDocument& sbem);
};
