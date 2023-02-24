/*+*************************************************************************//*!
\file:      timer.h

\summary:   benchmark / measure execution time or provide intervals

\struct:    measure
\classes:   Timer

\functions: benchmark\n
            Timer::set_timeout\n
            Timer::set_interval\n
            Timer::set_const_interval\n
            Timer::stop\n

\origin:    ArtEngine

Copyright (c) 2023 Kenneth Onulak Jr.
MIT License
**************************************************************************//*+*/
#ifndef ARTENGINE_TIMER_H
#define ARTENGINE_TIMER_H

namespace timer
{

/*F+F***********************************************************************//*!
\function:   benchmark

\summary:  benchmark the execution time of a function

\arg:      function - function to benchmark
\arg:      args -function arguments
\arg:      output - toggle printing output, default = true

\return:   float - execution time duration count
************************************************************************//*F-F*/
template <typename D, typename F, typename... Args>
float benchmark(F function, Args &&...args, bool output = true)
{
    auto start = std::chrono::high_resolution_clock::now();
    function(args...);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<D>(stop - start);
    if (output)
        std::cout << "Execution Time: " << duration.count() << std::endl;
    return static_cast<float>(duration.count());
}

/*S+S***********************************************************************//*!
\struct:   measure

\summary:  measure the execution time between the creation and destruction of
           the object

\methods:  measure - Constructor\n
           ~measure -Destructor\n
************************************************************************//*S-S*/
template <typename D>
struct measure
{
    /*M+M*******************************************************************//*!
    \method:   measure::measure

    \summary:  constructor, starts the execution time

    \modifies: [start]
    ********************************************************************//*M-M*/
    measure()
        : start(std::chrono::high_resolution_clock::now())
    {
    }

    /*M+M*******************************************************************//*!
    \method:   measure::~measure

    \summary:  destructor, stops and prints the execution time

    \modifies: [stop]
    ********************************************************************//*M-M*/
    ~measure()
    {
        stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<D>(stop - start);
        std::cout << "Execution Time: " << duration.count() << std::endl;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start; //!< start measuring execution time
    std::chrono::time_point<std::chrono::high_resolution_clock> stop;  //!< stop measuring execution time

}; // struct measure

/*C+C***********************************************************************//*!
\class:    Timer

\summary:  execute function after a duration or on intervals in another thread

\methods:  set_timeout - execute a function with a timeout\n
        :  set_interval - execute a function on an interval\n
        :  set_const_interval - execute a function on a constant interval\n
        :  stop - stop the timer
************************************************************************//*C-C*/
template <typename D>
class Timer
{
  public:
    /*M+M*******************************************************************//*!
    \method:   Timer::set_timeout

    \summary:  execute a function after a timeout if still active

    \args:     duration - time before executing the function
    \args:     function - function to execute

    \modifies: [active, thread].
    ********************************************************************//*M-M*/
    template <typename F>
    void set_timeout(D duration, F function)
    {
        active = true;
        thread = std::thread([=]() {
            std::this_thread::sleep_for(duration);
            // thread terminated before function execution
            if (!active)
                return;
            function();
            return;
        });
        thread.detach();
    }

    /*M+M*******************************************************************//*!
    \method:   Timer::set_interval

    \summary:  execute a function on a set interval

    \args:     duration - pointer to time before executing the function
    \args:     function - function to execute
    \args:     args - specified function arguments

    \modifies: [active, thread].
    ********************************************************************//*M-M*/
    template <typename F, typename... Args>
    void set_interval(D *duration, F function, Args &&...args)
    {
        active = true;
        thread = std::thread([=]() {
            while (active)
            {
                std::this_thread::sleep_for(*duration);
                function(args...);
            }
            return;
        });
        thread.detach();
    }

    /*M+M*******************************************************************//*!
    \method:   Timer::set_const_interval

    \summary:  execute a function on a set constant interval

    \args:     duration - pointer to time before executing the function
    \args:     function - function to execute
    \args:     args - specified function arguments

    \modifies: [active, thread, delay_time].
    ********************************************************************//*M-M*/
    template <typename F, typename... Args>
    void set_const_interval(D *duration, F function, Args &&...args)
    {
        active = true;
        thread = std::thread([=]() {
            while (active)
            {
                std::this_thread::sleep_for(*duration - delay_time);
                curr_time = std::chrono::high_resolution_clock::now();
                function(args...);
                delay_time = std::chrono::duration_cast<D>(std::chrono::high_resolution_clock::now() - curr_time);
            }
            return;
        });
        thread.detach();
    }

    /*M+M*******************************************************************//*!
    \method:   Timer::stop

    \summary:  stop the process

    \modifies: [active, thread]]
    ********************************************************************//*M-M*/
    void stop()
    {
        // stop the process and join the thread
        active = false;
        if (thread.joinable())
            thread.join();
    }

  private:
    std::atomic<bool> active = false;                                      //!< finish the timer
    std::chrono::time_point<std::chrono::high_resolution_clock> curr_time; //!< track execution time
    D delay_time = D(0);                                                   //!< delay time for a constant interval
    std::thread thread;                                                    //!< thread for the timer

}; // class Timer

} // namespace timer

#endif // ARTENGINE_TIMER_H
