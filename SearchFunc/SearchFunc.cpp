#include "SearchFunc.h"

vector<int> searchSongTop7(const string &prefix)
{
    string key = normalize(prefix);//prefix to search
    TrieNode *cur = root;
    for (char c : key)
    {
        if (!cur->children.count(c))
            return {};
        cur = cur->children[c];
    }
    double maxTrend = 1.0;
    for (auto &s : songs)
        maxTrend = max(maxTrend, s.trending_score);

    // max-heap by score; pair.first = score, pair.second = id
    priority_queue<pair<double, int>> pq;

    string prefixLower = toLowerCopy(prefix);

    for (int id : cur->song_ids)
    {
        if (id < 0 || id >= (int)songs.size()) continue;

        string title = toLowerCopy(songs[id].title);
        double matchScore = 0.0;

        if (title == prefixLower)
            matchScore = 1.0;
        else if (title.find(prefixLower) == 0)
            matchScore = 0.8;
        else if (title.find(prefixLower) != string::npos)
            matchScore = 0.5;
        else
            matchScore = 0.2;

        double trendNorm = maxTrend > 0.0 ? (songs[id].trending_score / maxTrend) : 0.0;
        double finalScore = 0.7 * matchScore + 0.3 * trendNorm;//70% prefix match 30% trending(can be modified)

        pq.push({finalScore, id});
    }

    vector<int> res;
    unordered_set<int> seen;
    for (int i = 0; i < 7 && !pq.empty(); )//top 7 recommendations
    {
        int id = pq.top().second;
        pq.pop();
        if (!seen.count(id))
        {
            res.push_back(id);
            seen.insert(id);
            i++;
        }
    }

    return res;
}