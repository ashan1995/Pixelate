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

    
    Camera(glm::vec3 pos , float width, float height)
    {
        cameraPos = pos;

        cameraFront=glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp=glm::vec3(0.0f, 1.0f, 0.0f);
        view=glm::mat4(1.0f);
        projection=glm::mat4(1.0f),
        aspectRatio=width / height;
        fov=45.0f;
        updateCamera();
    }

    void move(GLFWwindow* window,float deltaTime)
    {
        const float cameraSpeed = 2.5f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        cameraPos.y = 0.0f;

        updateCamera();
    }

    void lookAround(float horizontal, float vertical)
    {
        const float sensitivity = 10.0f;

        hoz += glm::radians(horizontal * sensitivity);
        vert += glm::radians(vertical * sensitivity);

        if (vert > 89.0f)
            vert = 89.0f;
        if (vert < -89.0f)
            vert = -89.0f;

        // Calculate new cameraFront direction
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(vert)) * sin(glm::radians(hoz));
        newFront.y = sin(glm::radians(vert));
        newFront.z = -cos(glm::radians(vert)) * cos(glm::radians(hoz));

        // Ensure cameraFront is normalized to avoid artifacts
        cameraFront = glm::normalize(newFront);

        updateCamera();
    }

private:
    void updateCamera()
    {
        
        projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }
};

#endif /* Camera_h */
