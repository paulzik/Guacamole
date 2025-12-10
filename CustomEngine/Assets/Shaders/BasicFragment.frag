#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 vertexColor;
in vec2 TexCoords;

uniform vec3 viewPos;

#define MAX_LIGHTS 16

struct Light {
    int type;      // 0 = directional, 1 = point
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;

    float radius; //Point light attenuation
};

uniform int lightCount;
uniform Light lights[MAX_LIGHTS];

uniform sampler2D albedoTexture;
uniform bool useTexture;

uniform float metallic;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 finalColor = vertexColor;
    if (useTexture)
        finalColor *= texture(albedoTexture, TexCoords).rgb;

    vec3 result = vec3(0.0);

    for (int i = 0; i < lightCount; ++i) {
    
        vec3 ambient = 0.1 * lights[i].color * lights[i].intensity;
    
        vec3 lightDir;
        float attenuation = 1.0;
    
        if (lights[i].type == 0) {
            // directional
            lightDir = normalize(-lights[i].direction);
        }
        else {
            // point light
            vec3 toLight = lights[i].position - FragPos;
            float dist = length(toLight);
            lightDir = normalize(toLight);
    
            // radius-based attenuation
            float x = clamp(1.0 - dist / lights[i].radius, 0.0, 1.0);
            attenuation = x * x;  // apply later to diffuse & spec
        }
    
        // Diffuse
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color * lights[i].intensity * (1.0 - metallic);
    
        // Specular
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    
        vec3 specularColor = mix(vec3(0.3), finalColor, metallic);
        vec3 specular = specularColor * spec * lights[i].intensity;
    
        // Apply attenuation for point lights only
        diffuse *= attenuation;
        specular *= attenuation;
    
        result += ambient + diffuse + specular;
    }

    FragColor = vec4(result * finalColor, 1.0);  // apply base color once
}
