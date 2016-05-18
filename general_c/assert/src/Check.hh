#ifndef Check_hh
#define Check_hh

#include <string>

namespace ch_ns
{
    using std::string;
    
    void check(string condition,
               string message,
               string file,
               int line);
}

// Check only happens in debug
#ifdef NDEBUG
#  define Check(condition, description)
#else
#  define Check(cond, desc)                                     \
    if (!(cond)) ch_ns::check(#cond, desc, __FILE__, __LINE__)
#endif

// Assert always happens
#define Assert(cond, desc)                                      \
    if (!(cond)) ch_ns::check(#cond, desc, __FILE__, __LINE__)

#endif
