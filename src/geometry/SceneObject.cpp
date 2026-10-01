#include "SceneObject.h"

SceneObject::SceneObject(Mesh *mesh)
    : mesh(mesh), translate(Float3(0.0f, 0.0f, 0.0f)),
      rotate(Float3(0.0f, 0.0f, 0.0f)), color(Float3(1.0f, 1.0f, 1.0f)),
      scalar(1.0f), normals_as_color(false), draw(true) {}

SceneObject::~SceneObject() = default;

/*
std::array<Float2, 3> SceneObject::get_Face_Texture_Coordinates(int i) const {
    return std::array<Float2, 3>{
        mesh->texture_coordinates.at(
            mesh->faces.at(i).texture_coordinate_index.at(0) - 1),
        mesh->texture_coordinates.at(
            mesh->faces.at(i).texture_coordinate_index.at(1) - 1),
        mesh->texture_coordinates.at(
            mesh->faces.at(i).texture_coordinate_index.at(2) - 1)};
}
*/

Matrix3x4 SceneObject::get_transform_matrix() const {
	return Transform::object_transform(translate, rotate, scalar);
}

Matrix3x4 SceneObject::get_rotation_matrix() const {
	return Transform::rotate(rotate);
}
