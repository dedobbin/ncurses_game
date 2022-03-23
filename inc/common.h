#pragma once
#include <vector>
#include <functional>

template <typename T, typename U>
std::vector<T> filter (std::vector<T> vec, U f) {
    std::vector<T> result;
    for (auto &e: vec) {
        if (f(e)) result.push_back(e);
    }
    return result;
}