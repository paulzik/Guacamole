#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aUV;
layout(location = 4) in ivec4 aBoneIDs;
layout(location = 5) in vec4 aBoneWeights;

out vec3 FragPos;
out vec3 Normal;
out vec3 vertexColor;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 bones[100];

void main()
{
    // Apply skinning
    mat4 skinMatrix = 
        aBoneWeights.x * bones[aBoneIDs.x] +
        aBoneWeights.y * bones[aBoneIDs.y] +
        aBoneWeights.z * bones[aBoneIDs.z] +
        aBoneWeights.w * bones[aBoneIDs.w];

    vec4 skinnedPos = skinMatrix * vec4(aPos, 1.0);
    vec3 skinnedNormal = mat3(transpose(inverse(skinMatrix))) * aNormal;

    FragPos = vec3(model * skinnedPos);
    Normal = mat3(transpose(inverse(model))) * skinnedNormal;
    vertexColor = aColor;
    TexCoords = aUV;

    gl_Position = projection * view * model * skinnedPos;
}