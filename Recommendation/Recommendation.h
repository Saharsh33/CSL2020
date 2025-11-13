#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <bits/stdc++.h>
using namespace std;

#include "../Globals/Globals.h"
#include "../Artist_tokenization/Artist_tokenization.h"
#include "../GraphCache/GraphCache.h"
#include "../String_helpers/String_helpers.h"

// function declarations
double cosineSim(const vector<double> &a, const vector<double> &b);

vector<double> getGenreVec(const string &genre);
vector<double> getArtistVec(const string &artist);

void buildFeatureVectors();
void buildGraph();


#endif // RECOMMENDATION_H