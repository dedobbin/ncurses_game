#pragma once
#include <vector>
#include <functional>
#include <algorithm>

enum Dir { NONE = 999, DOWN = 1, RIGHT = 0, LEFT = 2, UP = 3};

template <typename T, typename U>
std::vector<T> filter (std::vector<T> vec, U f) 
{
    std::vector<T> result;
    for (auto &e: vec) {
        if (f(e)) result.push_back(e);
    }
    return result;
}

std::vector<std::pair<int, int>> get_points_between(int x1, int y1, int x2, int y2);