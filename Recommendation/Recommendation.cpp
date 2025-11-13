#include "Recommendation.h"

double cosineSim(const vector<double> &a, const vector<double> &b)
{
    double dot = 0, na = 0, nb = 0;
    size_t n = max(a.size(), b.size());
    for (size_t i = 0; i < n; ++i)
    {
        double av = (i < a.size() ? a[i] : 0), bv = (i < b.size() ? b[i] : 0);
        dot += av * bv;
        na += av * av;
        nb += bv * bv;
    }
    if (na == 0 || nb == 0)
        return 0;
    return dot / sqrt(na * nb);
}

vector<double> getGenreVec(const string &genre)
{
    vector<double> v(GENRE_DIM, 0);
    if (genreIndex.count(genre))
        v[genreIndex[genre]] = 1.0;
    return v;
}

vector<double> getArtistVec(const string &artist)
{
    vector<double> v(ARTIST_DIM, 0);
    auto tokens = splitArtistTokens(artist);
    for (auto &t : tokens)
        if (artistIndex.count(t))
            v[artistIndex[t]] = 1;
    double n = 0;
    for (double x : v)
        n += x * x;
    n = sqrt(n);
    if (n > 1e-9)
        for (double &x : v)
            x /= n;
    return v;
}

void buildFeatureVectors()
{
    genreIndex.clear();
    artistIndex.clear();
    GENRE_DIM = ARTIST_DIM = 0;
    for (auto &s : songs)
        if (!s.genre.empty() && !genreIndex.count(s.genre))
            genreIndex[s.genre] = GENRE_DIM++;
    for (auto &s : songs)
        for (auto &t : splitArtistTokens(s.artist))
            if (!artistIndex.count(t))
                artistIndex[t] = ARTIST_DIM++;
}

// OPTIMIZED: Build graph in chunks with progress indicator
void buildGraph()
{
    graph.clear();
    cout << "Building recommendation graph...\n";

    int n = songs.size();
    long long totalPairs = (long long)n * (n - 1) / 2;
    long long processed = 0;
    int lastPercent = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double sim = 0.5 * ((songs[i].genre == songs[j].genre) ? 1 : 0.3) +
                         0.5 * (artistTokensIntersect(songs[i].artist, songs[j].artist) ? 1 : 0.5);

            if (sim > 0.2)
            {
                graph[i].push_back({j, sim});
                graph[j].push_back({i, sim});
            }

            processed++;

            // optional progress printing (commented by default)
            // if (totalPairs > 0) {
            //     int percent = int((processed * 100) / totalPairs);
            //     if (percent != lastPercent && percent % 1 == 0) {
            //         cout << "\rProgress: " << percent << "% (" << processed << "/" << totalPairs << " pairs)" << flush;
            //         lastPercent = percent;
            //     }
            // }
        }
    }

    cout << "Graph built successfully with " << graph.size() << " nodes.\n";
    cout << "Saving cache...\n";

    if (saveGraphCache())
        cout << "Graph cache saved to " << graphCacheFile << "\n";
    else
        cout << "Warning: Could not save graph cache.\n";
}