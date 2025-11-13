#include "GraphCache.h"

bool saveGraphCache()
{
    ofstream file(graphCacheFile);
    if (!file)
        return false;

    // Count total edges
    size_t totalEdges = 0;
    for (auto &kv : graph)
        totalEdges += kv.second.size();

    file << totalEdges << "\n";

    // Save edges: nodeA nodeB weight
    for (auto &kv : graph)
    {
        int nodeId = kv.first;
        for (auto &edge : kv.second)
        {
            if (nodeId < edge.first)  // save only once
                file << nodeId << " " << edge.first << " "
                     << fixed << setprecision(6) << edge.second << "\n";
        }
    }

    return true;
}
// Load graph cache from file
bool loadGraphCache()
{
    ifstream file(graphCacheFile);
    if (!file)
        return false;

    graph.clear();

    size_t totalEdges;
    if (!(file >> totalEdges))
        return false;

    // Reserve adjacency list capacity
    graph.reserve(songs.size());

    int nodeA, nodeB;
    double weight;
    size_t loaded = 0;

    while (file >> nodeA >> nodeB >> weight)
    {
        if (nodeA >= 0 && nodeA < (int)songs.size() &&
            nodeB >= 0 && nodeB < (int)songs.size())
        {
            graph[nodeA].push_back({nodeB, weight});
            graph[nodeB].push_back({nodeA, weight});
            loaded++;
        }
    }

    cout << "Loaded " << loaded << " edges from cache.\n";
    return true;
}