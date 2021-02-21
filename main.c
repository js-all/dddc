#include "matrixs.h"
#include "vectors.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define Z_NEAR 0.1
#define Z_FAR 100.0
#define WIDTH 140
#define HEIGHT 37
#define EMPTY_CHAR ' '
#define CORNER_CHAR 'O'
#define FOV_IN_DEGREES 100.0

struct Transforms {
  vec3 translation;
  vec3 scale; // needs to be in that exact order otherwise it crashes because of stack smashing
  vec3 rotation;
};

struct Camera {
    double fov;
    float aspect;
    float near;
    float far;
    struct Transforms transforms;
};

struct Object {
  struct Transforms transforms;
  // vector of pointers of vec3
  vector mesh;
  // vector of pointers of vec3i (each triangle stored as an int[3] with the indexes of the used points in the mesh vector)
  vector triangles;
};

static float aspect = (float)WIDTH / HEIGHT;
static double fov = FOV_IN_DEGREES / 180.0 * M_PI;
static int area = WIDTH * HEIGHT;

void transforms_computeMatrix(struct Transforms *transforms, mat4 *out, bool invert) {
  if(invert) { // mostly for the camera, to be able to compute the view matrix
    vec3 translation;
    vec3 scale;
    vec3 rotation;
    vec3_negate(&translation, &transforms->translation);
    vec3_negate(&scale, &transforms->scale);
    vec3_negate(&rotation, &transforms->rotation);
    mat4_fromScaleRotationTranslation(out, &scale, &rotation, &translation);
  } else {
    mat4_fromScaleRotationTranslation(out, &transforms->scale, &transforms->rotation, &transforms->translation);
  }
}

void camera_computeViewMatrix(struct Camera *camera, mat4 *out) {
  transforms_computeMatrix(&camera->transforms, out, true);
}
void camera_computePerspectiveMatrix(struct Camera *camera, mat4 *out) {
  mat4_perspective(out, out, camera->fov, camera->aspect, camera->near, camera->far);
}
// initialize object, mostly just allocate memory to the vectors
//
// mesh and triangles can be empty arrays, if so, meshSize and trianglesSize should be 0
int object_init(struct Object *obj, vec3 (*mesh)[], vec3i (*triangles)[], int meshSize, int trianglesSize) {
  int res1, res2;

  res1 = vector_init(&obj->mesh, meshSize);
  // push all elements in the vector (probably not verry efficient but it will
  // be run once at startup so not a problem)
  for (int i = 0; i < meshSize; i++) {
    vector_push(&obj->mesh, (&mesh)[i]);
  }
  res2 = vector_init(&obj->triangles, trianglesSize);
  for (int i = 0; i < trianglesSize; i++) {
    vector_push(&obj->triangles, (&triangles)[i]);
  }
  if (res1 != 0) {
    printf(
        "ERROR: Main, error in main whilst initailizing object mesh vector\n");
    return -1;
  }
  if (res2 != 0) {
    printf("ERROR: Main, error in main whilst initailizing object triangles "
           "vector\n");
    return -1;
  }
  return 0;
}
void object_computeModelMatrix(struct Object *obj, mat4 *out) {
  transforms_computeMatrix(&obj->transforms, out, false);
}
// allocate memory for a string long enough for every pixel of the display, and fill it with empty char
char* initRenderingString() {
  char *str = malloc((area + 1) * sizeof(char));
  memset(str, (int) EMPTY_CHAR, area * sizeof(char));
  str[area] = '\0';
  return str;
}
// pretty useless right now, might become bigger later
void freeRenderingString(char* str) {
  free(str);
}
// print the rendreing string with new lines character to make the output the right dimensions
void printRenderingString(char* str) {
  for(int i = 0; i < area; i += WIDTH) {
    printf("%.*s\n", WIDTH, str + (i * sizeof(char)));
  }
}

int main() {
  char *renderingString = initRenderingString();
  struct Camera camera;
  struct Object obj;

  camera.fov = fov;
  camera.aspect = aspect;
  camera.near = Z_NEAR;
  camera.far = Z_FAR;

  vec3_set(&camera.transforms.translation, 0, 0, 0);
  vec3_set(&camera.transforms.scale, 1, 1, 1);
  vec3_set(&camera.transforms.rotation, 0, 0, 0);
  
  vec3 mesh[] = {{-1, -1, -10}, {-1, 1, -10}, {1, -1, -10}};
  vec3i triangles[] = {{0, 1, 2}};
  object_init(&obj, &mesh, &triangles, sizeof(mesh) / sizeof(vec3), sizeof(triangles) / sizeof(vec3i));
  vec3_set(&obj.transforms.translation, 0, 0, 0);
  vec3_set(&obj.transforms.scale, 1, 1, 1);
  vec3_set(&obj.transforms.rotation, 0, 0, 0);

  {
    mat4 viewMatrix;
    mat4 perspectiveMatrix;
    mat4 modelMatrix;
    mat4 modelViewMatrix;
    mat4 masterMatrix;

    camera_computeViewMatrix(&camera, &viewMatrix);
    camera_computePerspectiveMatrix(&camera, &perspectiveMatrix);
    object_computeModelMatrix(&obj, &modelMatrix);

    mat4_multiply(&modelViewMatrix, &modelMatrix, &viewMatrix);
    mat4_multiply(&masterMatrix, &modelViewMatrix, &perspectiveMatrix);

    for(int i = 0; i < obj.mesh.used; i++) {
      vec4 transformedVertex;
      mat4_applyVec3(&transformedVertex, &masterMatrix, (vec3*)(obj.mesh.data[i]));
      vec3 projectedVertex;
      vec3_fromV4(&projectedVertex, &transformedVertex);
      vec3_divf(&projectedVertex, &projectedVertex, transformedVertex[3]);
      // at this point v3 is:
      // contained in -1, 1 in every axis
      // positive y up, x sideways, and -z depth
      vec2i mappedVertex = {
        (int) floor(flmap(projectedVertex[0], -1, 1, 0, WIDTH)),
        (int) floor(flmap(projectedVertex[1], -1, 1, HEIGHT, 0))
      };
      int renderingStringIndex = mappedVertex[1] * WIDTH + mappedVertex[0];
      renderingString[renderingStringIndex] = CORNER_CHAR;
    }
  }

  printRenderingString(renderingString);

  freeRenderingString(renderingString);

  return 0;
}