#include <stdio.h>
#include <math.h>

typedef int mat4[4][4];
typedef int vec3[3];


void m4mmul(mat4 *out, mat4 a, mat4 b)
{
    *out[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] + a[0][3] * b[3][0];
    *out[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] + a[0][3] * b[3][1];
    *out[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] + a[0][3] * b[3][2];
    *out[0][3] = a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] + a[0][3] * b[3][3];

    *out[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] + a[1][3] * b[3][0];
    *out[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] + a[1][3] * b[3][1];
    *out[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] + a[1][3] * b[3][2];
    *out[1][3] = a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] + a[1][3] * b[3][3];

    *out[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] + a[2][3] * b[3][0];
    *out[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] + a[2][3] * b[3][1];
    *out[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] + a[2][3] * b[3][2];
    *out[2][3] = a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] + a[2][3] * b[3][3];

    *out[3][0] = a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] + a[3][3] * b[3][0];
    *out[3][1] = a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] + a[3][3] * b[3][1];
    *out[3][2] = a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] + a[3][3] * b[3][2];
    *out[3][3] = a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] + a[3][3] * b[3][3];
}

void m4identity(mat4 *out)
{
    *out[0][0] = 1;
    *out[0][1] = 0;
    *out[0][2] = 0;
    *out[0][3] = 0;

    *out[1][0] = 0;
    *out[1][1] = 1;
    *out[1][2] = 0;
    *out[1][3] = 0;

    *out[2][0] = 0;
    *out[2][1] = 0;
    *out[2][2] = 1;
    *out[2][3] = 0;

    *out[3][0] = 0;
    *out[3][1] = 0;
    *out[3][2] = 0;
    *out[3][3] = 1;
}

void m4translate(mat4 *out, int x, int y, int z)
{
    *out[0][3] += x;
    *out[1][3] += y;
    *out[2][3] += z;
}

void m4scale(mat4 *out, int sx, int sy, int sz)
{
    *out[0][0] *= sx;
    *out[1][1] *= sy;
    *out[2][2] *= sz;
}

void m4rotate(mat4 *out, mat4 a, int rad, vec3 axis)
{

    int x = axis[0];
    int y = axis[1];
    int z = axis[2];

    int len = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    int s, c, t;
    int a00, a01, a02, a03;
    int a10, a11, a12, a13;
    int a20, a21, a22, a23;
    int b00, b01, b02;
    int b10, b11, b12;
    int b20, b21, b22;

    len = 1 / len;
    x *= len;
    y *= len;
    z *= len;
    s = sin(rad);
    c = cos(rad);
    t = 1 - c;

    a00 = a[0][0];
    a01 = a[0][1];
    a02 = a[0][2];
    a03 = a[0][3];
    a10 = a[1][0];
    a11 = a[1][1];
    a12 = a[1][2];
    a13 = a[1][3];
    a20 = a[2][0];
    a21 = a[2][1];
    a22 = a[2][2];
    a23 = a[2][3];

    // Construct the elements of the rotation matrix
    b00 = x * x * t + c;
    b01 = y * x * t + z * s;
    b02 = z * x * t - y * s;
    b10 = x * y * t - z * s;
    b11 = y * y * t + c;
    b12 = z * y * t + x * s;
    b20 = x * z * t + y * s;
    b21 = y * z * t - x * s;
    b22 = z * z * t + c;

    // Perform rotation-specific matrix multiplication
    *out[0][0] = a00 * b00 + a10 * b01 + a20 * b02;
    *out[0][1] = a01 * b00 + a11 * b01 + a21 * b02;
    *out[0][2] = a02 * b00 + a12 * b01 + a22 * b02;
    *out[0][3] = a03 * b00 + a13 * b01 + a23 * b02;
    *out[1][0] = a00 * b10 + a10 * b11 + a20 * b12;
    *out[1][1] = a01 * b10 + a11 * b11 + a21 * b12;
    *out[1][2] = a02 * b10 + a12 * b11 + a22 * b12;
    *out[1][3] = a03 * b10 + a13 * b11 + a23 * b12;
    *out[2][0] = a00 * b20 + a10 * b21 + a20 * b22;
    *out[2][1] = a01 * b20 + a11 * b21 + a21 * b22;
    *out[2][2] = a02 * b20 + a12 * b21 + a22 * b22;
    *out[2][3] = a03 * b20 + a13 * b21 + a23 * b22;

    if (a != *out)
    {
        // If the source and destination differ, copy the unchanged last row
        *out[3][0] = a[3][0];
        *out[3][1] = a[3][1];
        *out[3][2] = a[3][2];
        *out[3][3] = a[3][3];
    }
}

void m4perspective(mat4 *out, mat4 a, mat4 b, int fovy, int near, int far, int aspect)
{
    int f = 1.0 / tan(fovy / 2);
    int nf;

    *out[0][0] = f / aspect;
    *out[0][1] = 0;
    *out[0][2] = 0;
    *out[0][3] = 0;
    *out[1][0] = 0;
    *out[1][1] = f;
    *out[1][2] = 0;
    *out[1][3] = 0;
    *out[2][0] = 0;
    *out[2][1] = 0;
    *out[2][2] = -1;
    *out[2][3] = 0;
    *out[3][0] = 0;
    *out[3][2] = 0;

    if (far != NULL && far != INFINITY)
    {
        nf = 1 / (near - far);
        *out[2][2] = (far + near) * nf;
        *out[3][0] = 2 * far * near * nf;
    }
    else
    {
        *out[2][2] = -1;
        *out[3][0] = -2 * near;
    }
}

void v3add(vec3 *out, vec3 a, vec3 b) {
    *out[0] = a[0] + b[0];
    *out[1] = a[1] + b[1];
    *out[2] = a[2] + b[2];
}

void v3sub(vec3 *out, vec3 a, vec3 b) {
    *out[0] = a[0] - b[0];
    *out[1] = a[1] - b[1];
    *out[2] = a[2] - b[2];
}

void v3mul(vec3 *out, vec3 a, vec3 b) {
    *out[0] = a[0] * b[0];
    *out[1] = a[1] * b[1];
    *out[2] = a[2] * b[2];
}

void v3div(vec3 *out, vec3 a, vec3 b) {
    *out[0] = a[0] / b[0];
    *out[1] = a[1] / b[1];
    *out[2] = a[2] / b[2];
}

int v3dot(vec3 a, vec3 b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

int v3len(vec3 a) {
    return sqrt(vec3sqrLen(a));
}

int vec3sqrLen(vec3 a) {
    return pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2);
}