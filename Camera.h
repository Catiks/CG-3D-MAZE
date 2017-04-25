#ifndef CAMERA
#define CAMERA
#include <math.h>

#define PI 3.14159265

enum MoveDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
class Camera {
 public:

  Camera(GLfloat posx, GLfloat posy, GLfloat posz,
         GLfloat upx, GLfloat upy, GLfloat upz,
	 GLfloat targetx, GLfloat targety, GLfloat targetz);

  void moveForward(GLfloat distance);
  void moveBack(GLfloat distance);
  void moveLeft(GLfloat distance);
  void moveRight(GLfloat distance);
  void rotate(GLfloat const pitch, GLfloat const yaw);
  void update();
  void doMove(MoveDirection dir, GLfloat dis);
  void show();
  //for two vertex cross
  void cross(GLfloat* ans, const GLfloat *l, const GLfloat *r);
 private:
  GLfloat front[3];
  GLfloat position[3];
  GLfloat right[3];
  GLfloat up[3];
  GLfloat world_up[3];
  GLfloat _pitch, _yaw;
};

Camera::Camera(GLfloat posx, GLfloat posy, GLfloat posz,
	       GLfloat upx, GLfloat upy, GLfloat upz,
	       GLfloat targetx, GLfloat targety, GLfloat targetz) {
  position[0] = posx;
  position[1] = posy;
  position[2] = posz;
  world_up[0] = upx;
  world_up[1] = upy;
  world_up[2] = upz;
  
  GLfloat d = sqrt(pow(targetx - posx, 2) + pow(targetz - posz, 2));
  GLfloat a = d;
  GLfloat b = 1;
  
  _yaw = acos((targetx - posx)/(a*b))*180/PI;
  if (targetx < posx)
    _yaw = -_yaw;

  if (d != 0)
    _pitch = atan((targety - posy)/d)*180/PI;
  this->update();
}
  /*initialize camera--including the key and mouse move */

void Camera::doMove(MoveDirection dir, GLfloat dis) {
  if (dir == FORWARD)
    this->moveForward(dis);
  if (dir == BACKWARD)
    this->moveBack(dis);
  if (dir == LEFT)
    this->moveLeft(dis);
  if (dir == RIGHT)
    this->moveRight(dis);
}
void Camera::moveForward(GLfloat distance) {
  for (int i = 0; i < 3; i++) {
    position[i] += distance*front[i];
  }
}
void Camera::moveBack(GLfloat distance) {
  for (int i = 0; i < 3; i++) {
    position[i] -= distance*front[i];
  }
}
void Camera::moveLeft(GLfloat distance) {
  for (int i = 0; i < 3; i++) {
    position[i] -= distance*right[i];
  }
}
void Camera::moveRight(GLfloat distance) {
  for (int i = 0; i < 3; i++) {
    position[i] += distance*right[i];
  }
}
  /* //测试是查看打印各个参数的值
     void Camera::print() {
     std::cout << "Front : ";
     for (int i = 0; i < 3; i++)
     std::cout << front[i] << ' ';
     std::cout << std::endl;

     std::cout << "up : ";
     for (int i = 0; i < 3; i++)
     std::cout << up[i] << ' ';
     std::cout << std::endl;
     std::cout << "rigit : ";
     for (int i = 0; i < 3; i++)
     std::cout << right[i] << ' ';
     std::cout << std::endl;
     std::cout << "Pitch:" << _pitch << "    yaw: " << _yaw << std::endl;
     std::cout << "*************************" << std::endl;
     }
  */
void Camera::rotate(GLfloat const pitch, GLfloat const yaw) {
  _pitch -= pitch;
  if ( _pitch > 89)
    _pitch = 89;
  if (_pitch < -89)
    _pitch = -89;
  _yaw += yaw;
  if (_yaw > 360||_yaw < -360)
    _yaw = 0;
  this->update();
}
void Camera::update() {
  front[1] = sin(_pitch * PI / 180.0);
  front[2] = sin(_yaw* PI / 180.0) * cos(_pitch* PI / 180.0);
  front[0] = cos(_yaw * PI / 180.0) * cos(_pitch* PI / 180.0);
  cross(right, front, world_up);
  cross(up, right, front);
}
void Camera::cross(GLfloat* ans,const GLfloat *l,const GLfloat *r) {
  ans[0] = l[1]*r[2] - l[2]*r[1];
  ans[1] = l[0]*r[2] - l[2]*r[0];
  ans[2] = l[0]*r[1] - l[1]*r[0];
}

void Camera::show() {
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluPerspective(45,      //视角角度
		 1,       //高度比
		 0.01f,    //透视深度:近点1.0f
		 3000.0f  //透视深度:始点0.1f远点1000.0f
		 );
  gluLookAt(position[0], position[1], position[2],
	    position[0] + front[0], position[1] + front[1], position[2] + front[2],
	    world_up[0], world_up[1], world_up[2]);
}

#endif
