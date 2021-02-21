#include <math.h>
#include <stdio.h>
/*

`x [00, 01, 02, 03]`
`y [04, 05, 06, 07]`
`z [08, 09, 10, 11]`
`w [12, 13, 14, 15]`
`_ [ x,_ y,_ z,_ w]`
*/
typedef float mat4[16];
typedef float vec3[3];
typedef float vec4[4];
typedef float vec2[2];
typedef int vec3i[3];
typedef int vec2i[2];
// typedef double vec3d[3];

void mat4_identity(mat4 *out) {
  *out[0] = 1;
  *out[1] = 0;
  *out[2] = 0;
  *out[3] = 0;

  *out[4] = 0;
  *out[5] = 1;
  *out[6] = 0;
  *out[7] = 0;

  *out[8] = 0;
  *out[9] = 0;
  *out[10] = 1;
  *out[11] = 0;

  *out[12] = 0;
  *out[13] = 0;
  *out[14] = 0;
  *out[15] = 1;
}

void mat4_multiply(mat4 *out, mat4 *a, mat4 *b) {
  *out[0] = *a[0] * *b[0] + *a[1] * *b[4] + *a[2] * *b[8] + *a[3] * *b[12];
  *out[1] = *a[0] * *b[1] + *a[1] * *b[5] + *a[2] * *b[9] + *a[3] * *b[13];
  *out[2] = *a[0] * *b[2] + *a[1] * *b[6] + *a[2] * *b[10] + *a[3] * *b[14];
  *out[3] = *a[0] * *b[3] + *a[1] * *b[7] + *a[2] * *b[11] + *a[3] * *b[15];

  *out[4] = *a[4] * *b[0] + *a[5] * *b[4] + *a[6] * *b[8] + *a[7] * *b[12];
  *out[5] = *a[4] * *b[1] + *a[5] * *b[5] + *a[6] * *b[9] + *a[7] * *b[13];
  *out[6] = *a[4] * *b[2] + *a[5] * *b[6] + *a[6] * *b[10] + *a[7] * *b[14];
  *out[7] = *a[4] * *b[3] + *a[5] * *b[7] + *a[6] * *b[11] + *a[7] * *b[15];

  *out[8] = *a[8] * *b[0] + *a[9] * *b[4] + *a[10] * *b[8] + *a[11] * *b[12];
  *out[9] = *a[8] * *b[1] + *a[9] * *b[5] + *a[10] * *b[9] + *a[11] * *b[13];
  *out[10] = *a[8] * *b[2] + *a[9] * *b[6] + *a[10] * *b[10] + *a[11] * *b[14];
  *out[11] = *a[8] * *b[3] + *a[9] * *b[7] + *a[10] * *b[11] + *a[11] * *b[15];

  *out[12] = *a[12] * *b[0] + *a[13] * *b[4] + *a[14] * *b[8] + *a[15] * *b[12];
  *out[13] = *a[12] * *b[1] + *a[13] * *b[5] + *a[14] * *b[9] + *a[15] * *b[13];
  *out[14] =
      *a[12] * *b[2] + *a[13] * *b[6] + *a[14] * *b[10] + *a[15] * *b[14];
  *out[15] =
      *a[12] * *b[3] + *a[13] * *b[7] + *a[14] * *b[11] + *a[15] * *b[15];
}

void mat4_set(mat4 *out, mat4 *a) {
  *out[0] = *a[0];
  *out[1] = *a[1];
  *out[2] = *a[2];
  *out[3] = *a[3];

  *out[4] = *a[4];
  *out[5] = *a[5];
  *out[6] = *a[6];
  *out[7] = *a[7];

  *out[8] = *a[8];
  *out[9] = *a[9];
  *out[10] = *a[10];
  *out[11] = *a[11];

  *out[12] = *a[12];
  *out[13] = *a[13];
  *out[14] = *a[14];
  *out[15] = *a[15];
}

void mat4_scale(mat4 *out, mat4 *a, vec3 *v) {
  *out[0] *= *v[0];
  *out[1] *= *v[0];
  *out[2] *= *v[0];
  *out[3] *= *v[0];
  *out[4] *= *v[1];
  *out[5] *= *v[1];
  *out[6] *= *v[1];
  *out[7] *= *v[1];
  *out[8] *= *v[2];
  *out[9] *= *v[2];
  *out[10] *= *v[2];
  *out[11] *= *v[2];
  *out[12] = *a[12];
  *out[13] = *a[13];
  *out[14] = *a[14];
  *out[15] = *a[15];
}

void mat4_translate(mat4 *out, mat4 *a, vec3 *v) {
  if (out != a)
    mat4_set(out, a);
  *out[12] = *a[0] * *v[0] + *a[4] * *v[1] + *a[8] * *v[2] + *a[12];
  *out[13] = *a[1] * *v[0] + *a[5] * *v[1] + *a[9] * *v[2] + *a[13];
  *out[14] = *a[2] * *v[0] + *a[6] * *v[1] + *a[10] * *v[2] + *a[14];
  *out[15] = *a[3] * *v[0] + *a[7] * *v[1] + *a[11] * *v[2] + *a[15];
}

// for rotation
#define a00 *a[0]
#define a01 *a[1]
#define a02 *a[2]
#define a03 *a[3]
#define a10 *a[4]
#define a11 *a[5]
#define a12 *a[6]
#define a13 *a[7]
#define a20 *a[8]
#define a21 *a[9]
#define a22 *a[10]
#define a23 *a[11]

void mat4_rotateX(mat4 *out, mat4 *a, double rad) {
  double s = sin(rad);
  double c = cos(rad);

  if (a != out) {
    // If the source and destination differ, copy the unchanged rows
    *out[0] = *a[0];
    *out[1] = *a[1];
    *out[2] = *a[2];
    *out[3] = *a[3];
    *out[12] = *a[12];
    *out[13] = *a[13];
    *out[14] = *a[14];
    *out[15] = *a[15];
  }

  // Perform axis-specific matrix multiplication
  *out[4] = a10 * c + a20 * s;
  *out[5] = a11 * c + a21 * s;
  *out[6] = a12 * c + a22 * s;
  *out[7] = a13 * c + a23 * s;
  *out[8] = a20 * c - a10 * s;
  *out[9] = a21 * c - a11 * s;
  *out[10] = a22 * c - a12 * s;
  *out[11] = a23 * c - a13 * s;
}

void mat4_rotateY(mat4 *out, mat4 *a, double rad) {
  double s = sin(rad);
  double c = cos(rad);

  if (a != out) {
    // If the source and destination differ, copy the unchanged rows
    *out[4] = *a[4];
    *out[5] = *a[5];
    *out[6] = *a[6];
    *out[7] = *a[7];
    *out[12] = *a[12];
    *out[13] = *a[13];
    *out[14] = *a[14];
    *out[15] = *a[15];
  }

  // Perform axis-specific matrix multiplication
  *out[0] = a00 * c - a20 * s;
  *out[1] = a01 * c - a21 * s;
  *out[2] = a02 * c - a22 * s;
  *out[3] = a03 * c - a23 * s;
  *out[8] = a00 * s + a20 * c;
  *out[9] = a01 * s + a21 * c;
  *out[10] = a02 * s + a22 * c;
  *out[11] = a03 * s + a23 * c;
}

void mat4_rotateZ(mat4 *out, mat4 *a, double rad) {
  double s = sin(rad);
  double c = cos(rad);

  if (a != out) {
    // If the source and destination differ, copy the unchanged last row
    *out[8] = *a[8];
    *out[9] = *a[9];
    *out[10] = *a[10];
    *out[11] = *a[11];
    *out[12] = *a[12];
    *out[13] = *a[13];
    *out[14] = *a[14];
    *out[15] = *a[15];
  }

  // Perform axis-specific matrix multiplication
  *out[0] = a00 * c + a10 * s;
  *out[1] = a01 * c + a11 * s;
  *out[2] = a02 * c + a12 * s;
  *out[3] = a03 * c + a13 * s;
  *out[4] = a10 * c - a00 * s;
  *out[5] = a11 * c - a01 * s;
  *out[6] = a12 * c - a02 * s;
  *out[7] = a13 * c - a03 * s;
}

#undef a00
#undef a01
#undef a02
#undef a03
#undef a10
#undef a11
#undef a12
#undef a13
#undef a20
#undef a21
#undef a22
#undef a23

void mat4_perspective(mat4 *out, mat4 *a, double fov, float aspect, float near, float far) {
  double f = tan(M_PI_2 - 0.5 * fov);
  double rangeInv = 1.0 / (near - far);

  *out[0] = f/aspect;
  *out[1] = 0;
  *out[2] = 0;
  *out[3] = 0;

  *out[4] = 0;
  *out[5] = f;
  *out[6] = 0;
  *out[7] = 0;

  *out[8] = 0;
  *out[9] = 0;
  *out[10] = (near + far) * rangeInv;
  *out[11] = -1;

  *out[12] = 0;
  *out[13] = 0;
  *out[14] = near * far * rangeInv * 2;
  *out[15] = 0;
}

void mat4_fromScaleRotationTranslation(mat4 *out, vec3 *scale, vec3 *rotation, vec3 *translation) {
    mat4_identity(out);
    mat4_scale(out, out, scale);
    mat4_rotateX(out, out, *rotation[0]);
    mat4_rotateY(out, out, *rotation[1]);
    mat4_rotateZ(out, out, *rotation[2]);
    mat4_translate(out, out, translation);
}

void mat4_applyVec3(vec4 *out, mat4 *a, vec3 *b) {
  vec4 v = {*b[0], *b[1], *b[2], 1};

  *out[0] = *a[0] * v[0] + *a[4] * v[1] + *a[8] * v[2] + *a[12] * v[3];
  *out[1] = *a[1] * v[0] + *a[5] * v[1] + *a[9] * v[2] + *a[13] * v[3];
  *out[2] = *a[2] * v[0] + *a[6] * v[1] + *a[10] * v[2] + *a[14] * v[3];
  *out[3] = *a[3] * v[0] + *a[7] * v[1] + *a[11] * v[2] + *a[15] * v[3];
}

void vec3_divf(vec3 *out, vec3*a, float b) {
  *out[0] /= b;
  *out[1] /= b;
  *out[2] /= b;
}

void vec3_fromV4(vec3 *out, vec4 *a) {
  *out[0] = *a[0];
  *out[1] = *a[1];
  *out[2] = *a[2];
}
// here
void vec3_set(vec3 *out, float x, float y, float z) {
  *out[0] = x;
  *out[1] = y;
  *out[2] = z;
}

void vec3_negate(vec3 *out, vec3 *a) {
  *out[0] = -*a[0];
  *out[1] = -*a[1];
  *out[2] = -*a[2];
}
// and there
// void vec3d_set(vec3d *out, double x, double y, double z) {
//   *out[0] = x;
//   *out[1] = y;
//   *out[2] = z;
// }

// void vec3d_negate(vec3d *out, vec3d *a) {
//   *out[0] = -*a[0];
//   *out[1] = -*a[1];
//   *out[2] = -*a[2];
// }

float flmap(float in, float fmin, float fmax, float tmin, float tmax) {
  return (in - fmin) / (fmax - fmin) * (tmax - tmin) + tmin;
}