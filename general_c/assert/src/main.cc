#include "Check.hh"

int main()
{
    Check(true, "hello");

    double s = 2;
    double t = 4;
    Assert(s == t, "");
    Check(false, "hello");
}
