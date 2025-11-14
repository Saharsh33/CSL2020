#ifndef PLAYLIST_MANAGMENT_H
#define PLAYLIST_MANAGMENT_H

#include <bits/stdc++.h>
using namespace std;

#include "../Globals/Globals.h"
#include "../SavePlaylist/SavePlaylist.h"
#include "../SearchFunc/SearchFunc.h"

// Core playlist management API (definitions in playlist_managment.cpp)
void createPlaylist();
void addSongToPlaylist();
void removeSongFromPlaylist();

// (forward declaration) showPlaylists implemented in PlaylistOps.cpp
void showPlaylists();

#endif // PLAYLIST_MANAGMENT_H