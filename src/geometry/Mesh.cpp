#include "Mesh.h"
#include <algorithm>

Mesh *Mesh::find_mesh(const std::vector<std::unique_ptr<Mesh>> &meshes,
                      const std::string &name) {
	auto it = std::find_if(
	    meshes.begin(), meshes.end(),
	    [&](const std::unique_ptr<Mesh> &mesh) { return mesh->name == name; });
	return it != meshes.end() ? &*it->get() : nullptr;
}
