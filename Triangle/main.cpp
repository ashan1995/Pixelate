//
//  main.cpp
//  Triangle
//
//  Created by Ashan Samarasinghe on 18/5/2024.
//

#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "Camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float horizontal = 0.0f;
float vertical = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
        static double lastX = xpos;
        static double lastY = ypos;
        
        // Calculate offset from last position
        double xoffset = xpos - lastX;
        double yoffset = lastY - ypos;
    
        // Update last position
        lastX = xpos;
        lastY = ypos;
        
        // Update global variables for horizontal and vertical movement
        horizontal = static_cast<float>(xoffset);
        vertical = static_cast<float>(yoffset);
    
    
}


int main()
{
    //window creation
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    
   
    //loading texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load("wall.jpeg", &width, &height, &nrChannels, 0);
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    stbi_image_free(data);
    
    
    Shader ourShader("shader.vs", "textureshader.fs");
    Shader lightingShader("shader.vs", "lightshader.fs");
    
    glm::vec3 cameraPos(0.0f, 0.0f, 3.0f);
    Camera camera(cameraPos,(float)SCR_WIDTH, (float)SCR_HEIGHT);
  
      // Set up vertex data and buffers and configure vertex attributes
      unsigned int VBO, VAO;
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);

      glBindVertexArray(VAO);

    

      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      // Position attribute
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    
    ourShader.use();
    ourShader.setInt("ourTexture", 0);
//    glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture"), 0);
    
    
    glEnable(GL_DEPTH_TEST);
    
   
    
//    float forward = 0.0f;
//    float left = 0.0f;
   
      // Render loop
      while (!glfwWindowShouldClose(window))
      {
          
          // Input
          processInput(window);

          // Rendering commands
          glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
          
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_2D, texture);

          // Draw our first triangle
          ourShader.use();
          
          ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
          ourShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
        
          glm::mat4 view            = glm::mat4(1.0f);
          glm::mat4 projection      = glm::mat4(1.0f);
          glm::mat4 model           = glm::mat4(1.0f);
          
          glm::mat4 model2           = glm::mat4(1.0f);
        
          camera.move(window);
          camera.lookAround(window,horizontal,vertical);
        
          projection = camera.projection;
          view = camera.view;
       
          unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");

          glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        
          ourShader.setMat4("projection", projection);
          
          model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
          ourShader.setMat4("model", model);
          glBindVertexArray(VAO);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          
          
          lightingShader.use();
          
          unsigned int viewLoc2  = glGetUniformLocation(lightingShader.ID, "view");
          glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, &view[0][0]);
          lightingShader.setMat4("projection", projection);
    
          model2 = glm::translate(model2, glm::vec3(3.0f, 0.0f, 2.0f));
          lightingShader.setMat4("model", model2);
          glBindVertexArray(VAO);
          glDrawArrays(GL_TRIANGLES, 0, 36);

          // Check and call events and swap the buffers
          glfwSwapBuffers(window);
          glfwPollEvents();
      }

      // Clean up resources
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
     
      // Terminate GLFW, clearing any resources allocated by GLFW
      glfwTerminate();
      return 0;
  }
 


