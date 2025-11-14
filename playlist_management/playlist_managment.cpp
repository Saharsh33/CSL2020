#include "playlist_managment.h"

// Create a new playlist (asks user for name)
void createPlaylist()
{
    cout << "Enter new playlist name: ";
    string n;
    getline(cin, n);
    if (n.empty())
    {
        cout << "Cancelled: empty name.\n";
        return;
    }
    if (playlists.count(n))
    {
        cout << "Playlist already exists.\n";
        return;
    }
    playlists[n] = {};
    savePlaylists();
    cout << "Created playlist: " << n << "\n";
}

// Add a song to an existing playlist (searches by title)
void addSongToPlaylist()
{
    cout << "Enter playlist name: ";
    string n;
    getline(cin, n);
    if (!playlists.count(n))
    {
        cout << "Playlist not found.\n";
        return;
    }

    cout << "Enter song title to search and add: ";
    string q;
    getline(cin, q);
    if (q.empty())
    {
        cout << "Empty query.\n";
        return;
    }

    auto res = searchSongTop7(q);
    if (res.empty())
    {
        cout << "No matches found.\n";
        return;
    }

    cout << "Matches:\n";
    for (int i = 0; i < (int)res.size(); ++i)
        cout << i + 1 << ") " << songs[res[i]].title << " - " << songs[res[i]].artist << "\n";

    cout << "Enter number to add (0 to cancel): ";
    int sel;
    if (!(cin >> sel))
    {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Cancelled.\n";
        return;
    }
    cin.ignore();

    if (sel < 1 || sel > (int)res.size())
    {
        cout << "Invalid selection. Cancelled.\n";
        return;
    }

    playlists[n].push_back(res[sel - 1]);
    savePlaylists();
    cout << "Added: " << songs[res[sel - 1]].title << " to playlist '" << n << "'.\n";
}

// Remove a song from a playlist by index (user chooses)
void removeSongFromPlaylist()
{
    cout << "Enter playlist name: ";
    string n;
    getline(cin, n);
    if (!playlists.count(n))
    {
        cout << "Playlist not found.\n";
        return;
    }

    auto &list = playlists[n];
    if (list.empty())
    {
        cout << "Playlist is empty.\n";
        return;
    }

    cout << "Songs in '" << n << "':\n";
    for (int i = 0; i < (int)list.size(); ++i)
        cout << i + 1 << ") " << songs[list[i]].title << " - " << songs[list[i]].artist << "\n";

    cout << "Enter number to remove (0 to cancel): ";
    int sel;
    if (!(cin >> sel))
    {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Cancelled.\n";
        return;
    }
    cin.ignore();

    if (sel < 1 || sel > (int)list.size())
    {
        cout << "Invalid selection. Cancelled.\n";
        return;
    }

    int removedId = list[sel - 1];
    list.erase(list.begin() + sel - 1);
    savePlaylists();
    cout << "Removed: " << songs[removedId].title << " from playlist '" << n << "'.\n";
}