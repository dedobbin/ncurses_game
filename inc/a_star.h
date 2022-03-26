#include <cmath>
#include <queue>
#include <string>
#include "room.h"

const int dir=4; // number of possible directions to go at any position
// if dir==4
static int dx[dir]={1, 0, -1, 0};
static int dy[dir]={0, 1, 0, -1};
// if dir==8
// static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
// static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

struct Node 
{
    Node(int xp, int yp, int d, int p) 
    : xPos (xp), yPos(yp), level(d), priority(p) 
    {

    }

    void updatePriority(const int & xDest, const int & yDest)
    {
        //priority=level+remaining distance estimate
        priority=level+estimate(xDest, yDest)*10; //A*
    }

    void nextLevel(const int & i) // i: direction
    {
        level+=(dir==8?(i%2==0?10:14):10);
    }

    // Estimation function for the remaining distance to the goal.
    const int & estimate(const int & xDest, const int & yDest) const
    {
        static int xd, yd, d;
        xd=xDest-xPos;
        yd=yDest-yPos;         

        // Euclidian Distance
        d=static_cast<int>(sqrt(xd*xd+yd*yd));

        // Manhattan distance
        //d=abs(xd)+abs(yd);
        
        // Chebyshev distance
        //d=max(abs(xd), abs(yd));

        return(d);
    }

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