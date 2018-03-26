//
// Created by pbrink on 25/03/18.
//

#ifndef SENSOR_COMMUNICATION_CALLBACKTIMER_H
#define SENSOR_COMMUNICATION_CALLBACKTIMER_H

#include <atomic>
#include <chrono>
#include <functional>
#include <thread>

class CallBackTimer
{
public:
    CallBackTimer() :_execute(false) {}

    ~CallBackTimer() {
        if( _execute.load(std::memory_order_acquire) ) {
            stop();
        };
    }

    void stop()
    {
        _execute.store(false, std::memory_order_release);
        if( _thd.joinable() )
            _thd.join();
    }

    void start(int interval, std::function<void(void)> func)
    {
        if( _execute.load(std::memory_order_acquire) ) {
            stop();
        };
        _execute.store(true, std::memory_order_release);
        _thd = std::thread([this, interval, func]()
                           {
                               while (_execute.load(std::memory_order_acquire)) {
                                   func();
                                   std::this_thread::sleep_for(
                                           std::chrono::milliseconds(interval));
                               }
                           });
    }

    bool is_running() const noexcept {
        return ( _execute.load(std::memory_order_acquire) &&
                 _thd.joinable() );
    }

private:
    std::atomic<bool> _execute;
    std::thread _thd;
};

#endif //SENSOR_COMMUNICATION_CALLBACKTIMER_H
