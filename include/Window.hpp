#pragma once
#include <GLFW/glfw3.h>

class Window {
public:
  Window(int width, int height, const char *title);
  ~Window();

  bool shouldClose() const;
  void swapBuffers();
  void pollEvents();

  void processInput();

  GLFWwindow *native() const { return m_window; }
  void getSizeByRef(int &width, int &height) const {
    glfwGetWindowSize(m_window, &width, &height);
  }
  float getTime() const { return glfwGetTime(); }

private:
  GLFWwindow *m_window = nullptr;
};
