#ifndef ARTENGINE_LOG_H
#define ARTENGINE_LOG_H

namespace my_log
{

extern bool is_debug;   //!< use debug mode
extern std::string key; //!< type of log

////////////////////////////////////////////////////////////////////////////////
//// RAW DATA OUTPUT
////////////////////////////////////////////////////////////////////////////////

void raw();

template <typename T>
void raw(T message)
{
    std::cout << message << std::endl;
}

template <typename T, typename... Args>
void raw(T message, Args... args)
{
    std::cout << message;
    raw(args...);
}

////////////////////////////////////////////////////////////////////////////////
//// STANDARD OUTPUT
////////////////////////////////////////////////////////////////////////////////

template <typename T>
void out(T message)
{
    std::cout << "[" << key << "] ";
    raw(message);
}

template <typename T, typename... Args>
void out(T message, Args... args)
{
    std::cout << "[" << key << "] ";
    raw(message, args...);
}

////////////////////////////////////////////////////////////////////////////////
//// ERROR OUTPUT
////////////////////////////////////////////////////////////////////////////////

template <typename T>
void error(T message)
{
    std::cout << "[ERROR] ";
    raw(message);
}

template <typename T, typename... Args>
void error(T message, Args... args)
{
    std::cout << "[ERROR] ";
    raw(message, args...);
}

////////////////////////////////////////////////////////////////////////////////
//// DEBUG OUTPUT
////////////////////////////////////////////////////////////////////////////////

template <typename... Args>
void debug(Args... args)
{
    if (!is_debug)
        return;
    std::cout << "[DEBUG] ";
    raw(args...);
}

template <typename... Args>
void debug(bool condition, Args... args)
{
    if (!condition)
        return; // failed the debug condition
    std::cout << "[DEBUG] ";
    raw(args...);
}

template <typename T>
void progress(T d, T D)
{
    if (d != 0)
        std::cout << "\n";
    std::cout << "[" << d << "/" << D << "][";

    for (int i = 0; i < 25; ++i)
    {
        if (i < 25 * static_cast<float>(d) / static_cast<float>(D))
            std::cout << "#";
        else
            std::cout << "-";
    }
    std::cout << "]";
    if (d == D - 1)
        std::cout << "\n";
    std::cout << std::flush;
}

} // namespace log

#endif // ARTENGINE_LOG_H
