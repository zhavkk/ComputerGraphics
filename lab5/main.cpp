#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <limits>
#include <random>
#include <algorithm>

using namespace std;

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
    Vec3 operator/(float s) const { return Vec3(x / s, y / s, z / s); }

    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

    Vec3 normalize() const {
        float len = length();
        if (len == 0) return Vec3(0, 0, 0); 
        return Vec3(x / len, y / len, z / len);
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

struct Sphere {
    Vec3 center;  
    float radius; 
    Vec3 color;   

    Sphere(const Vec3& center, float radius, const Vec3& color) : center(center), radius(radius), color(color) {}

    bool intersect(const Vec3& origin, const Vec3& direction, float& t) const {
        Vec3 oc = origin - center; 
        float a = direction.dot(direction); 
        float b = 2.0f * oc.dot(direction); 
        float c = oc.dot(oc) - radius * radius; 
        float discriminant = b * b - 4 * a * c; 
        if (discriminant < 0) return false; 
        float sqrtDisc = std::sqrt(discriminant); 
        float t0 = (-b - sqrtDisc) / (2.0f * a); 
        float t1 = (-b + sqrtDisc) / (2.0f * a); 

        if (t0 > 1e-4f) {
            t = t0;
            return true;
        }
        if (t1 > 1e-4f) {
            t = t1;
            return true;
        }
        return false;
    }
};

struct Plane {
    Vec3 point; 
    Vec3 normal;
    Vec3 color; 

    Plane(const Vec3& point, const Vec3& normal, const Vec3& color) : point(point), normal(normal.normalize()), color(color) {}

    bool intersect(const Vec3& origin, const Vec3& direction, float& t) const {
        float denom = normal.dot(direction); 
        if (std::abs(denom) < 1e-6) return false; 
        t = (point - origin).dot(normal) / denom; 
        return t > 1e-4f; 
    }
};

float randomFloat() {
    static std::mt19937 generator(std::random_device{}()); 
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f); 
    return distribution(generator);
}

Vec3 traceRay(const Vec3& origin, const Vec3& direction, const std::vector<Sphere>& spheres, const Plane& plane, const Vec3& lightPos) {
    float tClosest = std::numeric_limits<float>::max(); 
    const Sphere* hitSphere = nullptr;
    Vec3 hitColor; 
    Vec3 hitPoint; 
    Vec3 hitNormal; 

    for (const Sphere& sphere : spheres) {
        float tSphere;
        if (sphere.intersect(origin, direction, tSphere) && tSphere < tClosest) {
            tClosest = tSphere;
            hitSphere = &sphere;
            hitPoint = origin + direction * tSphere;
            hitNormal = (hitPoint - sphere.center).normalize();
            hitColor = sphere.color;
        }
    }

    if (tClosest == std::numeric_limits<float>::max()) {
        float tPlane;
        if (plane.intersect(origin, direction, tPlane)) {
            tClosest = tPlane;
            hitPoint = origin + direction * tPlane;
            hitNormal = plane.normal;
            hitColor = plane.color;
        }
    }

    if (tClosest == std::numeric_limits<float>::max()) {
        return Vec3(0, 0, 0);
    }

    Vec3 lightDir = (lightPos - hitPoint).normalize(); 

    bool inShadow = false;
    Vec3 shadowOrigin = hitPoint + hitNormal * 1e-4f; 
    Vec3 shadowDir = lightDir;
    for (const Sphere& sphere : spheres) {
        float tShadow;
        if (sphere.intersect(shadowOrigin, shadowDir, tShadow)) {
            inShadow = true; 
            break;
        }
    }
    if (!inShadow) {
        float tShadowPlane;
        if (plane.intersect(shadowOrigin, shadowDir, tShadowPlane)) {
            inShadow = true;
        }
    }

    float diffuse = 0.0f;
    if (!inShadow) {
        diffuse = std::max(hitNormal.dot(lightDir), 0.0f); 
    }

    return hitColor * diffuse;
}

Vec3 getRayDirection(int x, int y, int width, int height, float aspectRatio) {
    float u = (2.0f * (x + 0.5f) / width - 1.0f) * aspectRatio; 
    float v = 1.0f - 2.0f * (y + 0.5f) / height; 
    return Vec3(u, v, -1).normalize(); 
}

Vec3 applyDepthOfField(const Vec3& origin, const Vec3& direction, const Vec3& cameraPos, const float focusDistance,
                        const int numSamples, const std::vector<Sphere>& spheres, const Plane& plane, const Vec3& lightPos) {
    Vec3 color(0, 0, 0); 

    Vec3 focusPoint = cameraPos + direction * focusDistance;

    for (int i = 0; i < numSamples; i++) {
        float apertureSize = 0.3f; 
        float randX = (randomFloat() - 0.5f) * apertureSize;
        float randY = (randomFloat() - 0.5f) * apertureSize;

        Vec3 offsetOrigin = cameraPos + Vec3(randX, randY, 0);

        Vec3 rayDir = (focusPoint - offsetOrigin).normalize();

        Vec3 hitColor = traceRay(offsetOrigin, rayDir, spheres, plane, lightPos);

        color = color + hitColor;
    }

    return color / static_cast<float>(numSamples);
}

int main() {
    const int width = 800;
    const int height = 600;
    const int numSamples = 200; 
    const float aspectRatio = static_cast<float>(width) / height;

    Vec3 cameraPos(0, 1, 5);
    Vec3 cameraDir = Vec3(0, -0.2, -1).normalize(); 

    Sphere sphere1(Vec3(0, 1, 2.5), 1.0f, Vec3(1, 0, 0));  // Красная сфера (в фокусе)
    Sphere sphere2(Vec3(2, 1, 0), 1.0f, Vec3(0, 1, 0));    // Зеленая сфера (сзади)
    Sphere sphere3(Vec3(-2, 1, 0), 1.0f, Vec3(0, 0, 1));   // Синяя сфера (сзади)

    std::vector<Sphere> spheres = {sphere1, sphere2, sphere3};

    Plane plane(Vec3(0, 0, 0), Vec3(0, 1, 0), Vec3(0.5f, 0.5f, 0.5f));

    Vec3 lightPos(10, 10, 10);

    float focusDistance = (sphere1.center - cameraPos).length();

    std::vector<Vec3> image(width * height, Vec3());

    for (int y = 0; y < height; y++) {
        if (y % 50 == 0) { 
            std::cout << "Rendering line " << y << " of " << height << std::endl;
        }
        for (int x = 0; x < width; x++) {
            Vec3 rayDir = getRayDirection(x, y, width, height, aspectRatio);

            Vec3 pixelColor = applyDepthOfField(cameraPos, rayDir, cameraPos, focusDistance, numSamples, spheres, plane, lightPos);

            image[y * width + x] = pixelColor;
        }
    }

    std::ofstream outFile("image1.ppm");
    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return 1;
    }

    outFile << "P3\n" << width << " " << height << "\n255\n";

    for (const Vec3& pixel : image) {
        int r = static_cast<int>(std::clamp(pixel.x, 0.0f, 1.0f) * 255);
        int g = static_cast<int>(std::clamp(pixel.y, 0.0f, 1.0f) * 255);
        int b = static_cast<int>(std::clamp(pixel.z, 0.0f, 1.0f) * 255);
        outFile << r << " " << g << " " << b << " ";
    }

    outFile.close();
    std::cout << "Image saved as image1.ppm" << std::endl;

    return 0;
}
