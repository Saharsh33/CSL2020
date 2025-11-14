#include <bits/stdc++.h>
#include "./Globals/Globals.h"
#include "./playlist_management/playlist_managment.h"
#include "./String_helpers/String_helpers.h"
#include "./Artist_Tokenization/Artist_tokenization.h"
#include "./SaveSong/SaveSong.h"
#include "./SavePlaylist/SavePlaylist.h"
#include "./GraphCache/GraphCache.h"
#include "./Trie/Trie.h"
#include "./SearchFunc/SearchFunc.h"
#include "./Recommendation/Recommendation.h"
#include "./Queue_Management/QManage.h"
#include "./PlaySong/PlaySong.h"
#include "./QueueNavigation/QNav.h"
#include "./PlaylistOps/PlaylistOps.h"
using namespace std;

void clearTerminal() {
cout << "\033[2J\033[1;1H";
cout<<"\n";
}

void searchAndPlaySong()
{
    cout << "Enter song title to search: ";
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
        cout << "\n\033[31;1mNo results.\033[0m\n";
        return;
    }
    for (int i = 0; i < (int)res.size(); i++)
        cout <<"\n\033[36;1m"<< i + 1 << ") " << songs[res[i]].title << " - " << songs[res[i]].artist << "\033[0m\n";
    cout << "\n\033[33;1mEnter number to add to queue (0 to cancel): \033[0m";
    int idx;
    if (!(cin >> idx))
    {
        cin.clear();
        cin.ignore(999, '\n');
        return;
    }
    cin.ignore();
    if (idx >= 1 && idx <= (int)res.size())
    {
        int chosen = res[idx - 1];
        bool wasEmpty = enqueueSong(chosen);
        cout << "\033[2J\033[1;1H";
        cout<<"\n";
        cout << "\033[32;1mAdded to queue: " << songs[chosen].title << " - " << songs[chosen].artist << "\033[0m\n";
        if (wasEmpty)
        {
            // If queue was empty, start playing immediately
            playSong(currentNode->song_id);
        }

        // Navigation loop after adding to queue
        cout << "\n\033[1;33;4mQueue Navigation Active\033[0m\n";
        cout << "\n\033[33;1mCommands: [N]ext | [P]revious | [A]dd more songs | [M]ain menu\033[0m\n";

        while (true)
        {
            cout << "\n\033[33;1;4mEnter command (N/P/A/M): \033[0m";
            char cmd;
            cin >> cmd;
            cin.ignore();
            cmd = tolower(cmd);

            if (cmd == 'n')
            {
                clearTerminal();
                cout << "Playing next song...\n";
                queueNext();
            }
            else if (cmd == 'p')
            {
                clearTerminal();
                cout << "\n\033[37;1mPlaying previous song...\033[0m\n";
                queuePrev();
            }
            else if (cmd == 'a')
            {
                clearTerminal();
                // Add more songs to queue
                cout << "\nEnter song title to search: ";
                string newQ;
                getline(cin, newQ);
                if (!newQ.empty())
                {
                    auto newRes = searchSongTop7(newQ);
                    if (!newRes.empty())
                    {
                        for (int i = 0; i < (int)newRes.size(); i++)
                            cout << i + 1 << ") " << songs[newRes[i]].title << " - " << songs[newRes[i]].artist << "\n";
                        cout << "Enter number to add to queue (0 to skip): ";
                        int newIdx;
                        if (cin >> newIdx && newIdx >= 1 && newIdx <= (int)newRes.size())
                        {
                            enqueueSong(newRes[newIdx - 1]);
                            cout << "Added: " << songs[newRes[newIdx - 1]].title << "\n";
                        }
                        cin.ignore();
                    }
                    else
                    {
                        cout << "\n\033[31;1mNo results found.\n\033[0m\n";
                    }
                }
            }
            else if (cmd == 'm')
            {
                clearTerminal();
                cout << "Returning to main menu...\n";
                break;
            }
            else
            {
                clearTerminal();
                cout << "\033[31;1mInvalid command. Use N/P/A/M.\033[0m\n";
            }
        }
    }
    else
    {
        cout << "Cancelled.\n";
    }
}

// =====================================================
// MAIN MENU
// =====================================================
int main()
{
    // cout << "Enter filename to load songs (default songs.txt): ";
    // string filename=songsFile;
    // getline(cin, filename);
    // if (filename.empty())
    //     filename = songsFile;

    loadSongsFromFile(songsFile);
    loadPlaylists();
    buildFeatureVectors();
    buildTrie();

    // Try to load graph from cache first
    cout << "Checking for graph cache...\n";
    if (loadGraphCache())
    {
        cout << "✓ Graph loaded from cache (" << graphCacheFile << ") - Fast startup!\n";
    }
    else
    {
        cout << "No cache found. Building graph from scratch (this may take a few minutes for large datasets)...\n";
        buildGraph();
    }

    while (true)
    {
        cout << "\033[36;1m\n========= MUSIC PLAYER MENU =========\n";
        cout << "1. Search & Add to Queue (with Navigation)\n";
        cout << "2. View + Play Playlist\n";
        cout << "3. Create Playlist\n";
        cout << "4. Add Song to Playlist\n";
        cout << "5. Remove Song from Playlist\n";
        cout << "6. Next Song (Queue)\n";
        cout << "7. Previous Song (Queue)\n";
        cout << "8. Rebuild Graph Cache\n";
        cout << "9. Exit\n";
        cout << "=====================================\nChoose: \033[0m";

        int ch;
        if (!(cin >> ch))
            break;
        cin.ignore();

        if (ch == 1){
            clearTerminal();
            searchAndPlaySong();
        }
        else if (ch == 2){
            clearTerminal();
            showPlaylists();
        }
        else if (ch == 3){
            clearTerminal();
            createPlaylist();
        }
        else if (ch == 4){
            clearTerminal();
            addSongToPlaylist();
        }
        else if (ch == 5){
            clearTerminal();
            removeSongFromPlaylist();
        }
        else if (ch == 6){
            clearTerminal();
            queueNext();
        }
        else if (ch == 7){
            clearTerminal();
            queuePrev();
        }
        else if (ch == 8)
        {
            clearTerminal();
            cout << "Rebuilding graph cache...\n";
            buildGraph();
            cout << "Graph cache rebuilt successfully!\n";
        }
        else if (ch == 9)
        {
            cout << "Exiting...\n";
            break;
        }
        else
            cout << "Invalid.\n";
    }
    freeTrie(root);

    // Cleanup linked list nodes
    QueueNode *cur = head;
    while (cur)
    {
        QueueNode *tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    clearTerminal();
    return 0;
}