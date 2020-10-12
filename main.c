#include <stdio.h>
#include <math.h>
#include <time.h>
#include "matrixs.c"
#include <string.h>

#define zNear 0.1
#define zFar 100
#define meshLen 8
#define size 30

vec3 objRot = {0, 0, 0};
vec3 objSca = {.25, .25, .25};
vec3 objTra = {0, 0, 1};

float fov;
float aspect = 16 / 9;

static vec3 mesh[meshLen] = {
    {-1, -1, -1},
    {1, -1, -1},
    {-1, -1, 1},
    {1, -1, 1},
    {-1, 1, -1},
    {1, 1, -1},
    {-1, 1, 1},
    {1, 1, 1}};

void computeModelMatrix(mat4 out, vec3 scale, vec3 rotation, vec3 translation)
{

    vec3 axisX = {1, 0, 0};
    vec3 axisY = {0, 1, 0};
    vec3 axisZ = {0, 0, 1};
    m4identity(out);
    m4scale(out, out, scale[0], scale[1], scale[2]);
    m4rotate(out, out, rotation[0], axisX);
    m4rotate(out, out, rotation[1], axisY);
    m4rotate(out, out, rotation[2], axisZ);
    m4translate(out, out, translation[0], translation[1], translation[2]);
}

void drawString(char string[size * size])
{
    for (int s = 0; s < strlen(string); s++)
    {
        printf("%c", string[s]);
        if (s > 0 && (s + 1) % size == 0)
        {
            printf("\n");
        }
    }
}

void initString(char string[size * size])
{
    for (int i = 0; i < size * size; i++)
    {
        string[i] = ' ';
    }
}

float rad(float in)
{
    return in / 180 * M_PI;
}

int main(int argc, char *argv[])
{
    fov = rad(90);
    objRot[0] = rad(45);

    while (1)
    {
        mat4 modelMatrix;
        computeModelMatrix(modelMatrix, objSca, objRot, objTra);
        mat4 projectionMatrix;
        m4identity(projectionMatrix);
        m4perspective(projectionMatrix, fov, zNear, zFar, aspect);
        mat4 masterMatrix;
        m4mul(masterMatrix, modelMatrix, projectionMatrix);

        vec3 projectedPoints[meshLen];

        for (int i = 0; i < meshLen; i++)
        {
            vec3 resPoint;
            v3applyMat4(resPoint, mesh[i], masterMatrix);
            v3set(projectedPoints[i], resPoint);
        };

        char resStr[size * size];
        initString(resStr);

        for (int j = 0; j < meshLen; j++)
        {
            int px = floor((projectedPoints[j][0] + 1.0) / 2.0 * size);
            int py = floor((projectedPoints[j][1] + 1.0) / 2.0 * size);
            resStr[px * size + py] = 'O';
        }
        drawString(resStr);
        printf("\n");
        struct timespec ts;
        ts.tv_nsec = 0;
        ts.tv_sec = 1;
        nanosleep(&ts, &ts);
        //objRot[0] += rad(5);
        //objRot[1] += rad(10);
        objRot[2] += rad(10);
    }

    return 0;
}
