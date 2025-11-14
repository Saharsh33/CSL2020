#ifndef SEARCH_FUNC_H
#define SEARCH_FUNC_H

#include <bits/stdc++.h>
using namespace std;

#include "../Trie/Trie.h"
#include "../String_helpers/String_helpers.h"
#include "../Globals/Globals.h"

// returns up to top 7 matching song IDs for a prefix
vector<int> searchSongTop7(const string &prefix);

#endif