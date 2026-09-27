struct Edge {
	float x;
	float step;
	int y_end;

	Edge(float x0, float y0, float x1, float y1);

	void step_x();
};
