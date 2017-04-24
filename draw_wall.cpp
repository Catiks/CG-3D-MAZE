#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include "./wall.h"
#include "./Camera.h"

GLfloat lastX, lastY;
GLfloat deltaTime;
bool firstMouseMove = true;
GLfloat speed = 1;

void processKeyBoard(GLfloat dis);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLfloat presstime, globletime;

void drawCoordinate();
Camera cam(1.0f, 1.0f, 1.f,
	   0.0f, 1.0f, 0.0f,
	   0.0f, 0.0f, 0.0f);
int main() {

  GLFWwindow *window;
  glfwInit();
  window = glfwCreateWindow(500, 500, "View", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  wall wa[6];
  GLfloat camPosX;
  GLfloat camPosZ;
  GLfloat lastTime =(GLfloat)glfwGetTime();
  // 注册窗口键盘事件回调函数
  glfwSetKeyCallback(window, key_callback);
  // 注册鼠标事件回调函数
  glfwSetCursorPosCallback(window, mouse_move_callback);
  // 捕获鼠标
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      wa[3*i+j] = wall(0.0, i*0.1, j*0.1,
		   0.1,   0.1,  0.1);
    }
  }
  while(!glfwWindowShouldClose(window)) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat currentTime = (GLfloat)glfwGetTime();
    globletime = currentTime;
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    
    cam.show();
    processKeyBoard(deltaTime/2*speed);

    for (int i = 0; i < 6; i++)
      wa[i].draw();
    drawCoordinate();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  return 0;
}

void drawCoordinate() {
  glBegin(GL_LINES);
  // x-ra
  glColor3f(1, 0, 0); //red
  glVertex3f(5, 0, 0);
  glColor3f(0.1, 0, 0);
  glVertex3f(-5, 0, 0);
  // y-ra
  glColor3f(0, 1, 0); //green
  glVertex3f(0, 5, 0);
  glColor3f(0, 0.1, 0);
  glVertex3f(0, -5, 0);
  // z-ra
  glColor3f( 0, 0, 1); // bule
  glVertex3f(0, 0, 5);
  glColor3f(0, 0, 0.1);
  glVertex3f(0, 0, -5);
  glEnd();
  glFlush();
}

bool once = 0;

bool keyPressedStatus[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // 设置按键
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    glfwSetWindowShouldClose(window, GL_TRUE);

  if (key >=0 && key < 1024) {
    if (action == GLFW_PRESS) {
      keyPressedStatus[key] = true;
    }
    else if (action == GLFW_RELEASE) {
      keyPressedStatus[key] = false;
    }
  }
}

void processKeyBoard(GLfloat dis) {
  if (keyPressedStatus[GLFW_KEY_W])
    cam.doMove(FORWARD, dis);
  if (keyPressedStatus[GLFW_KEY_S])
    cam.doMove(BACKWARD, dis);
  if (keyPressedStatus[GLFW_KEY_A])
    cam.doMove(LEFT, dis);
  if (keyPressedStatus[GLFW_KEY_D])
    cam.doMove(RIGHT, dis);
}
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
  if (firstMouseMove) {
    lastX = xpos;
    lastY = ypos;
    firstMouseMove = false;
  }
  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset = ypos - lastY;
  lastX = xpos;
  lastY = ypos;
  cam.rotate(yoffset/100.0, xoffset/100.0);
}
