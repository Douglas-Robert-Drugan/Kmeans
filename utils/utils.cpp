#include "utils.hpp"

std::istream & utils::safeGetline(std::istream & is, std::string & t)
{
    t.clear();
    //chars in stream read one by one with streambuf
    //sentry object performs guards for thread synchronization

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for (;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if (sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            if (t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

std::string utils::removeTrailingZeros(std::string s)
{
    int i = 0;
    while (s[i] == '0') {
        i++;
    }
    //apply erase function
    s.erase(0, i);
    return s;
}