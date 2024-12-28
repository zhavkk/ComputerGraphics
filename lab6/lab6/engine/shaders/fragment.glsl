#version 330 core

in vec2 texCoord;
in vec3 FragNormal;
in vec3 FragPos;

uniform vec3 cameraPos;
uniform sampler2D myTexture;
uniform bool is_glowing;

uniform int dl_size;
uniform int pl_size;

uniform vec3 light_dirs[100];
uniform vec3 light_points[100];
uniform ivec3 dl_colors[100];
uniform ivec3 pl_colors[100];

// Параметры затухания
uniform float constantAtt = 1.0;
uniform float linearAtt = 0.09;
uniform float quadraticAtt = 0.032;

out vec4 FragColor;

vec3 phongLighting(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 materialColor,
                   vec3 lightColor, float shininess, float attenuation) {
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

    // Расчёт итогового цвета с учётом затухания
    vec3 ambient = 0.3 * materialColor; // Постоянная фоновая составляющая
    vec3 result = (ambient + diffuse * materialColor + specular) * attenuation;

    return result;
}

void main() {
    FragColor = texture(myTexture, texCoord);

    if (!is_glowing) {
        vec3 sumColors = vec3(0);

        // Освещение от направленных источников света
        for (int i = 0; i < dl_size; i++) {
            sumColors += phongLighting(
                FragNormal, -light_dirs[i], vec3(cameraPos - FragPos),
                vec3(FragColor), vec3(dl_colors[i]) / 255, 32,
                1.0); // Для направленных источников затухание не учитывается
        }

        // Освещение от точечных источников света с затуханием
        for (int i = 0; i < pl_size; i++) {
            vec3 lightDir = light_points[i] - FragPos;
            float distance = length(lightDir);
            float attenuation = 1.0 / (constantAtt + linearAtt * distance +
                                       quadraticAtt * (distance * distance));
            sumColors += phongLighting(
                FragNormal, lightDir, vec3(cameraPos - FragPos),
                vec3(FragColor), vec3(pl_colors[i]) / 255, 32, attenuation);
        }

        FragColor = vec4(sumColors, 1);
    }
}
