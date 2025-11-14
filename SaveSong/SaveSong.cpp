#include "SaveSong.h"

//function to save song
void saveSongsToFile()
{
    ofstream file(songsFile);
    for (auto &s : songs)
    {
        file << s.title << "," 
             << s.artist << "," 
             << s.genre << ","
             << s.play_count << "," 
             << s.trending_score << "\n";
    }
}

//function to load song
void loadSongsFromFile(const string &filename)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "No songs file found.\n";
        return;
    }

    songs.clear();
    string line;
    int count = 0;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string title, artist, genre, play_str, trend_str;

        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');
        getline(ss, play_str, ',');
        getline(ss, trend_str, ',');

        long long pc = 0;
        double ts = 0.0;

        try { pc = stoll(play_str); }
        catch (...) { pc = 0; }

        try { ts = stod(trend_str); }
        catch (...) { ts = 0.0; }

        songs.push_back({count++, title, artist, genre, pc, ts});
    }

    cout << "Loaded " << songs.size() << " songs.\n";
}