/*

`x [00, 01, 02, 03]`
`y [04, 05, 06, 07]`
`z [08, 09, 10, 11]`
`w [12, 13, 14, 15]`
`_ [ x,_ y,_ z,_ w]`
*/
typedef float mat4[16];

typedef float vec4[4];

typedef float vec3[3];
typedef int vec3i[3];
// typedef double vec3d[3];

typedef float vec2[2];
typedef int vec2i[2];

void mat4_identity(mat4 *out);
void mat4_multiply(mat4 *out, mat4 *a, mat4 *b);
void mat4_set(mat4 *out, mat4 *a);
void mat4_scale(mat4 *out, mat4 *a, vec3 *v);
void mat4_translate(mat4 *out, mat4 *a, vec3 *v);
void mat4_rotateX(mat4 *out, mat4 *a, double rad);
void mat4_rotateY(mat4 *out, mat4 *a, double rad);
void mat4_rotateZ(mat4 *out, mat4 *a, double rad);
void mat4_perspective(mat4 *out, mat4 *a, double fov, float aspect, float near, float far);
void mat4_fromScaleRotationTranslation(mat4 *out, vec3 *scale, vec3 *rotation, vec3 *translation);
void mat4_applyVec3(vec4 *out, mat4 *a, vec3 *b);

void vec3_divf(vec3 *out, vec3*a, float b);
void vec3_fromV4(vec3 *out, vec4 *a);
void vec3_set(vec3 *out, float x, float y, float z);
void vec3_negate(vec3 *out, vec3 *a);

// void vec3d_set(vec3d *out, double x, double y, double z);
// void vec3d_negate(vec3d *out, vec3d *a);

float flmap(float in, float fmin, float fmax, float tmin, float tmax);