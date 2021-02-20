#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef float mat4[4][4];
typedef float vec3[3];
typedef float vec2[2];
typedef vec3 triangle[3];

void m4mul(mat4 out, mat4 a, mat4 b);
void m4identity(mat4 out);
void m4translate(mat4 out, mat4 a, float x, float y, float z);
void m4scale(mat4 out, mat4 a, float sx, float sy, float sz);
void m4rotate(mat4 out, mat4 a, float rad, vec3 axis);
void m4perspective(mat4 out, float fovy, float near, float far, float aspect);
void m4set(mat4 out, mat4 in);
void m4print(mat4 a);

void v3add(vec3 out, vec3 a, vec3 b);
void v3addFloat(vec3 out, vec3 a, float b);
void v3sub(vec3 out, vec3 a, vec3 b);
void v3subFloat(vec3 out, vec3 a, float b);
void v3mul(vec3 out, vec3 a, vec3 b);
void v3mulFloat(vec3 out, vec3 a, float b);
void v3div(vec3 out, vec3 a, vec3 b);
void v3divFloat(vec3 out, vec3 a, float b);
float v3dot(vec3 a, vec3 b);
float v3sqrLen(vec3 a);
float v3len(vec3 a);
void v3normalize(vec3 out, vec3 a);
float v3applyMat4(vec3 out, vec3 a, mat4 b);
void v3set(vec3 out, vec3 in);
void v3print(vec3 a);
void v3map(vec3 out, vec3 in, float fromMin, float fromMax, float toMin, float toMax); 

void v2sub(vec2 out, vec2 a, vec2 b); 
void v2add(vec2 out, vec2 a, vec2 b); 
float v2dot(vec2 a, vec2 b);
float v2len(vec2 a); 
void v2mul(vec2 out, vec2 a, vec2 b); 
void v2print(vec2 a); void v3toV2(vec2 out, vec3 a); 
void v2toV3(vec3 out, vec2 a); 
void v2normalize(vec2 out, vec2 a); 
void v2toBarycentric(vec2 out, vec2 a, triangle triangle); 
float v2computeAreaTriangle(vec2 tri[3]); 
int v2isInTriangle(vec2 p, vec2 triangle[3]); 

float flMap(float num, float fmin, float fmax, float tmin, float tmax); 
