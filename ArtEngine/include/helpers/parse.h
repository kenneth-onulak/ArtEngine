#ifndef ARTENGINE_PARSE_H
#define ARTENGINE_PARSE_H

namespace parse
{

extern std::string program;                        //!< program name
extern std::vector<std::string> values;            //!< argument values
extern std::unordered_set<std::string> flags;      //!< argument flags
extern std::map<std::string, std::string> options; //!< argument options

void get(int n, char *args[]);

} // namespace parse

#endif // ARTENGINE_PARSE_H
