#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

out vec2 texCoord;
out vec3 FragNormal;
out vec3 FragPos;

void main() {
    // Преобразование позиции
    gl_Position = cameraMatrix * modelMatrix * vec4(aPos, 1.0);
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0)); // Позиция вершины в мировых координатах

    // Вычисление матрицы нормалей
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

    // Преобразование нормали
    FragNormal = normalize(normalMatrix * aNormal);

    // Передача текстурных координат
    texCoord = aTexCoord;
}
