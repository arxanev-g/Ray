#pragma once

#include "triangle.h"
#include "material.h"
#include "sphere.h"
#include "vector.h"

struct Object {
    const Material* material = nullptr;
    Triangle polygon;
    // Triangle normal;

    const Vector* GetNormal(size_t index) const {
        return &normals[index];
    }
    std::array<Vector, 3> normals{{Vector{0, 0, 0}, Vector{0, 0, 0}, Vector{0, 0, 0}}};

    Object(const Material* material, Triangle polygon, std::array<Vector, 3> normals)
        : material(material), polygon(polygon), normals(normals) {
    }
};

struct SphereObject {
    Material* material = nullptr;
    Sphere sphere;
};