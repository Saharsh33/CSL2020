#include "Globals.h"

// Definations of global variables
vector<Song> songs;
string songsFile = "songs.txt";
string playlistFile = "playlists.txt";
string graphCacheFile = "graph_cache.dat";
unordered_map<string, vector<int>> playlists;

unordered_map<string, int> genreIndex;
unordered_map<string, int> artistIndex;
int GENRE_DIM = 0, ARTIST_DIM = 0;

unordered_map<int, vector<pair<int, double>>> graph;
string currentPlaylist = "";
int currentSongIndex = -1;
bool playlistMode = false;

QueueNode *head = nullptr;
QueueNode *tail = nullptr;
QueueNode *currentNode = nullptr;