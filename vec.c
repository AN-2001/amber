#include "vec.h"
#include <math.h>
#define EPSILON 1e-5
double vecMag(Vec2 v){
	return sqrt(v.x * v.x + v.y * v.y);
}
Vec2 vecNorm(Vec2 v){
	double mag = vecMag(v);
	if(mag < EPSILON)
		return v;
	return vecScale(v, 1.0f/mag);
}
Vec2 vecAdd(Vec2 v, Vec2 u){
	return VEC_CREATE(v.x + u.x, v.y + u.y);
}
Vec2 vecScale(Vec2 v, double s){
	return VEC_CREATE(v.x * s, v.y * s);
}
