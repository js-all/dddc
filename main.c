#include <stdio.h>
#include <math.h>
#include "matrixs.c"
#include <string.h>

#define zNear 0.1
#define zFar 100
#define meshLen 8
#define size 50

vec3 objRot = {0, 0, 0};
vec3 objSca = {1, 1, 1};
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

float rad(float in)
{
    return in / 180 * M_PI;
}

int main(int argc, char *argv[])
{
    fov = rad(90);
    objRot[1] = rad(45);


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
        projectedPoints[i][0] = resPoint[0];
        projectedPoints[i][1] = resPoint[1];
        projectedPoints[i][2] = resPoint[2];
    };

    char resStr[size * size];

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            for (int j = 0; j < meshLen; j++)
            {
                int px = floor((projectedPoints[j][0] + 1.0) / 2.0 * size);
                int py = floor((projectedPoints[j][1] + 1.0) / 2.0 * size);
                if (px == x && py == y)
                {
                    resStr[y * size + x] = '@';
                }
                else
                {
                    resStr[y * size + x] = 'o';
                }
            }
        }
    }

    for (int s = 0; s < strlen(resStr); s++)
    {
        printf("%c", resStr[s]);
        if (s > 0 && s % size == 0)
        {
            printf("\n");
        }
    }

    objRot[0] += 0.01;
    objRot[1] += 0.02;
    objRot[2] += 0.005;

    return 0;
}
