#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;

out vec2 texCoord;
out vec3 FragNormal;
out vec3 FragTangent;
out vec3 FragBitangent;
out vec3 FragPos;

void main() {
    gl_Position = cameraMatrix * modelMatrix * vec4(aPos, 1.0);
    FragPos = vec3(modelMatrix * vec4(aPos, 1)); // Позиция вершины в мировых координатах
    FragNormal = vec3(modelMatrix * vec4(aNormal, 0)); // Корректируем нормаль
    FragTangent = vec3(modelMatrix * vec4(aTangent, 0));
    FragBitangent = vec3(modelMatrix * vec4(aBitangent, 0));
    texCoord = aTexCoord;
}
