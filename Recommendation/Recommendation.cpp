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

// compute the same per-pair score used earlier (S for pair cur->i)
double computePairRecommendationScore(int cur, int i,
                                      double Pmax, double Tmax, double Wmax)
{
    if (cur < 0 || cur >= (int)songs.size() || i < 0 || i >= (int)songs.size())
        return 0.0;
    double alpha = 0.20;   // graph similarity weight
    double beta  = 0.10;   // popularity weight
    double gamma = 0.15;   // genre similarity weight
    double delta = 0.35;   // artist similarity weight
    double eta   = 0.10;   // diversity weight
    double zeta  = 0.10;   // trending weight
    double Ci = 0.0;
    if (graph.count(cur))
    {
        for (auto &e : graph[cur])
            if (e.first == i)
            {
                if (Wmax > 0)
                    Ci = e.second / Wmax;
                else
                    Ci = e.second;
                break;
            }
    }
    double Pn = 0.0;
    if (Pmax > 0)
        Pn = log(1 + songs[i].play_count) / log(1 + Pmax);
    double Gi = cosineSim(getGenreVec(songs[i].genre), getGenreVec(songs[cur].genre));
    double Ai = cosineSim(getArtistVec(songs[i].artist), getArtistVec(songs[cur].artist));
    double Ti = (Tmax > 0 ? songs[i].trending_score / Tmax : 0.0);
    double Di = 1.0 - (0.5 * Gi + 0.5 * Ai);
    double S = alpha * Ci + beta * Pn + gamma * Gi + delta * Ai + eta * Di + zeta * Ti;
    return S;
}