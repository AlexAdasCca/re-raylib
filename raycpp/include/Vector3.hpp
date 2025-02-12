#ifndef RAYLIB_CPP_INCLUDE_VECTOR3_HPP_
#define RAYLIB_CPP_INCLUDE_VECTOR3_HPP_

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#endif

#include <string>

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"
#include "./raymath.hpp"

namespace raylib {
/**
 * Vector3 type
 */
class Vector3 : public ::Vector3 {
public:
    Vector3(const ::Vector3& vec) : ::Vector3{vec.x, vec.y, vec.z} {}

    Vector3(float x, float y, float z) : ::Vector3{x, y, z} {}
    Vector3(float x, float y) : ::Vector3{x, y, 0} {}
    Vector3(float x) : ::Vector3{x, 0, 0} {}
    Vector3() {}

    Vector3(::Color color) { set(RLColorToHSV(color)); }

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Z, z)

    Vector3& operator=(const ::Vector3& vector3) {
        set(vector3);
        return *this;
    }

    bool operator==(const ::Vector3& other) const { return x == other.x && y == other.y && z == other.z; }

    bool operator!=(const ::Vector3& other) const { return !(*this == other); }

    std::string ToString() const { return RLTextFormat("Vector3(%f, %f, %f)", x, y, z); }

    operator std::string() const { return ToString(); }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * Add two vectors
     */
    Vector3 Add(const ::Vector3& vector3) const { return RLVector3Add(*this, vector3); }

    /**
     * Add two vectors
     */
    Vector3 operator+(const ::Vector3& vector3) const { return RLVector3Add(*this, vector3); }

    Vector3& operator+=(const ::Vector3& vector3) {
        set(RLVector3Add(*this, vector3));

        return *this;
    }

    /**
     * Subtract two vectors.
     */
    Vector3 Subtract(const ::Vector3& vector3) const { return RLVector3Subtract(*this, vector3); }

    /**
     * Subtract two vectors.
     */
    Vector3 operator-(const ::Vector3& vector3) const { return RLVector3Subtract(*this, vector3); }

    Vector3& operator-=(const ::Vector3& vector3) {
        set(RLVector3Subtract(*this, vector3));

        return *this;
    }

    /**
     * Negate provided vector (invert direction)
     */
    Vector3 Negate() const { return RLVector3Negate(*this); }

    /**
     * Negate provided vector (invert direction)
     */
    Vector3 operator-() const { return RLVector3Negate(*this); }

    /**
     * Multiply vector by vector
     */
    Vector3 Multiply(const ::Vector3& vector3) const { return RLVector3Multiply(*this, vector3); }

    /**
     * Multiply vector by vector
     */
    Vector3 operator*(const ::Vector3& vector3) const { return RLVector3Multiply(*this, vector3); }

    /**
     * Multiply vector by vector
     */
    Vector3& operator*=(const ::Vector3& vector3) {
        set(RLVector3Multiply(*this, vector3));

        return *this;
    }

    /**
     * Multiply vector by scalar
     */
    Vector3 Scale(const float scaler) const { return RLVector3Scale(*this, scaler); }

    /**
     * Multiply vector by scalar
     */
    Vector3 operator*(const float scaler) const { return RLVector3Scale(*this, scaler); }

    /**
     * Multiply vector by scalar
     */
    Vector3& operator*=(const float scaler) {
        set(RLVector3Scale(*this, scaler));

        return *this;
    }

    /**
     * Divide vector by vector
     */
    Vector3 Divide(const ::Vector3& vector3) const { return RLVector3Divide(*this, vector3); }

    /**
     * Divide vector by vector
     */
    Vector3 operator/(const ::Vector3& vector3) const { return RLVector3Divide(*this, vector3); }

    /**
     * Divide vector by vector
     */
    Vector3& operator/=(const ::Vector3& vector3) {
        x /= vector3.x;
        y /= vector3.y;
        z /= vector3.z;

        return *this;
    }

    /**
     * Divide a vector by a value.
     */
    Vector3 Divide(const float div) const { return ::Vector3{x / div, y / div, z / div}; }

    /**
     * Divide a vector by a value.
     */
    Vector3 operator/(const float div) const { return Divide(div); }

    /**
     * Divide a vector by a value.
     */
    Vector3& operator/=(const float div) {
        x /= div;
        y /= div;
        z /= div;

        return *this;
    }

    /**
     * Calculate vector length
     */
    float Length() const { return RLVector3Length(*this); }

    /**
     * Calculate vector square length
     */
    float LengthSqr() const { return RLVector3LengthSqr(*this); }

    Vector3 Normalize() const { return RLVector3Normalize(*this); }

    float DotProduct(const ::Vector3& vector3) const { return RLVector3DotProduct(*this, vector3); }

    float Distance(const ::Vector3& vector3) const { return RLVector3Distance(*this, vector3); }

    Vector3 Lerp(const ::Vector3& vector3, const float amount) const { return RLVector3Lerp(*this, vector3, amount); }

    Vector3 CrossProduct(const ::Vector3& vector3) const { return RLVector3CrossProduct(*this, vector3); }

    Vector3 Perpendicular() const { return RLVector3Perpendicular(*this); }

    Vector3 Project(const ::Vector3& vector3) const { return RLVector3Project(*this, vector3); }

    Vector3 Reject(const ::Vector3& vector3) const { return RLVector3Reject(*this, vector3); }

    void OrthoNormalize(::Vector3* vector3) { RLVector3OrthoNormalize(this, vector3); }

    Vector3 Transform(const ::Matrix& matrix) const { return RLVector3Transform(*this, matrix); }

    Vector3 RotateByQuaternion(const ::Quaternion& quaternion) const {
        return RLVector3RotateByQuaternion(*this, quaternion);
    }

    Vector3 Reflect(const ::Vector3& normal) const { return RLVector3Reflect(*this, normal); }

    Vector3 Min(const ::Vector3& vector3) const { return RLVector3Min(*this, vector3); }

    Vector3 Max(const ::Vector3& vector3) const { return RLVector3Max(*this, vector3); }

    Vector3 Barycenter(const ::Vector3& a, const ::Vector3& b, const ::Vector3& c) const {
        return RLVector3Barycenter(*this, a, b, c);
    }

    static Vector3 Zero() { return RLVector3Zero(); }

    static Vector3 One() { return RLVector3One(); }
#endif

    void DrawLine3D(const ::Vector3& endPos, ::Color color) const { ::RLDrawLine3D(*this, endPos, color); }

    void DrawPoint3D(::Color color) const { ::RLDrawPoint3D(*this, color); }

    void DrawCircle3D(float radius, const ::Vector3& rotationAxis, float rotationAngle, Color color) const {
        ::RLDrawCircle3D(*this, radius, rotationAxis, rotationAngle, color);
    }

    void DrawCube(float width, float height, float length, ::Color color) const {
        ::RLDrawCube(*this, width, height, length, color);
    }

    void DrawCube(const ::Vector3& size, ::Color color) const { ::RLDrawCubeV(*this, size, color); }

    void DrawCubeWires(float width, float height, float length, ::Color color) const {
        ::RLDrawCubeWires(*this, width, height, length, color);
    }

    void DrawCubeWires(const ::Vector3& size, ::Color color) const { ::RLDrawCubeWiresV(*this, size, color); }

    void DrawSphere(float radius, ::Color color) const { ::RLDrawSphere(*this, radius, color); }

    void DrawSphere(float radius, int rings, int slices, ::Color color) const {
        ::RLDrawSphereEx(*this, radius, rings, slices, color);
    }

    void DrawSphereWires(float radius, int rings, int slices, ::Color color) const {
        ::RLDrawSphereWires(*this, radius, rings, slices, color);
    }

    void DrawCylinder(float radiusTop, float radiusBottom, float height, int slices, ::Color color) const {
        ::RLDrawCylinder(*this, radiusTop, radiusBottom, height, slices, color);
    }

    void DrawCylinderWires(float radiusTop, float radiusBottom, float height, int slices, ::Color color) const {
        ::RLDrawCylinderWires(*this, radiusTop, radiusBottom, height, slices, color);
    }

    void DrawPlane(const ::Vector2& size, ::Color color) const { ::RLDrawPlane(*this, size, color); }

    /**
     * Detect collision between two spheres
     */
    bool CheckCollision(float radius1, const ::Vector3& center2, float radius2) const {
        return RLCheckCollisionSpheres(*this, radius1, center2, radius2);
    }
protected:
    void set(const ::Vector3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }
};
} // namespace raylib

using RVector3 = raylib::Vector3;

#endif // RAYLIB_CPP_INCLUDE_VECTOR3_HPP_
