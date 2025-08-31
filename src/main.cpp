#include "config.h"
using namespace std;

int main() {

    GLFWwindow* window;

    if(!glfwInit()) {
        cout << "GLFW couldn't load window";
        return -1;
    }

    window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);

    while(!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();

    }

    glfwTerminate();

    return 0;
}