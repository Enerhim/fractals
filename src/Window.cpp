#include <glad/glad.h>
#include "Window.hpp"
#include <stdexcept>

void resize_callback(GLFWwindow *window, int width, int height);

Window::Window(int width, int height, const char *title) {
  if (!glfwInit()) {
    throw std::runtime_error("Failure: Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (m_window == NULL) {
    throw std::runtime_error("Failure: Unable to create GLFW Window");
    glfwTerminate();
  }

  glfwMakeContextCurrent(m_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failure: Unable to initialize GLAD");
    glfwTerminate();
  }

  glfwSetFramebufferSizeCallback(m_window, resize_callback);
}

Window::~Window() {
  if (m_window)
    glfwDestroyWindow(m_window);
  glfwTerminate();
}

bool Window::shouldClose() const { return glfwWindowShouldClose(m_window); }

void Window::swapBuffers() { glfwSwapBuffers(m_window); }

void Window::pollEvents() { glfwPollEvents(); }

void Window::processInput() {
  if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(m_window, true);
}

void resize_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
