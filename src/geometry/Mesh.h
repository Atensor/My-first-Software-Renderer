#include "Face.h"
#include "math/Transform.h"
#include <memory>
#include <string>
#include <vector>

#ifndef MESH_H
#define MESH_H

struct Mesh {
	std::vector<Float4> vertices;
	std::vector<Float4> normals;
	std::vector<Float2> texture_coordinates;

	std::vector<Face> faces;
	std::string name;

	static Mesh *find_mesh(const std::vector<std::unique_ptr<Mesh>> &meshes,
	                       const std::string &name);

	void transform_vertices(const Matrix4 &transform, const Matrix4 &rotate,
	                        std::vector<Float4> *transformed_verices) const;
};

#endif
