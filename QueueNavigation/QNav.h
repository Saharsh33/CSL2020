#ifndef QNAV_H
#define QNAV_H

#include <bits/stdc++.h>
using namespace std;

#include "../Globals/Globals.h"
#include "../Queue_Management/QManage.h"
#include "../PlaySong/PlaySong.h"

// go backward in queue
void queuePrev();

// go forward in queue (autoplay recommendation if at end)
void queueNext();

#endif