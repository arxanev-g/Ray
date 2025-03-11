#pragma once

#include "vector.h"

#include <cstddef>

class Triangle {
public:
    Triangle(const Vector& a, const Vector& b, const Vector& c) : vertices_({a, b, c}) {
    }

    Triangle(const std::initializer_list<Vector>& list) {
        size_t i = 0;
        for (const auto& x : list) {
            vertices_[i++] = x;
        }
    }

    double Area() const {
        return Length(CrossProduct(vertices_[0] - vertices_[1], vertices_[0] - vertices_[2])) / 2;
    }

    Vector& operator[](size_t ind) {
        return vertices_[ind];
    }

    const Vector& operator[](size_t ind) const {
        return vertices_[ind];
    }

private:
    std::array<Vector, 3> vertices_;
};
