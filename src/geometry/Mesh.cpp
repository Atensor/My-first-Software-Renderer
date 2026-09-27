#include "Mesh.h"
#include <algorithm>

Mesh *Mesh::find_mesh(const std::vector<std::unique_ptr<Mesh>> &meshes,
                      const std::string &name) {
	auto it = std::find_if(
	    meshes.begin(), meshes.end(),
	    [&](const std::unique_ptr<Mesh> &mesh) { return mesh->name == name; });
	return it != meshes.end() ? &*it->get() : nullptr;
}

// TODO: transform all vertices/normals of the mesh
/*
void Mesh::transform_vertices(const Matrix4 &transform, const Matrix4 &rotate,
                              std::vector<Float4> *transformed_vertices,
                              std::vector<Float4> *transformed_normals) const {
    for (int i = 0;auto &vertex : vertices) {
        Transform::transform(vertex, transform, rotate);
*/
