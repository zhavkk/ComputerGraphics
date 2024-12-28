#version 330 core

in vec2 texCoord;
in vec3 FragNormal;
in vec3 FragTangent;
in vec3 FragBitangent;
in vec3 FragPos;

uniform vec3 cameraPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform bool is_glowing;

uniform int dl_size;
uniform int pl_size;

uniform vec3 light_dirs[100];
uniform vec3 light_points[100];
uniform ivec3 dl_colors[100];
uniform ivec3 pl_colors[100];

out vec4 FragColor;

vec3 phongLighting(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 materialColor,
                   vec3 lightColor, float shininess) {
    // Нормализация входных векторов
    normal = normalize(normal);
    lightDir = normalize(lightDir);
    viewDir = normalize(viewDir);

    // Расчёт диффузной составляющей (Diffuse)
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Расчёт зеркальной составляющей (Specular)
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * lightColor;

    // Расчёт итогового цвета
    vec3 ambient = 0.3 * materialColor; // Постоянная фоновая составляющая
    vec3 result = ambient + diffuse * materialColor + specular;

    return result;
}

void main() {
    FragColor = texture(texture_diffuse1, texCoord);
    // FragColor = texture(texture_normal1, texCoord);
    // FragColor = vec4(1);

    if (!is_glowing) {
        mat3 TBN = mat3(FragTangent, FragBitangent, FragNormal);
        vec3 normal = vec3(texture(texture_normal1, texCoord) * 2 - 1);
        if (normal.z > 0) {
            normal.z = -normal.z;
        }
        normal = TBN * normal;
        // vec3 normal = TBN * vec3(texture(texture_diffuse1, texCoord) * 2 - 1);

        // vec3 normal = TBN * vec3(0, 0, 1);
        // vec3 normal = FragNormal;

        vec3 sumColors = vec3(0);

        for (int i = 0; i < dl_size; i++) {
            sumColors +=
                phongLighting(normal, light_dirs[i], vec3(cameraPos - FragPos),
                              vec3(FragColor), vec3(dl_colors[i]) / 255, 32);
        }
        for (int i = 0; i < pl_size; i++) {
            sumColors +=
                phongLighting(normal, vec3(light_points[i] - FragPos),
                              vec3(cameraPos - FragPos), vec3(FragColor),
                              vec3(pl_colors[i]) / 255, 32);
        }

        FragColor = vec4(sumColors, 1);
    }
}