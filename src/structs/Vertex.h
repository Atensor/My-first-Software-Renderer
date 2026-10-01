#include "../math/vector/Float4.h"

#ifndef VERTEX_H
#define VERTEX_H
struct Vertex {
	Float3 pos;
	Float3 normal;
	Float3 color;

	float light;
};
#endif
