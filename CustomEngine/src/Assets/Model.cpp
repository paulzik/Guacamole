#include "Model.h"

void Model::OnPathAssigned()
{
    for (size_t i = 0; i < meshes.size(); ++i)
    {
        meshes[i]->path = path + "#" + std::to_string(i);
        meshes[i]->name = name + "_Mesh" + std::to_string(i);
    }
}
