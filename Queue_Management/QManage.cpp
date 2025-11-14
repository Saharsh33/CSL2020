#include "QManage.h"

//function to add song in the queue
bool enqueueSong(int id)
{
    QueueNode *node = new QueueNode(id);
    bool wasEmpty = (head == nullptr);
    if (wasEmpty)
    {
        head = tail = currentNode = node;
    }
    else
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    return wasEmpty;
}

//function to check whether the song exists
bool isInQueue(int id)
{
    QueueNode *t = head;
    while (t)
    {
        if (t->song_id == id)
            return true;
        t = t->next;
    }
    return false;
}

//function to get recommended songs from the currently playing and remaining songs
vector<int> getQueueBasedRecommendations()
{
    vector<int> context;
    QueueNode *t = currentNode;
    if (!t)
        return {};
    while (t)
    {
        context.push_back(t->song_id);
        t = t->next;
    }
    if (context.empty())
        return {};

    double Pmax = 1.0, Tmax = 1.0, Wmax = 1.0;
    for (auto &s : songs)
    {
        Pmax = max(Pmax, (double)s.play_count);
        Tmax = max(Tmax, s.trending_score);
    }
    for (auto &kv : graph)
        for (auto &e : kv.second)
            Wmax = max(Wmax, e.second);

    unordered_map<int, double> finalScore;
    for (int cand = 0; cand < (int)songs.size(); ++cand)
    {
        bool skip = false;
        for (int x : context)
            if (x == cand)
            {
                skip = true;
                break;
            }
        if (skip)
            continue;

        double weight = 1.0;
        double totalW = 0.0;
        double weightedSum = 0.0;

        for (size_t k = 0; k < context.size(); ++k)
        {
            int ctx = context[k];
            double S = computePairRecommendationScore(ctx, cand, Pmax, Tmax, Wmax);
            weightedSum += S * weight;
            totalW += weight;
            weight *= 0.85;
        }
        if (totalW > 0)
            finalScore[cand] = weightedSum / totalW;
        else
            finalScore[cand] = 0.0;
    }

    vector<pair<double, int>> ranked;
    for (auto &p : finalScore)
        ranked.push_back({p.second, p.first});
    sort(ranked.rbegin(), ranked.rend());

    vector<int> result;
    for (auto &p : ranked)
        result.push_back(p.second);
    return result;
}

//function to get recommended songs
int getTopRecommendedSong()
{
    auto recs = getQueueBasedRecommendations();
    for (int id : recs)
    {
        if (!isInQueue(id))
            return id;
    }

    for (int i = 0; i < (int)songs.size(); ++i)
    {
        if (!isInQueue(i))
            return i;
    }

    return songs.empty() ? -1 : 0;
}

//computing recommendation score
void computeAndShowRecommendationsFromQueue()
{
    if (!currentNode)
        return;

    auto recs = getQueueBasedRecommendations();

    cout << "\n\033[34;1mRecommended Songs Based On Queue (current + remaining):\033[0m\n";

    double Pmax = 1.0, Tmax = 1.0, Wmax = 1.0;
    for (auto &s : songs)
    {
        Pmax = max(Pmax, (double)s.play_count);
        Tmax = max(Tmax, s.trending_score);
    }
    for (auto &kv : graph)
        for (auto &e : kv.second)
            Wmax = max(Wmax, e.second);

    int shown = 0;
    for (int id : recs)
    {
        double score = 0.0;

        vector<int> context;
        QueueNode *t = currentNode;
        while (t)
        {
            context.push_back(t->song_id);
            t = t->next;
        }

        double total = 0, cnt = 0;
        for (int ctx : context)
        {
            total += computePairRecommendationScore(ctx, id, Pmax, Tmax, Wmax);
            cnt++;
        }
        if (cnt > 0)
            score = total / cnt;

        cout << "\033[36;1m" << ++shown << ") \033[0m"
             << "\033[36;1m" << songs[id].title << " - " << songs[id].artist
             << "  [Score: " << fixed << setprecision(3) << score << "]\033[0m\n";

        if (shown >= 5)
            break;
    }

    if (shown == 0)
        cout << "No recommendations available.\n";
}