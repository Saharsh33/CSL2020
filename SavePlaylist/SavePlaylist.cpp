#include "SavePlaylist.h"

void savePlaylists()
{
    ofstream f(playlistFile);
    if (!f)
    {
        cout << "Error: cannot open playlist file.\n";
        return;
    }

    for (auto &p : playlists)
    {
        f << p.first << "\n";   // playlist name

        for (int i = 0; i < (int)p.second.size(); i++)
        {
            f << p.second[i];
            if (i < (int)p.second.size() - 1)
                f << ",";
        }

        f << "\n"; // newline after each playlist
    }
}

void loadPlaylists()
{
    ifstream f(playlistFile);
    if (!f)
        return;  // no playlist file yet

    playlists.clear();

    string name, line;

    while (getline(f, name))
    {
        if (name.empty())
            continue;

        if (!getline(f, line))
            break;

        stringstream ss(line);
        vector<int> ids;
        string idStr;

        while (getline(ss, idStr, ','))
        {
            try
            {
                ids.push_back(stoi(idStr));
            }
            catch (...) {}
        }

        playlists[name] = ids;
    }
}