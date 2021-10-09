#ifndef VEC_H
#define VEC_H
#define VEC_CREATE(u, v) (Vec2){.x = (u), .y = (v)}
typedef struct{
	float x,y;
} Vec2;

Vec2 vecNorm(Vec2 v);
Vec2 vecAdd(Vec2 v, Vec2 u);
Vec2 vecScale(Vec2 v, double s);
double vecMag(Vec2 v);
#endif // VEC_H
