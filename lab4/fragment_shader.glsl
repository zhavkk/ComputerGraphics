#version 330 core

in vec3 FragPos;       // Позиция фрагмента в мировых координатах
in vec3 Normal;        // Нормаль фрагмента
in vec2 TexCoord;      // Текстурные координаты

uniform vec3 viewPos;         // Позиция камеры
uniform vec3 dirLightDirection; // Направление направленного света
uniform vec3 pointLightPosition; // Позиция точечного света

uniform sampler2D ourTexture;  // Текстура

out vec4 FragColor;

// Функция для расчета направленного света
vec3 CalcDirLight(vec3 normal, vec3 lightDir) {
    float diff = max(dot(normal, -lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0); // Диффузное освещение

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * vec3(1.0, 1.0, 1.0); // Спекулярное освещение

    return diffuse + specular;
}

// Функция для расчета точечного света
vec3 CalcPointLight(vec3 normal, vec3 lightPos) {
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * vec3(1.0, 1.0, 1.0);

    return diffuse + specular;
}

void main() {
    vec3 normal = normalize(Normal);

    // Освещение от направленного света
    vec3 dirLight = CalcDirLight(normal, dirLightDirection);

    // Освещение от точечного света
    vec3 pointLight = CalcPointLight(normal, pointLightPosition);

    // Итоговое освещение
    vec3 lighting = dirLight + pointLight;

    // Применяем текстуру
    vec3 textureColor = texture(ourTexture, TexCoord).rgb;

    FragColor = vec4(lighting * textureColor, 1.0);
}
