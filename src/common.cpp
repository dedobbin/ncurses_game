#include "common.h"

std::vector<std::pair<int, int>> get_points_between(int x1, int y1, int x2, int y2)
{
    // thanks brad
    // https://stackoverflow.com/questions/25837544/get-all-points-of-a-straight-line-in-python
    // bresenhamsLineGeneration
    std::vector<std::pair<int, int>> points;
    bool issteep = (abs(y2 - y1) > abs(x2 - x1));
    if (issteep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }
    bool rev = false;
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
        rev = true;
    }
    int deltax = x2 - x1;
    int deltay = abs(y2 - y1);
    int error  = int(deltax / 2);
    int y      = y1;
    int ystep;
    if (y1 < y2) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (int x = x1; x < x2 + 1; ++x) {
        if (issteep) {
            std::pair<int, int> pt = std::make_pair(y, x);
            points.emplace_back(pt);
        } else {
            std::pair<int, int> pt = std::make_pair(x, y);
            points.emplace_back(pt);
        }

        error -= deltay;
        if (error < 0) {
            y += ystep;
            error += deltax;
        }
    }
    // Reverse the list if the coordinates were reversed
    if (rev) {
        std::reverse(points.begin(), points.end());
    }
    
    return points;
}
