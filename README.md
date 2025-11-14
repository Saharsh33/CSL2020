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
- Cosine similarity for hot vectors
- Multi-factor scoring  
- Trending analysis
- Popularity analysis
- Diversity analysis
- Weighted score calculation 
- Max-heap based top-7 recommendation  
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

## Algorithms & Formulas (Detailed Explanation)

### **1. Cosine Similarity (Gi & Ai)**  
Cosine similarity measures how close two songs are based on their **genre vectors** and **artist vectors**.

$$
CosineSim(A,B) = \frac{A \cdot B}{||A|| \cdot ||B||}
$$

- Genres → one-hot vectors  
- Artists → multi-hot normalized vectors  
- Range: **0 to 1**

Used as:
- **Gi** = genre similarity  
- **Ai** = artist similarity  


---

### **2. Graph Edge Similarity (During Graph Build)**  
Each pair of songs gets a graph similarity edge weight:

$$
Sim = 0.5 \cdot GenreScore + 0.5 \cdot ArtistScore
$$

Where:
- GenreScore = **1.0** if genres match, else **0.3**  
- ArtistScore = **1.0** if artist tokens overlap, else **0.5**

Edges are added only when:

$$
Sim > 0.2
$$


---

### **3. Graph Similarity (Ci)**  

$$
Ci = \frac{EdgeWeight(cur,i)}{WeightMax}
$$

- **EdgeWeight(cur,i)** → direct connection in graph  
- **WeightMax** → max edge weight overall  
- If no edge exists → **Ci = 0**  


---

### **4. Popularity Score (Pn)**  

$$
Pn = \frac{\log(1 + PlayCount_i)}{\log(1 + PlayCount_{max})}
$$

- Logarithmic to reduce dominance of very-high play counts  
- Normalized **0–1**  


---

### **5. Trending Score (Ti)**  

$$
Ti = \frac{TrendingScore_i}{T_{max}}
$$

- Based on song's trending value  
- Normalized **0–1**  


---

### **6. Diversity Score (Di)**  

$$
Di = 1 - (0.5 \cdot Gi + 0.5 \cdot Ai)
$$

Purpose:
- Encourages **variety** in recommendations  
- Penalizes songs too similar to current track  


---

### **7. Final Recommendation Score (S)**  

Weighted sum of all contribution factors:

| Component           | Symbol | Weight |
|--------------------|--------|--------|
| Graph similarity   | Ci     | 0.20   |
| Popularity         | Pn     | 0.10   |
| Genre similarity   | Gi     | 0.15   |
| Artist similarity  | Ai     | 0.35   |
| Diversity          | Di     | 0.10   |
| Trending           | Ti     | 0.10   |

Final score:

$$
S = 0.20Ci + 0.10Pn + 0.15Gi + 0.35Ai + 0.10Di + 0.10Ti
$$

Higher **S** → stronger recommendation.

Top-K songs are extracted using a **max-heap**.


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
