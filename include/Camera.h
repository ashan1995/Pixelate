#ifndef Camera_h
#define Camera_h

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    float fov;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::mat4 view;
    glm::mat4 projection;
    float aspectRatio;

    float hoz = 0.0f;
    float vert = 0.0f;

    Camera(glm::vec3 pos, float width, float height);
    void move(GLFWwindow* window, float deltaTime);
    void lookAround(float horizontal, float vertical);

private:
    void updateCamera();
};

#endif /* Camera_h */
