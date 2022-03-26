#include <cmath>
#include <queue>
#include <string>
#include "common.h"

struct Room;

//https://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/

const int dir=4; // number of possible directions to go at any position
static int dx[dir]={1, 0, -1, 0};
static int dy[dir]={0, 1, 0, -1};
// for dir == 8, diag, also set:
// static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
// static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

struct Node 
{
    Node(int xp, int yp, int d, int p);

    void updatePriority(const int & xDest, const int & yDest);

    void nextLevel(const int & i);

    // Estimation function for the remaining distance to the goal.
    const int & estimate(const int & xDest, const int & yDest) const;

    int xPos;
    int yPos;
    int priority;  // smaller: higher priority
    int level;  // total distance already travelled to reach the node
};

bool operator<(const Node & a, const Node & b);

// A-star algorithm.
// The route returned is a string of direction digits.
std::string pathFind(Room* room, const int & xStart, const int & yStart, 
                 const int & xFinish, const int & yFinish );

Dir nextStep(Room* room, const int & xStart, const int & yStart, 
                 const int & xFinish, const int & yFinish );