#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 vertexColor;
in vec2 TexCoords;

uniform vec3 viewPos;

#define MAX_LIGHTS 16

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

uniform int lightCount;
uniform Light lights[MAX_LIGHTS];

uniform sampler2D albedoTexture;
uniform bool useTexture;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < lightCount; ++i) {
        // --- Ambient ---
        vec3 ambient = 0.1 * lights[i].color * lights[i].intensity;

        // --- Diffuse ---
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color * lights[i].intensity;

        // --- Specular ---
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = vec3(0.3) * spec * lights[i].intensity;

        // Add to result
        result += ambient + diffuse + specular;
    }

    vec3 finalColor = vertexColor;
    if (useTexture)
        finalColor *= texture(albedoTexture, TexCoords).rgb;

    result *= finalColor;

    FragColor = vec4(result, 1.0);
}
