#pragma once

#include "vector.h"
#include "sphere.h"
#include "intersection.h"
#include "triangle.h"
#include "ray.h"

#include <optional>

std::optional<Intersection> GetIntersection(const Ray& ray, const Sphere& sphere) {
    Vector l = sphere.GetCenter() - ray.GetOrigin();
    double cross_prod = Length(CrossProduct(l, ray.GetDirection())) / Length(ray.GetDirection());
    if (cross_prod > sphere.GetRadius() ||
        (DotProduct(l, ray.GetDirection()) < 0 && Length(l) > sphere.GetRadius())) {
        return std::nullopt;
    }
    double length = sqrt(Length(l) * Length(l) - cross_prod * cross_prod) -
                    sqrt(sphere.GetRadius() * sphere.GetRadius() - cross_prod * cross_prod);
    if (Length(l) < sphere.GetRadius()) {
        if (DotProduct(l, ray.GetDirection()) > 0) {
            length = sqrt(Length(l) * Length(l) - cross_prod * cross_prod) +
                     sqrt(sphere.GetRadius() * sphere.GetRadius() - cross_prod * cross_prod);
        } else {
            length = -sqrt(Length(l) * Length(l) - cross_prod * cross_prod) +
                     sqrt(sphere.GetRadius() * sphere.GetRadius() - cross_prod * cross_prod);
        }
    }
    Vector answer_point = length / Length(ray.GetDirection()) * ray.GetDirection();
    Vector result_point = ray.GetOrigin() + answer_point;
    Vector normal = result_point - sphere.GetCenter();
    normal.Normalize();
    normal = (Length(l) > sphere.GetRadius() ? normal : -1 * normal);
    return Intersection(result_point, normal, Length(answer_point));
}

std::optional<Intersection> GetIntersection(const Ray& ray, const Triangle& triangle) {
    double u, v;
    Vector h, s;
    Vector ab = triangle[1] - triangle[0];
    Vector ac = triangle[2] - triangle[0];
    h = CrossProduct(ray.GetDirection(), ac);

    s = ray.GetOrigin() - triangle[0];
    u = DotProduct(s, h) / DotProduct(ab, h);

    v = DotProduct(ray.GetDirection(), CrossProduct(s, ab)) / DotProduct(ab, h);

    double t = DotProduct(ac, CrossProduct(s, ab)) / DotProduct(ab, h);
    if (t < 0 or u < 0.0 or v < 0.0 or u + v > 1.0) {
        return std::nullopt;
    }
    auto pos = ray.GetOrigin() + t * ray.GetDirection();
    auto normal = CrossProduct(ab, ac);
    normal.Normalize();
    normal = (DotProduct(ray.GetDirection(), normal) < 0 ? normal : -1 * normal);
    auto dist = Length(pos - ray.GetOrigin());
    return Intersection(pos, normal, dist);
}

std::optional<Vector> Refract(const Vector& ray, const Vector& normal, double eta) {
    auto cos1 = (DotProduct(ray, normal) > 0 ? DotProduct(ray, normal) : -DotProduct(ray, normal));
    auto sin2 = eta * sqrt(1 - cos1 * cos1);
    if (std::abs(sin2) > 1) {
        return std::nullopt;
    }
    auto cos2 = sqrt(1 - sin2 * sin2);
    auto output = eta * ray + (eta * cos1 - cos2) * normal;
    output.Normalize();
    return output;
}

Vector Reflect(const Vector& ray, const Vector& normal) {
    auto cos1 = (DotProduct(ray, normal) > 0 ? DotProduct(ray, normal) : -DotProduct(ray, normal));
    auto output = ray + 2 * cos1 * normal;
    output.Normalize();
    return output;
}

Vector GetBarycentricCoords(const Triangle& triangle, const Vector& point) {
    double u, v, w;
    Vector ab = triangle[1] - triangle[0];
    Vector ac = triangle[2] - triangle[0];
    Vector ap = point - triangle[0];
    Vector cp = point - triangle[2];
    Vector bp = point - triangle[1];
    auto full_area = Length(CrossProduct(ab, ac));
    u = Length(CrossProduct(cp, bp)) / full_area;
    v = Length(CrossProduct(ap, cp)) / full_area;
    w = Length(CrossProduct(ap, bp)) / full_area;
    return Vector({u, v, w});
}