#include "Artist_tokenization.h"

vector<string> splitArtistTokens(const string &raw)
{
    string s = toLowerCopy(raw);

    vector<string> patterns = {
        "feat.", "featuring", "ft.", "ft", "with", "x", 
        "&", "/", ",", " and "
    };

    for (auto &p : patterns)
    {
        size_t pos = 0;
        while ((pos = s.find(p, pos)) != string::npos)
        {
            s.replace(pos, p.size(), ",");
            pos++;
        }
    }

    vector<string> tokens;
    string token;
    stringstream ss(s);

    while (getline(ss, token, ','))
    {
        token = trim_copy(token);
        if (!token.empty())
            tokens.push_back(token);
    }

    unordered_set<string> seen;
    vector<string> result;

    for (auto &t : tokens)
        if (seen.insert(t).second)
            result.push_back(t);

    return result;
}

bool artistTokensIntersect(const string &a, const string &b)
{
    auto ta = splitArtistTokens(a);
    auto tb = splitArtistTokens(b);

    unordered_set<string> A(ta.begin(), ta.end());

    for (auto &t : tb)
        if (A.count(t))
            return true;

    return false;
}