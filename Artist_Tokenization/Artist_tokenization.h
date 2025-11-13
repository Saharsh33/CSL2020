#ifndef ARTIST_TOKENIZATION_H
#define ARTIST_TOKENIZATION_H

#include <bits/stdc++.h>
using namespace std;

// Needed because we use trim_copy and toLowerCopy
#include "../String_helpers/String_helpers.h"

// declares functions
vector<string> splitArtistTokens(const string &raw);
bool artistTokensIntersect(const string &a, const string &b);

#endif