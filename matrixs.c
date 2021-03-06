#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef float mat4[4][4];
typedef float vec3[3];
typedef float vec2[2];
typedef vec3 triangle[3];

void m4mul(mat4 out, mat4 a, mat4 b)
{
    out[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] + a[0][3] * b[3][0];
    out[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] + a[0][3] * b[3][1];
    out[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] + a[0][3] * b[3][2];
    out[0][3] = a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] + a[0][3] * b[3][3];

    out[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] + a[1][3] * b[3][0];
    out[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] + a[1][3] * b[3][1];
    out[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] + a[1][3] * b[3][2];
    out[1][3] = a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] + a[1][3] * b[3][3];

    out[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] + a[2][3] * b[3][0];
    out[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] + a[2][3] * b[3][1];
    out[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] + a[2][3] * b[3][2];
    out[2][3] = a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] + a[2][3] * b[3][3];

    out[3][0] = a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] + a[3][3] * b[3][0];
    out[3][1] = a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] + a[3][3] * b[3][1];
    out[3][2] = a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] + a[3][3] * b[3][2];
    out[3][3] = a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] + a[3][3] * b[3][3];
}

void m4identity(mat4 out)
{
    out[0][0] = 1;
    out[0][1] = 0;
    out[0][2] = 0;
    out[0][3] = 0;

    out[1][0] = 0;
    out[1][1] = 1;
    out[1][2] = 0;
    out[1][3] = 0;

    out[2][0] = 0;
    out[2][1] = 0;
    out[2][2] = 1;
    out[2][3] = 0;

    out[3][0] = 0;
    out[3][1] = 0;
    out[3][2] = 0;
    out[3][3] = 1;
}

void m4translate(mat4 out, mat4 a, float x, float y, float z)
{
    /* if (a == out)
    {
        out[3][0] = a[0][0] * x + a[1][0] * y + a[2][0] * z + a[3][0];
        out[3][1] = a[0][1] * x + a[1][1] * y + a[2][1] * z + a[3][1];
        out[3][2] = a[0][2] * x + a[1][2] * y + a[2][2] * z + a[3][2];
        out[3][3] = a[0][3] * x + a[1][3] * y + a[2][3] * z + a[3][3];
    }
    else
    {
        a[0][0] = a[0][0];
        a[0][1] = a[0][1];
        a[0][2] = a[0][2];
        a[0][3] = a[0][3];
        a[1][0] = a[1][0];
        a[1][1] = a[1][1];
        a[1][2] = a[1][2];
        a[1][3] = a[1][3];
        a[2][0] = a[2][0];
        a[2][1] = a[2][1];
        a[2][2] = a[2][2];
        a[2][3] = a[2][3];
        out[0][0] = a[0][0];
        out[0][1] = a[0][1];
        out[0][2] = a[0][2];
        out[0][3] = a[0][3];
        out[1][0] = a[1][0];
        out[1][1] = a[1][1];
        out[1][2] = a[1][2];
        out[1][3] = a[1][3];
        out[2][0] = a[2][0];
        out[2][1] = a[2][1];
        out[2][2] = a[2][2];
        out[2][3] = a[2][3];
        out[3][0] = a[0][0] * x + a[1][0] * y + a[2][0] * z + a[3][0];
        out[3][1] = a[0][1] * x + a[1][1] * y + a[2][1] * z + a[3][1];
        out[3][2] = a[0][2] * x + a[1][2] * y + a[2][2] * z + a[3][2];
        out[3][3] = a[0][3] * x + a[1][3] * y + a[2][3] * z + a[3][3];
    } */
    out[0][3] += x;
    out[1][3] += y;
    out[2][3] += z;
}

void m4scale(mat4 out, mat4 a, float sx, float sy, float sz)
{
    out[0][0] = a[0][0] * sx;
    out[0][1] = a[0][1] * sx;
    out[0][2] = a[0][2] * sx;
    out[0][3] = a[0][3] * sx;
    out[1][0] = a[1][0] * sy;
    out[1][1] = a[1][1] * sy;
    out[1][2] = a[1][2] * sy;
    out[1][3] = a[1][3] * sy;
    out[2][0] = a[2][0] * sz;
    out[2][1] = a[2][1] * sz;
    out[2][2] = a[2][2] * sz;
    out[2][3] = a[2][3] * sz;
    out[3][0] = a[3][0];
    out[3][1] = a[3][1];
    out[3][2] = a[3][2];
    out[3][3] = a[3][3];
}

void m4rotate(mat4 out, mat4 a, float rad, vec3 axis)
{

    float x = axis[0];
    float y = axis[1];
    float z = axis[2];

    float len = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    float s, c, t;
    float a00, a01, a02, a03;
    float a10, a11, a12, a13;
    float a20, a21, a22, a23;
    float b00, b01, b02;
    float b10, b11, b12;
    float b20, b21, b22;

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
    out[0][0] = a00 * b00 + a10 * b01 + a20 * b02;
    out[0][1] = a01 * b00 + a11 * b01 + a21 * b02;
    out[0][2] = a02 * b00 + a12 * b01 + a22 * b02;
    out[0][3] = a03 * b00 + a13 * b01 + a23 * b02;
    out[1][0] = a00 * b10 + a10 * b11 + a20 * b12;
    out[1][1] = a01 * b10 + a11 * b11 + a21 * b12;
    out[1][2] = a02 * b10 + a12 * b11 + a22 * b12;
    out[1][3] = a03 * b10 + a13 * b11 + a23 * b12;
    out[2][0] = a00 * b20 + a10 * b21 + a20 * b22;
    out[2][1] = a01 * b20 + a11 * b21 + a21 * b22;
    out[2][2] = a02 * b20 + a12 * b21 + a22 * b22;
    out[2][3] = a03 * b20 + a13 * b21 + a23 * b22;

    if (a != out)
    {
        // If the source and destination differ, copy the unchanged last row
        out[3][0] = a[3][0];
        out[3][1] = a[3][1];
        out[3][2] = a[3][2];
        out[3][3] = a[3][3];
    }
}

void m4perspective(mat4 out, float fovy, float near, float far, float aspect)
{
    float f = 1.0 / tan(fovy / 2);
    float nf;

    out[0][0] = f / aspect;
    out[0][1] = 0;
    out[0][2] = 0;
    out[0][3] = 0;
    out[1][0] = 0;
    out[1][1] = f;
    out[1][2] = 0;
    out[1][3] = 0;
    out[2][0] = 0;
    out[2][1] = 0;
    out[2][2] = -1;
    out[2][3] = 0;
    out[3][0] = 0;
    out[3][2] = 0;

    if (far != INFINITY)
    {
        nf = 1 / (near - far);
        out[2][2] = (far + near) * nf;
        out[3][0] = 2 * far * near * nf;
    }
    else
    {
        out[2][2] = -1;
        out[3][0] = -2 * near;
    }
}

void m4set(mat4 out, mat4 in)
{
    out[0][0] = in[0][0];
    out[0][1] = in[0][1];
    out[0][2] = in[0][2];
    out[0][3] = in[0][3];
    out[1][0] = in[1][0];
    out[1][1] = in[1][1];
    out[1][2] = in[1][2];
    out[1][3] = in[1][3];
    out[2][0] = in[2][0];
    out[2][1] = in[2][1];
    out[2][2] = in[2][2];
    out[2][3] = in[2][3];
    out[3][0] = in[3][0];
    out[3][1] = in[3][1];
    out[3][2] = in[3][2];
    out[3][3] = in[3][3];
}

void m4print(mat4 a)
{
    printf("[\n");
    printf("   [%f, ", a[0][0]);
    printf("   %f, ", a[0][1]);
    printf("   %f, ", a[0][2]);
    printf("   %f]\n", a[0][3]);
    printf("   [%f, ", a[1][0]);
    printf("   %f, ", a[1][1]);
    printf("   %f, ", a[1][2]);
    printf("   %f]\n", a[1][3]);
    printf("   [%f, ", a[2][0]);
    printf("   %f, ", a[2][1]);
    printf("   %f, ", a[2][2]);
    printf("   %f]\n", a[2][3]);
    printf("   [%f, ", a[3][0]);
    printf("   %f, ", a[3][1]);
    printf("   %f, ", a[3][2]);
    printf("   %f]\n", a[3][3]);
    printf("]\n");
}

void v3add(vec3 out, vec3 a, vec3 b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

void v3addFloat(vec3 out, vec3 a, float b)
{
    out[0] = a[0] + b;
    out[1] = a[1] + b;
    out[2] = a[2] + b;
}

void v3sub(vec3 out, vec3 a, vec3 b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

void v3subFloat(vec3 out, vec3 a, float b)
{
    out[0] = a[0] - b;
    out[1] = a[1] - b;
    out[2] = a[2] - b;
}

void v3mul(vec3 out, vec3 a, vec3 b)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}

void v3mulFloat(vec3 out, vec3 a, float b)
{
    out[0] = a[0] * b;
    out[1] = a[1] * b;
    out[2] = a[2] * b;
}

void v3div(vec3 out, vec3 a, vec3 b)
{
    out[0] = a[0] / b[0];
    out[1] = a[1] / b[1];
    out[2] = a[2] / b[2];
}

void v3divFloat(vec3 out, vec3 a, float b)
{
    out[0] = a[0] / b;
    out[1] = a[1] / b;
    out[2] = a[2] / b;
}

float v3dot(vec3 a, vec3 b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float v3sqrLen(vec3 a)
{
    return v3dot(a, a);
}

float v3len(vec3 a)
{
    return sqrt(v3sqrLen(a));
}

void v3normalize(vec3 out, vec3 a)
{
    float len = v3len(a);
    out[0] = a[0] / len;
    out[1] = a[1] / len;
    out[2] = a[2] / len;
}

float v3applyMat4(vec3 out, vec3 a, mat4 b)
{
    out[0] = b[0][0] * a[0] + b[0][1] * a[1] + b[0][2] * a[2] + b[0][3];
    out[1] = b[1][0] * a[0] + b[1][1] * a[1] + b[1][2] * a[2] + b[1][3];
    out[2] = b[2][0] * a[0] + b[2][1] * a[1] + b[2][2] * a[2] + b[2][3];
    return   b[3][0] * a[0] + b[3][1] * a[1] + b[3][2] * a[2] + b[3][3];
}

void v3set(vec3 out, vec3 in)
{
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
}

void v3print(vec3 a)
{
    printf("[%f, ", a[0]);
    printf("%f, ", a[1]);
    printf("%f]\n", a[2]);
}

void v3map(vec3 out, vec3 in, float fromMin, float fromMax, float toMin, float toMax) {
    out[0] = (in[0] - fromMin) / (fromMax - fromMin) * (toMax - toMin) + toMin;
    out[1] = (in[1] - fromMin) / (fromMax - fromMin) * (toMax - toMin) + toMin;
    out[2] = (in[2] - fromMin) / (fromMax - fromMin) * (toMax - toMin) + toMin;
}

void v2sub(vec2 out, vec2 a, vec2 b) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
}

void v2add(vec2 out, vec2 a, vec2 b) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
}

float v2dot(vec2 a, vec2 b)
{
    return a[0] * b[0] + a[1] * b[1];
}

float v2len(vec2 a) {
    return sqrt(a[0] * a[0] + a[1] * a[1]);
}

void v2mul(vec2 out, vec2 a, vec2 b) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
}

void v2print(vec2 a) {
    printf("[%f, ", a[0]);
    printf("%f]\n", a[1]);
}


void v3toV2(vec2 out, vec3 a) {
    out[0] = a[0];
    out[1] = a[1];
}

void v2toV3(vec3 out, vec2 a) {
    out[0] = a[0];
    out[1] = a[1];
    out[2] = 1;
}

void v2normalize(vec2 out, vec2 a) {
    float len = v2len(a);
    out[0] = a[0] / len;
    out[1] = a[1] / len;
}

void v2toBarycentric(vec2 out, vec2 a, triangle triangle) {
    float dx = a[0]-triangle[2][0];
    float dy = a[0]-triangle[2][1];
    float dx21 = triangle[2][0]-triangle[1][0];
    float dy12 = triangle[1][1]-triangle[2][1];
    float D = dy12*(triangle[0][0]-triangle[2][0]) + dx21*(triangle[0][1]-triangle[2][1]);
    float s = dy12*dx + dx21*dy;
    float t = (triangle[2][1]-triangle[0][1])*dx + (triangle[0][0]-triangle[2][0])*dy;
    out[0] = s;
    out[1] = t;
}

float flMap(float num, float fmin, float fmax, float tmin, float tmax) {
    return (num - fmin) / (fmax - fmin) * (tmax - tmin) + tmin;
}

float v2computeAreaTriangle(vec2 tri[3]) {
    vec2 side1[2] = {*tri[0], *tri[1]};
    vec2 side2[2] = {*tri[1], *tri[2]};
    vec2 a;
    v2sub(a, side1[1], side1[0]);
    v2normalize(a, a);
    vec2 v;
    v2sub(v, side2[1], side2[0]);
    float dot = v2dot(v, a);
    vec2 dotv = {dot, dot};
    vec2 p;
    v2mul(p, a, dotv);
    vec2 point;
    v2add(point, side1[1], p);
    vec2 h;
    v2sub(h, side2[1], point);
    vec2 b;
    v2sub(a, side1[1], side1[0]);
    float hLen = v2len(h);
    float bLen = v2len(b);
    return (hLen + bLen) / 2;
}

int v2isInTriangle(vec2 p, vec2 triangle[3]) {
    vec2 t1[3] = {
        *p,
        *triangle[0],
        *triangle[1]
    };
    vec2 t2[3] = {
        *p,
        *triangle[1],
        *triangle[2]
    };
    vec2 t3[3] = {
        *p,
        *triangle[2],
        *triangle[0]
    };
    float area0 = v2computeAreaTriangle(triangle);
    float area1 = v2computeAreaTriangle(t1);
    float area2 = v2computeAreaTriangle(t2);
    float area3 = v2computeAreaTriangle(t3);
    float areaSum = area1 + area2 + area3;
    return areaSum == area0;
}

