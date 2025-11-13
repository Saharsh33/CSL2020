#ifndef TRIE_H
#define TRIE_H

#include <bits/stdc++.h>
using namespace std;

#include "../Globals/Globals.h"
#include "../String_helpers/String_helpers.h"

struct TrieNode
{
    unordered_map<char, TrieNode *> children;
    vector<int> song_ids;

    TrieNode() = default;
};

extern TrieNode *root;

// function declarations
void freeTrie(TrieNode *node);
void insertToTrie(int id);
void buildTrie();

#endif