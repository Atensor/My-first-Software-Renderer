#include "Edge.h"
#include <cmath>

Edge::Edge(float x0, float y0, float x1, float y1)
    : y_end(static_cast<int>(std::ceil(y1))) {
	step = (x1 - x0) / (y1 - y0);

	int y_start = static_cast<int>(std::ceil(y0));
	x = x0 + (y_start - y0) * step;
}

void Edge::step_x() { x += step; }
