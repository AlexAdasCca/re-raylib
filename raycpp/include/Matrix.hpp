#ifndef RAYLIB_CPP_INCLUDE_MATRIX_HPP_
#define RAYLIB_CPP_INCLUDE_MATRIX_HPP_

#include "./raylib-cpp-utils.hpp"
#include "./raylib.hpp"
#include "./raymath.hpp"

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#endif

namespace raylib {
/**
 * Matrix type (OpenGL style 4x4 - right handed, column major)
 */
class Matrix : public ::Matrix {
public:
    Matrix(const ::Matrix& mat)
        : ::Matrix{
              mat.m0,
              mat.m4,
              mat.m8,
              mat.m12,
              mat.m1,
              mat.m5,
              mat.m9,
              mat.m13,
              mat.m2,
              mat.m6,
              mat.m10,
              mat.m14,
              mat.m3,
              mat.m7,
              mat.m11,
              mat.m15} {
        // Nothing.
    }

    Matrix(
        float m0 = 0,
        float m4 = 0,
        float m8 = 0,
        float m12 = 0,
        float m1 = 0,
        float m5 = 0,
        float m9 = 0,
        float m13 = 0,
        float m2 = 0,
        float m6 = 0,
        float m10 = 0,
        float m14 = 0,
        float m3 = 0,
        float m7 = 0,
        float m11 = 0,
        float m15 = 0)
        : ::Matrix{m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15} {
        // Nothing.
    }

    GETTERSETTER(float, M0, m0)
    GETTERSETTER(float, M1, m1)
    GETTERSETTER(float, M2, m2)
    GETTERSETTER(float, M3, m3)
    GETTERSETTER(float, M4, m4)
    GETTERSETTER(float, M5, m5)
    GETTERSETTER(float, M6, m6)
    GETTERSETTER(float, M7, m7)
    GETTERSETTER(float, M8, m8)
    GETTERSETTER(float, M9, m9)
    GETTERSETTER(float, M10, m10)
    GETTERSETTER(float, M11, m11)
    GETTERSETTER(float, M12, m12)
    GETTERSETTER(float, M13, m13)
    GETTERSETTER(float, M14, m14)
    GETTERSETTER(float, M15, m15)

    Matrix& operator=(const ::Matrix& matrix) {
        set(matrix);
        return *this;
    }

    Matrix& operator=(const Matrix& matrix) {
        set(matrix);
        return *this;
    }

    bool operator==(const ::Matrix& other) {
        return m0 == other.m0 && m1 == other.m1 && m2 == other.m2 && m3 == other.m3 && m4 == other.m4 &&
               m5 == other.m5 && m6 == other.m6 && m7 == other.m7 && m8 == other.m8 && m9 == other.m9 &&
               m10 == other.m10 && m11 == other.m11 && m12 == other.m12 && m13 == other.m13 && m14 == other.m14 &&
               m15 == other.m15;
    }

    bool operator!=(const ::Matrix& other) { return !(*this == other); }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * Returns the trace of the matrix (sum of the values along the diagonal)
     */
    float Trace() const { return ::RLMatrixTrace(*this); }

    /**
     * Transposes provided matrix
     */
    Matrix Transpose() const { return ::RLMatrixTranspose(*this); }

    Matrix Invert() const { return ::RLMatrixInvert(*this); }

    static Matrix Identity() { return ::RLMatrixIdentity(); }

    Matrix Add(const ::Matrix& right) { return ::RLMatrixAdd(*this, right); }

    Matrix operator+(const ::Matrix& matrix) { return ::RLMatrixAdd(*this, matrix); }

    Matrix Subtract(const ::Matrix& right) { return ::RLMatrixSubtract(*this, right); }

    Matrix operator-(const ::Matrix& matrix) { return ::RLMatrixSubtract(*this, matrix); }

    static Matrix Translate(float x, float y, float z) { return ::RLMatrixTranslate(x, y, z); }

    static Matrix Rotate(Vector3 axis, float angle) { return ::RLMatrixRotate(axis, angle); }

    static Matrix RotateXYZ(Vector3 angle) { return ::RLMatrixRotateXYZ(angle); }

    static Matrix RotateX(float angle) { return ::RLMatrixRotateX(angle); }

    static Matrix RotateY(float angle) { return ::RLMatrixRotateY(angle); }

    static Matrix RotateZ(float angle) { return ::RLMatrixRotateZ(angle); }

    static Matrix Scale(float x, float y, float z) { return ::RLMatrixScale(x, y, z); }

    Matrix Multiply(const ::Matrix& right) const { return ::RLMatrixMultiply(*this, right); }

    Matrix operator*(const ::Matrix& matrix) { return ::RLMatrixMultiply(*this, matrix); }

    static Matrix Frustum(double left, double right, double bottom, double top, double near, double far) {
        return ::RLMatrixFrustum(left, right, bottom, top, near, far);
    }

    static Matrix Perspective(double fovy, double aspect, double near, double far) {
        return ::RLMatrixPerspective(fovy, aspect, near, far);
    }

    static Matrix Ortho(double left, double right, double bottom, double top, double near, double far) {
        return ::RLMatrixOrtho(left, right, bottom, top, near, far);
    }

    static Matrix LookAt(Vector3 eye, Vector3 target, Vector3 up) { return ::RLMatrixLookAt(eye, target, up); }

    float16 ToFloatV() const { return ::RLMatrixToFloatV(*this); }

    operator float16() { return ToFloatV(); }

    /**
     * Set shader uniform value (matrix 4x4)
     */
    Matrix& SetShaderValue(const ::Shader& shader, int uniformLoc) {
        ::RLSetShaderValueMatrix(shader, uniformLoc, *this);
        return *this;
    }

    static Matrix GetCamera(const ::Camera& camera) { return ::RLGetCameraMatrix(camera); }

    static Matrix GetCamera(const ::Camera2D& camera) { return ::RLGetCameraMatrix2D(camera); }

#endif
protected:
    void set(const ::Matrix& mat) {
        m0 = mat.m0;
        m1 = mat.m1;
        m2 = mat.m2;
        m3 = mat.m3;
        m4 = mat.m4;
        m5 = mat.m5;
        m6 = mat.m6;
        m7 = mat.m7;
        m8 = mat.m8;
        m9 = mat.m9;
        m10 = mat.m10;
        m11 = mat.m11;
        m12 = mat.m12;
        m13 = mat.m13;
        m14 = mat.m14;
        m15 = mat.m15;
    }
};
} // namespace raylib

using RMatrix = raylib::Matrix;

#endif // RAYLIB_CPP_INCLUDE_MATRIX_HPP_
