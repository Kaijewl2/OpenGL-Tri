#include "config.h"
#include <glad/glad.h>
using namespace std;

// Vertex Shader source
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n" // Position variable has attribute position 0
    "layout (location = 1) in vec3 aColor;\n" // Color variable has attribute positon 1

    "out vec3 ourColor;\n" // Output color to frag shader

    "void main()\n"
    "{\n"
        "gl_Position = vec4(aPos, 1.0);\n" // Gives vec3 to vec4 constructor
        "ourColor = aColor;\n" // Set ourColor to input color we get from vertex data
    "}\n";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"

    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n";

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {

    GLFWwindow* window;

    if(!glfwInit()) {
        cout << "GLFW couldn't load window";
        return -1;
    }

    window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.05f, 0.1f, 0.05f, 1.0f);

    // Build & compile shader program

    // Intialize Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Error handling Vertex Shader compilation
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    // Initialize Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Error handling Fragment Shader compilation
    int fragmentSuccess;
    char fragInfoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);

    if (!fragmentSuccess) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fragInfoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragInfoLog << endl;
    }

    // Create program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Link shaders to program object
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Error handling Program Object
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }
    // No longer need created vertex & fragment shaders in memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.6f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.4f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.2f, 0.1f, 1.0f    // top 
    };   
    unsigned int indices[] = { // Starting from 0
        0, 1, 3, // First triangle
    };

    // Create Buffer Objects

    // Declare Buffer Objects
    unsigned int VAOs[1], VBOs[1];
    glGenVertexArrays(1, VAOs);
    glGenBuffers(1, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while(!glfwWindowShouldClose(window)) {
        
        // Input
        processInput(window);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Activate shader
        glUseProgram(shaderProgram);
        
        // Draw triangle
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}