#ifndef GLOBALS_H
#define GLOBALS_H

#include <bits/stdc++.h>
using namespace std;

// STRUCTS
struct Song
{
    int id;
    string title;
    string artist;
    string genre;
    long long play_count;
    double trending_score;
};

struct PLNode
{
    int song_id;
    PLNode* next;
    PLNode* prev;
    PLNode(int id) : song_id(id), next(nullptr), prev(nullptr) {}
};

struct QueueNode
{
    int song_id;
    QueueNode *prev;
    QueueNode *next;
    QueueNode(int id) : song_id(id), prev(nullptr), next(nullptr) {}
};

// Global Variables
extern vector<Song> songs;
extern string songsFile;
extern string playlistFile;
extern string graphCacheFile;
extern unordered_map<string, vector<int>> playlists;

extern unordered_map<string, int> genreIndex;
extern unordered_map<string, int> artistIndex;
extern int GENRE_DIM;
extern int ARTIST_DIM;

extern unordered_map<int, vector<pair<int, double>>> graph;
extern string currentPlaylist;
extern int currentSongIndex;
extern bool playlistMode;

extern QueueNode *head;
extern QueueNode *tail;
extern QueueNode *currentNode;

#endif