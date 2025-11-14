#include "PlaylistOps.h"

//shows playlist, lets user to play songs in loop by building a circular doubly linked-list
void showPlaylists()
{
    if (playlists.empty())
    {
        cout << "No playlists yet.\n";
        return;
    }

    cout << "\n\033[1;34;4mPlaylists:\033[0m\n";
    int index = 1;
    vector<string> names;
    for (auto &p : playlists)
    {
        cout <<"\033[1;36m"<< index++ << ") " << p.first << " (" << p.second.size() << " songs)\033[0m\n";
        names.push_back(p.first);
    }

    cout << "\nEnter playlist number to view (0 to skip): ";
    int choice;
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(999, '\n');
        return;
    }
    cin.ignore();
    if (choice <= 0 || choice > (int)names.size())
        return;

    string selected = names[choice - 1];
    auto &list = playlists[selected];
    if (list.empty())
    {
        cout << "Playlist '" << selected << "' is empty.\n";
        return;
    }

    cout << "\n\033[1;34;4mSongs in '" << selected << "':\033[0m\n";
    for (size_t i = 0; i < list.size(); i++)
        cout <<"\033[1;36m"<< i + 1 << ") " << songs[list[i]].title << " - " << songs[list[i]].artist << "\033[0m\n";

    cout << "\n\033[1;33mDo you want to play this playlist? (\033[1;32my\033[1;33m/\033[1;31mn\033[1;33m): \033[0m";
    char ch;
    cin >> ch;
    cin.ignore();

    if (tolower(ch) == 'y')
    {
        currentPlaylist = selected;
        currentSongIndex = 0;

        auto &listRef = playlists[currentPlaylist];

        playlistMode = true;

        PLNode* headP = nullptr;
        PLNode* prevP = nullptr;

        for (int id : listRef)
        {
            PLNode* node = new PLNode(id);
            if (!headP)
            {
                headP = node;
                prevP = node;
            }
            else
            {
                prevP->next = node;
                node->prev = prevP;
                prevP = node;
            }
        }

        if (prevP && headP)
        {
            prevP->next = headP;
            headP->prev = prevP;
        }

        PLNode* cur = headP;
        if (!cur)
        {
            cout << "Playlist empty.\n";
            playlistMode = false;
            return;
        }

        while (true)
        {
            cout << "\033[2J\033[1;1H";
            cout<<"\n";
            playSong(cur->song_id);

            cout << "\nOptions: \033[1;32m[N]\033[0mext  \033[1;37m[P]\033[0mrev  \033[31;1m[Q]\033[0muit Playlist\nChoose: ";
            char c;
            if (!(cin >> c))
            {
                cin.clear();
                cin.ignore(999, '\n');
                break;
            }
            cin.ignore();
            c = tolower(c);

            if (c == 'n')
            {
                cout << "\033[2J\033[1;1H";
                cout<<"\n";
                cur = cur->next;
            }
            else if (c == 'p')
            {
                cout << "\033[2J\033[1;1H";
                cout<<"\n";
                cur = cur->prev;
            }
            else if (c == 'q')
            {
                cout << "\033[2J\033[1;1H";
                cout<<"\n";
                cout << "Stopped playlist.\n";
                break;
            }
            else
            {
                cout << "Invalid Command.\n";
            }
        }

        if (headP)
        {
            PLNode* temp = headP->next;
            while (temp != nullptr && temp != headP)
            {
                PLNode* nxt = temp->next;
                delete temp;
                temp = nxt;
            }
            delete headP;
        }

        playlistMode = false;
    }
}