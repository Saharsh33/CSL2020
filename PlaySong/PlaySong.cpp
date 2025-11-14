#include "PlaySong.h"

void playSong(int id)
{
    if (id < 0 || id >= (int)songs.size())
        return;
    songs[id].play_count++;
    songs[id].trending_score = songs[id].trending_score * 0.8 + 5.0;
    cout << "\n\033[33;1mNow playing:- \033[32m" << songs[id].title << " by " << songs[id].artist << "\033[0m\n";
    saveSongsToFile();

    // Show recommendations based on queue if active; otherwise use single-song fallback
    if (playlistMode)
        return;

    if (currentNode)
        computeAndShowRecommendationsFromQueue();
    else
    {
        // fallback single-song recommendation (previous behavior)
        // simulate a temporary queue of just this song
        QueueNode *savedHead = head;
        QueueNode *savedTail = tail;
        QueueNode *savedCurrent = currentNode;

        // temporary single-node queue
        head = tail = currentNode = new QueueNode(id);

        computeAndShowRecommendationsFromQueue();

        // free the temporary node and restore
        delete currentNode;
        head = savedHead;
        tail = savedTail;
        currentNode = savedCurrent;
    }
}