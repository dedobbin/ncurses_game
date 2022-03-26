//https://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/

#include "a_star.h"
#include "room.h"
#include <iostream>


Node::Node(int xp, int yp, int d, int p) 
: xPos (xp), yPos(yp), level(d), priority(p) 
{}

void Node::updatePriority(const int & xDest, const int & yDest)
{
    //priority=level+remaining distance estimate
    priority=level+estimate(xDest, yDest)*10; //A*
}

void Node::nextLevel(const int & i) // i: direction
{
    level+=(dir==8?(i%2==0?10:14):10);
}

const int & Node::estimate(const int & xDest, const int & yDest) const
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

Dir nextStep(Room* room, const int & xStart, const int & yStart, 
                 const int & xFinish, const int & yFinish)
{
    auto path = pathFind(room, xStart, yStart, xFinish, yFinish);
    if (path.empty())
        return Dir::NONE;

    return static_cast<Dir>(path[0] - '0');
}

bool operator<(const Node & a, const Node & b)
{
  return a.priority < b.priority > b.priority;;
}

//todo: just return vector instead of string
std::string pathFind(Room* room, const int & xStart, const int & yStart, 
                 const int & xFinish, const int & yFinish )
{
    static std::priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static std::unique_ptr<Node> n0;
    static std::unique_ptr<Node> m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;


    int m = room->h;
    int n = room->w;

    int dir_map[n][m]; // map of directions
    int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
    int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes


    // reset the node maps TODO: dont think this is needed..
    for(y=0;y<m;y++)
    {
        for(x=0;x<n;x++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }

    // create the start node and push into list of open nodes
    n0=std::make_unique<Node>(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[x][y]=n0->priority; // mark it on the open nodes map

    // A* search
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0=std::make_unique<Node>( pq[pqi].top().xPos, pq[pqi].top().yPos, 
                     pq[pqi].top().level, pq[pqi].top().priority);

        x=n0->xPos; y=n0->yPos;

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x==xFinish && y==yFinish) 
        {
            // generate the path from finish to start
            // by following the directions
            std::string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            // empty the leftover nodes
            while(!pq[pqi].empty()) pq[pqi].pop();           
            return path;
        }

        // generate moves (child nodes) in all possible directions
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || room->hasWall(xdx, ydy) 
                || closed_nodes_map[xdx][ydy]==1))
            {
                // generate a child node
                m0=std::make_unique<Node>( xdx, ydy, n0->level, 
                             n0->priority);
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->priority;
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx][ydy]>m0->priority)
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy]=m0->priority;
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().xPos==xdx && 
                           pq[pqi].top().yPos==ydy))
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pq[pqi].pop(); // remove the wanted node
                    
                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // add the better node instead
                }
                
            }
        }
    }
    return ""; // no route found
}