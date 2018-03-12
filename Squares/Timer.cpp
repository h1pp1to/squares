#include "Timer.h"
#include <algorithm>
#include <iostream>

namespace
{
    uint64_t GetNextFreeId()
    {
        static uint64_t id = 0;
        return id++;
    }
}

void Timer::Once(Callback cb)
{
    TimerData ti;
    ti.timerId = GetNextFreeId();
    ti.cb = cb;
    ti.info = TimerInfo::once;
    timers.emplace_back(std::move(ti));
}

void Timer::CallInfinite(Callback cb)
{
    TimerData ti;
    ti.timerId = GetNextFreeId();
    ti.cb = cb;
    ti.info = TimerInfo::infinite;
    timers.emplace_back(std::move(ti));
}

void Timer::EveryOnce(int time, Callback cb)
{
    TimerData ti;
    ti.timerId = GetNextFreeId();
    ti.cb = cb;
    ti.frequency = time;
    ti.info = TimerInfo::everyOnce;
    timers.emplace_back(std::move(ti));
}

void Timer::StartAfter(int time, Callback cb)
{
    TimerData ti;
    ti.timerId = GetNextFreeId();
    ti.cb = cb;
    ti.frequency = time;
    ti.info = TimerInfo::startAfter;
    timers.emplace_back(std::move(ti));
}

void Timer::CallUntil(int time, Callback cb)
{
    TimerData ti;
    ti.timerId = GetNextFreeId();
    ti.cb = cb;
    ti.frequency = time;
    ti.info = TimerInfo::callUntil;
    timers.emplace_back(std::move(ti));
}

void Timer::StopTimer(uint64_t timerId)
{
    auto iter = std::remove_if(timers.begin(), timers.end(), [timerId](const TimerData& timer)
    {
        return timer.timerId == timerId;
    });
    timers.erase(iter, timers.end());
}

void Timer::Update(int deltaTime)
{
//    static auto timeStart = std::chrono::steady_clock::now();
//    auto deltaTimeInClock = std::chrono::steady_clock::now() - timeStart;
//    timeStart = std::chrono::steady_clock::now();

//    auto deltaTimeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTimeInClock);
//    deltaTime = static_cast<int>(deltaTimeInMs.count());
//    deltaTime = 15;

    auto iter = std::remove_if(timers.begin(), timers.end(),
    [this, deltaTime](TimerData& timer)
    {
        if( nullptr == timer.cb )
        {
            return true; //remove
        }
        timer.elapsed += deltaTime;

        switch( timer.info )
        {
            case TimerInfo::everyOnce:
            {
                if( timer.elapsed > timer.frequency )
                {
                    timer.elapsed -= timer.frequency;
                    timer.cb();
                }
            }break;
            case TimerInfo::startAfter:
            {
                if(timer.elapsed >= timer.frequency )
                {
                    timer.cb();
                }
            }break;
            case TimerInfo::infinite:
            {
                timer.cb();
            }break;
            case TimerInfo::once:
            {
                timer.cb();
                return true; // remove
            }
            case TimerInfo::callUntil:
            {
                if(timer.elapsed <= timer.frequency)
                {
                    timer.cb();
                }
                else
                {
                    return true; // remove
                }
            }break;
        }
        return false;
    });
    timers.erase(iter, timers.end());
}
