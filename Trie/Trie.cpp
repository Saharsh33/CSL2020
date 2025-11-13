#include "Trie.h"


TrieNode *root = new TrieNode();

void freeTrie(TrieNode *node)
{
    if (!node)
        return;
    for (auto &p : node->children)
        freeTrie(p.second);
    delete node;
}

void insertToTrie(int id)//function to insert to trie
{
    if (id < 0 || id >= (int)songs.size()) return;

    string key = normalize(songs[id].title);
    
    TrieNode *cur = root;
    for (char c : key)
    {
        if (!cur->children.count(c))
            cur->children[c] = new TrieNode();
        cur = cur->children[c];
        cur->song_ids.push_back(id);
    }
}

void buildTrie()//function to build trie
{
    freeTrie(root);
    root = new TrieNode();
    for (int i = 0; i < (int)songs.size(); i++)
        insertToTrie(i);
}