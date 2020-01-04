#include "Object.h"

void Object::AddMesh(Mesh& _mesh)
{
	meshes.push_back(_mesh);
}

void Object::Draw()
{
	// for every mesh in object
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw();
	}
}

void Object::Delete()
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].Delete();
	}
}
