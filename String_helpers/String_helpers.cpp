#include "String_helpers.h"

string trim_copy(string s)
{
    while (!s.empty() && isspace((unsigned char)s.front()))
        s.erase(s.begin());
    while (!s.empty() && isspace((unsigned char)s.back()))
        s.pop_back();
    return s;
}

string toLowerCopy(const string &s)
{
    string out;
    for (char c : s)
        out.push_back(tolower((unsigned char)c));
    return out;
}

string normalize(const string &s)
{
    string r;
    for (char c : s)
    {
        if (isalnum((unsigned char)c))
            r.push_back(tolower((unsigned char)c));
        else if (c == ' ')
            r.push_back(' ');
    }
    return r;
}