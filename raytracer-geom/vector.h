#pragma once

#include <array>
#include <cmath>
#include <cstddef>

class Vector;

inline double Length(const Vector& vec);

class Vector {
public:
    Vector() = default;

    Vector(const std::initializer_list<double>& list) {
        size_t i = 0;
        for (auto x : list) {
            data_[i++] = x;
        }
    }

    Vector(const std::array<double, 3>& data) : data_(data) {
    }

    Vector(double a, double b, double c) : Vector({a, b, c}) {
    }

    double& operator[](size_t ind) {
        return data_[ind];
    }

    double operator[](size_t ind) const {
        return data_[ind];
    }

    void Normalize() {
        double length = Length(*this);
        for (auto& x : data_) {
            x /= length;
        }
    }

    bool NotZero() const {
        return Length(*this) != 0;
    }

    bool IsZero() const {
        return not NotZero();
    }

    friend Vector operator+(const Vector& lhs, const Vector& rhs) {
        return {lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]};
    }

    friend Vector operator-(const Vector& lhs, const Vector& rhs) {
        return {lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]};
    }

    friend Vector operator*(double k, const Vector& rhs) {
        return {k * rhs[0], k * rhs[1], k * rhs[2]};
    }

    friend Vector operator*(const Vector& lhs, const Vector& rhs) {
        return {lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]};
    }
    friend Vector operator/(const Vector& a, const Vector& b) {
        return {a[0] / b[0], a[1] / b[1], a[2] / b[2]};
    }

    Vector& operator/=(double t) {
        for (int i = 0; i < 3; ++i) {
            data_[i] /= t;
        }
        return *this;
    }

    Vector& operator+=(double t) {
        for (int i = 0; i < 3; ++i) {
            data_[i] += t;
        }
        return *this;
    }

    Vector& operator*=(double t) {
        for (int i = 0; i < 3; ++i) {
            data_[i] *= t;
        }
        return *this;
    }

    Vector& operator*=(const Vector& other) {
        for (int i = 0; i < 3; ++i) {
            data_[i] *= other[i];
        }
        return *this;
    }

    Vector& operator/=(const Vector& other) {
        for (int i = 0; i < 3; ++i) {
            data_[i] /= other[i];
        }
        return *this;
    }

    Vector& operator+=(const Vector& other) {
        for (int i = 0; i < 3; ++i) {
            data_[i] += other[i];
        }
        return *this;
    }

    bool operator==(const Vector& other) const {
        return data_ == other.data_;
    }

    auto operator<=>(const Vector& other) const {
        return data_ <=> other.data_;
    }

private:
    std::array<double, 3> data_;
};

Vector Normalize(Vector from) {
    from.Normalize();
    return from;
}

inline double DotProduct(const Vector& lhs, const Vector& rhs) {
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

inline Vector CrossProduct(const Vector& lhs, const Vector& rhs) {
    return {lhs[1] * rhs[2] - lhs[2] * rhs[1], lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]};
}

inline double Length(const Vector& vec) {
    return sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

Vector operator/(const Vector& a, double t) {
    Vector out;
    for (int i = 0; i < 3; ++i) {
        out[i] = a[i] / t;
    }
    return out;
}

Vector operator*(const Vector& a, double t) {
    Vector h;
    for (int i = 0; i < 3; ++i) {
        h[i] = a[i] * t;
    }
    return h;
}
