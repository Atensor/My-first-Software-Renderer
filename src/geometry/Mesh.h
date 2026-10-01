#include "Face.h"
#include <memory>
#include <string>
#include <vector>

#ifndef MESH_H
#define MESH_H

struct Mesh {
	std::vector<Float3> positions;
	std::vector<Float3> normals;
	// std::vector<Float2> texture_coordinates;

	std::vector<Face> faces;
	std::string name;

	static Mesh *find_mesh(const std::vector<std::unique_ptr<Mesh>> &meshes,
	                       const std::string &name);
};

#endif
