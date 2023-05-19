#pragma once
#include "DLLManager.h"
#include "Utility/Time.h"

class DLLEXPORT TimeSingleton
{
public:
    TimeSingleton(const TimeSingleton&) = delete;
    static TimeSingleton& Get()
    {
        static TimeSingleton instance;
        return instance;
    }
    static Time* GetTime() { return Get().GetTimeInternal(); }
    static void SetTime(Time* newTime) { Get().SetTimeInternal(newTime); }
private:
    Time* GetTimeInternal() { return time; }
    void SetTimeInternal(Time* newTime) { time = newTime; }
    TimeSingleton() {}
    Time* time;
};