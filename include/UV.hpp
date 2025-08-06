#pragma once
#include <array>

struct UV {
    int u, v;

    constexpr UV(int u = 0, int v = 0) : u(u), v(v) {}
};

constexpr std::array<UV, 6> makeSameAll(int u, int v) {
    return { UV(u, v), UV(u, v), UV(u, v), UV(u, v), UV(u, v), UV(u, v) };
}