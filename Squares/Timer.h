#pragma once
#include <functional>
#include <vector>
#include <chrono>
#include <memory>

class Timer
{
public:
    using Ptr = std::shared_ptr<Timer>;
    using Callback = std::function<void()>;

    void Once(Callback cb);
    void CallInfinite(Callback cb);
    void EveryOnce(int time, Callback cb);
    void StartAfter(int time, Callback cb);
    void CallUntil(int time, Callback cb);
    void StopTimer(uint64_t timerId);

    void Update(int deltaTime);
private:
    enum class TimerInfo { everyOnce, startAfter, callUntil, once, infinite };
    struct TimerData
    {
        uint64_t timerId = 0;
        TimerInfo info;
        int elapsed = 0;
        int frequency = 0;
        Callback cb;
    };

    std::vector<TimerData> timers;
};
