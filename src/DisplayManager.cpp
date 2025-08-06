#include "DisplayManager.h"


void DisplayManager::createDisplay() {

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "VoxelCraft", nullptr, nullptr);

    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    glfwSwapInterval(2);
            
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    lastFrameTime = getCurrentTime();
}

void DisplayManager::updateDisplay() {
    processInput(window);

    glfwSwapBuffers(window);
    glfwPollEvents();

    double currentFrameTime = getCurrentTime();
    delta = (currentFrameTime - lastFrameTime)/1000;
    lastFrameTime = currentFrameTime;

}

bool DisplayManager::shouldClose() {
    return glfwWindowShouldClose(window);
}

double DisplayManager::getFrameTime() {
    //std::cout<<delta<<std::endl;
    return delta;
}

void DisplayManager::closeDisplay() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

double DisplayManager::getCurrentTime() {
    return glfwGetTime()*1000;
}

void DisplayManager::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

void DisplayManager::processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLFWwindow* DisplayManager::getWindow() const {
    return window;
}

const int DisplayManager::getWidth(){
    return WINDOW_WIDTH;
}
const int DisplayManager::getHeight(){
    return WINDOW_HEIGHT;
}