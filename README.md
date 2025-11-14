# Music Management & Recommendation System
![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Contributions](https://img.shields.io/badge/contributions-welcome-orange.svg)
![Project Status](https://img.shields.io/badge/status-active-success.svg)

A high-performance C++17 music management application featuring intelligent song recommendations powered by graph-based similarity algorithms, advanced data structures, and efficient caching mechanisms.

**CSL2020 Data Structures & Algorithms - Major Project**  
*Indian Institute of Technology Jodhpur*

## Overview
This system provides a comprehensive solution for managing music libraries with smart recommendations. It combines multiple data structures and algorithms to deliver fast search, efficient playlist management, and personalized song suggestions.

## Features

### Core Functionality
- Music Library Management  
- Playlist Creation & Editing  
- Dynamic Playback Queue  
- Smart Prefix Search using Trie  
- Artist Tokenization & Multi-Artist Support  
- Persistent Storage  

### Recommendation Engine
- Graph-based similarity  
- Multi-factor scoring  
- Trending analysis  
- Max-heap based top-K recommendation  
- Cached graph  

## Architecture

### Data Structures Used
| Structure | Purpose | Complexity |
|----------|---------|------------|
| Doubly Linked List | Playlist ops | O(1) |
| Circular Queue | Playback | O(1) |
| Trie | Prefix search | O(m) |
| Hash Maps | Indexing | O(1) |
| Graph | Similarity graph | O(V+E) |
| Max-Heap | Top-K | O(n log k) |
| Binary Cache | Persistence | O(1) |

### Main Components
Globals, Playlist Management, PlaylistOps, String Helpers, Artist Tokenization, SaveSong, SavePlaylist, GraphCache, Trie, SearchFunc, Recommendation, QueueManagement, PlaySong, QueueNavigation

## Algorithms & Formulas (Exact)

### 1. Cosine Similarity
CosineSim(A,B) = (A·B)/(||A||·||B||)

### 2. Graph Edge Similarity
Sim = 0.5*GenreScore + 0.5*ArtistScore

### 3. Graph Similarity (Ci)
Ci = EdgeWeight(cur,i) / Wmax

### 4. Popularity Score
Pn = log(1+PlayCount)/log(1+Pmax)

### 5. Trending Score
Ti = TrendingScore_i / Tmax

### 6. Diversity Score
Di = 1 - (0.5Gi + 0.5Ai)

### 7. Final Score
S = 0.20Ci + 0.10Pn + 0.15Gi + 0.35Ai + 0.10Di + 0.10Ti

## Build Instructions

### macOS / Linux
```bash
git clone https://github.com/Saharsh33/CSL2020.git
cd CSL2020

g++ -std=c++17 main.cpp     Globals/Globals.cpp     playlist_management/playlist_managment.cpp     PlaylistOps/PlaylistOps.cpp     String_helpers/String_helpers.cpp     Artist_Tokenization/Artist_tokenization.cpp     SaveSong/SaveSong.cpp     SavePlaylist/SavePlaylist.cpp     GraphCache/GraphCache.cpp     Trie/Trie.cpp     SearchFunc/SearchFunc.cpp     Recommendation/Recommendation.cpp     Queue_Management/QManage.cpp     PlaySong/PlaySong.cpp     QueueNavigation/QNav.cpp     -o musicplayer

./musicplayer
```

### Windows (PowerShell)
```powershell
git clone https://github.com/Saharsh33/CSL2020.git
cd CSL2020

g++ -std=c++17 main.cpp `
    Globals/Globals.cpp `
    playlist_management/playlist_managment.cpp `
    PlaylistOps/PlaylistOps.cpp `
    String_helpers/String_helpers.cpp `
    Artist_Tokenization/Artist_tokenization.cpp `
    SaveSong/SaveSong.cpp `
    SavePlaylist/SavePlaylist.cpp `
    GraphCache/GraphCache.cpp `
    Trie/Trie.cpp `
    SearchFunc/SearchFunc.cpp `
    Recommendation/Recommendation.cpp `
    Queue_Management/QManage.cpp `
    PlaySong/PlaySong.cpp `
    QueueNavigation/QNav.cpp `
    -o musicplayer.exe

.\musicplayer.exe
```

### Single-Line Build
```bash
g++ -std=c++17 main.cpp Globals/Globals.cpp playlist_management/playlist_managment.cpp PlaylistOps/PlaylistOps.cpp String_helpers/String_helpers.cpp Artist_Tokenization/Artist_tokenization.cpp SaveSong/SaveSong.cpp SavePlaylist/SavePlaylist.cpp GraphCache/GraphCache.cpp Trie/Trie.cpp SearchFunc/SearchFunc.cpp Recommendation/Recommendation.cpp Queue_Management/QManage.cpp PlaySong/PlaySong.cpp QueueNavigation/QNav.cpp -o musicplayer && ./musicplayer
```

## Usage
- Add/View/Edit songs  
- Prefix-based search  
- Create/Merge/Edit playlists  
- Playback navigation  
- Smart Recommendations  
- Trending songs  
- Save/Load data  

## Project Members
- Saharsh Thakor — B24CS1105  
- Aditya Ranjan — B24CM1004  
- Pal Vaghasiya — B24CS1078  
- Vishwajeet Parmar — B24CS1089  

## Repository
https://github.com/Saharsh33/CSL2020
