#ifndef QMANAGE_H
#define QMANAGE_H

#include <bits/stdc++.h>
using namespace std;

#include "../Globals/Globals.h"
#include "../Recommendation/Recommendation.h"

// Enqueue
bool enqueueSong(int id);

// Check if song id is in queue
bool isInQueue(int id);

// Recommendation functions
vector<int> getQueueBasedRecommendations();
int getTopRecommendedSong();
void computeAndShowRecommendationsFromQueue();

#endif