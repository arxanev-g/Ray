#pragma once

#include "vector.h"

class Intersection {
public:
    Intersection() {
    }
    Intersection(const Vector& pos, const Vector& norm, double distance)
        : position_(pos), normal_(Normalize(norm)), distance_(distance) {
    }

    const Vector& GetPosition() const {
        return position_;
    }

    const Vector& GetNormal() const {
        return normal_;
    }

    double GetDistance() const {
        return distance_;
    }

    void SetNormal(Vector normal) {
        normal_ = normal;
    }

private:
    Vector position_;
    Vector normal_;
    double distance_;
};