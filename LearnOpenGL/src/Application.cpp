#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    std::cout<< glGetString(GL_VERSION) <<std::endl;

    float positions[6] = { //create an array for vertex positions
        -0.5f,-0.5f,
         0.0f, 0.5f,
         0.5f, -0.5f,
    };

    unsigned int buffer;    //identifier
    glGenBuffers(1, &buffer);    //create buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);  //select buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); //copying the array to buffer

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2, 0); //setting up vertex attribute and layout

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

       /* glBegin(GL_TRIANGLES);

        glVertex2f(-0.5f,-0.5f);
        glVertex2f( 0.0f, 0.5f);
        glVertex2f( 0.5f, -0.5f);
        
        glEnd();*/

        glDrawArrays(GL_TRIANGLES, 0, 3);  //The draw call

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}