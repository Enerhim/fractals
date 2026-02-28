#include "Shader.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include <cmath>

int main() {
  Window window(1600, 900, "mandelbrot");
  Shader shader;
  Renderer renderer(0, 0, 1600, 900);

  float vertices[] = {
      // positions
      -1.0f, -1.0f, // bottom left
      1.0f,  -1.0f, // bottom right
      1.0f,  1.0f,  // top right
      -1.0f, 1.0f   // top left
  };

  unsigned int VAO, VBO, EBO;
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  // VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // Vertex attribute
  glVertexAttribPointer(0, // location = 0
                        2, // 2 floats per vertex (x,y)
                        GL_FLOAT, GL_FALSE,
                        2 * sizeof(float), // tightly packed
                        (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  float prevTime = 0;

  while (!window.shouldClose()) {
    window.processInput();
    renderer.clear(1.0f, 1.0f, 1.0f, 1.0f);
    shader.use();

    float time = window.getTime();
    float deltaTime = time - prevTime;

    float zoom = expf(time * 0.1f);

    shader.setFloat1f("zoom", zoom);
    shader.setFloat2f("center", -0.74364388703f, 0.13182590421f);
    shader.setInteger1("maxIter", int(50 + 100.0f * log(zoom)));
    int width = 0;
    int height = 0;
    window.getSizeByRef(width, height);
    shader.setInteger1("width", width);
    shader.setInteger1("height", height);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    window.swapBuffers();
    window.pollEvents();
    prevTime = time;
  }
  return 0;
}
