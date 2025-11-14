#include "QNav.h"

//navigating through songs
void queuePrev()
{
    if (!currentNode)
    {
        cout << "Queue empty.\n";
        return;
    }
    if (currentNode->prev)
    {
        currentNode = currentNode->prev;
        playSong(currentNode->song_id);
    }
    else
    {
        cout << "\n\033[32;1mStart of queue reached!!\n\033[0m\n";
    }
}

void queueNext()
{
    if (!currentNode)
    {
        cout << "Queue empty.\n";
        return;
    }
    if (currentNode->next)
    {
        currentNode = currentNode->next;
        playSong(currentNode->song_id);
        return;
    }
    
    // End of queue: autoplay top recommendation
    cout << "\033[31;1mEnd of queue reached. Auto-playing recommended song...\033[0m\n";
    int nextSong = getTopRecommendedSong();
    if (nextSong == -1)
    {
        cout << "No songs available to autoplay.\n";
        return;
    }
    enqueueSong(nextSong); // append
    currentNode = tail;    // move to newly added node
    playSong(currentNode->song_id);
}