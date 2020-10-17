#include <stdio.h>
#include <math.h>
#include <time.h>
#include "matrixs.c"
#include <string.h>
#include <stdbool.h>

#define zNear 0.1
#define zFar 100
#define meshLen 8
#define triangleCount 12
#define size 20

/**
 * 
 * * check https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
 * 
 */
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

static int triangles[triangleCount][3] = {
    {0, 1, 2},
    {1, 3, 2},
    {6, 7, 2},
    {7, 3, 2},
    {4, 6, 0},
    {6, 2, 0},
    {5, 7, 3},
    {5, 3, 1},
    {4, 5, 0},
    {5, 1, 0},
    {4, 5, 6},
    {5, 7, 6}
};

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
        string[i] = '.';
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
    vec2 tr[3] = {
        {0, 0},
        {1, 0},
        {0.5, -1}
    };
    vec2 point = {0.5, -2};
    printf("%d", v2isInTriangle(point, tr) );
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
            float w = v3applyMat4(resPoint, mesh[i], masterMatrix);
            //v3divFloat(resPoint, resPoint, 1);
            v3set(projectedPoints[i], resPoint);
        };

        char resStr[size * size];
        initString(resStr);

        for(int x = 0; x < size; x++) {
            for(int y = 0; y < size; y++) {
                int stringLoc = x * size + y;
                vec2 pixel;
                pixel[0] = flMap(x, 0, size, -1, 1);
                pixel[1] = flMap(y, 0, size, -1, 1);
                for(int i = 0; i < triangleCount; i++) {
                    vec3 t1;
                    vec3 t2;
                    vec3 t3;
                    v3set(t1, projectedPoints[triangles[i][0]]);
                    v3set(t2, projectedPoints[triangles[i][1]]);
                    v3set(t3, projectedPoints[triangles[i][2]]);
                    vec2 tri[3] = {
                        {t1[0], t1[1]},
                        {t2[0], t2[1]},
                        {t3[0], t3[1]},
                    };
                    if(v2isInTriangle(pixel, tri) && resStr[stringLoc] != 'O') {
                        // printf("pixel: ");
                        // v2print(pixel);
                        // printf("triangle: \n");
                        // vec2 p0;
                        // vec2 p1;
                        // vec2 p2;
                        // v3toV2(p0, tri[0]);
                        // v3toV2(p1, tri[1]);
                        // v3toV2(p2, tri[2]);
                        // v2print(p0);
                        // v2print(p1);
                        // v2print(p2);
                        // printf("/--/\n");
                        resStr[stringLoc] = 'O';
                    }
                }
            }
        }

        for (int j = 0; j < meshLen; j++)
        {
            int px = floor((projectedPoints[j][0] + 1.0) / 2.0 * size);
            int py = floor((projectedPoints[j][1] + 1.0) / 2.0 * size);
            resStr[px * size + py] = '#';
        }

        drawString(resStr);
        printf("\n");
        struct timespec ts;
        ts.tv_nsec = 0;
        ts.tv_sec = 1;
        nanosleep(&ts, &ts);
        //objRot[0] += rad(5);
        //objRot[1] += rad(10);
        objRot[1] += rad(10);
    }

    return 0;
}

