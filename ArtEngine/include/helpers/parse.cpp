#include "../pch.h"

namespace parse
{

std::string program = "";                   //!< program name
std::vector<std::string> values;            //!< argument values
std::unordered_set<std::string> flags;      //!< argument flags
std::map<std::string, std::string> options; //!< argument options

void get(int n, char *args[])
{
    std::string arg;
    for (int i = 0; i < n; ++i)
    {
        arg = std::string(args[i]);

        // first argument should always be the program
        if (i == 0)
        {
            program = arg;
            continue;
        }
        // handle flags
        if (arg.substr(0, 2) == "--")
            flags.insert(arg.substr(2));
        // handle options
        else if (arg.substr(0, 1) == "-")
        {
            // last arg should not be an option
            if (i == n - 1)
                return;
            // move to the next argument and save the option
            options[arg.substr(1)] = std::string(args[++i]);
        }
        else // not a flag or option, save the value
        {
            values.push_back(arg);
        }
    }
}

} // namespace parse