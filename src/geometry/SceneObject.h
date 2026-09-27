#include "../math/Transform.h"
#include "Mesh.h"
#include <memory>

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

struct SceneObject {
	Mesh *mesh;

	Float4 color;

	Float4 translate;
	Float3 rotate;
	float scalar;

	bool normals_as_color;
	bool draw;

	SceneObject(Mesh *mesh);
	~SceneObject();

	std::array<Vertex, 3> get_Face_Vertices(int i) const;
	std::array<Float2, 3> get_Face_Texture_Coordinates(int i) const;

	Matrix4 get_transform_matrix() const;

	Matrix4 get_rotation_matrix() const;
};

#endif
