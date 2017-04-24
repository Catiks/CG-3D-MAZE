#ifndef WALL
#define WALL

class wall {
 private:
  float posx;
  float posy;
  float posz;
  float height, width, length;
 public:
  wall(float x = 0, float y = 0, float z = 0, 
       float l = 0.1, float w = 0.1, float h = 0.1);
  void draw();
};

wall::wall(float x, float y, float z,
	   float l, float w, float h) {
  posx = x;
  posy = y;
  posz = z;
  length = l;
  width = w;
  height = h;
}
void wall::draw(){
  float h = height/2;
  float w = width/2;
  float l = length/2;
  glBegin(GL_QUADS);
  glColor3f(0.5,0.5, 0.5);
  
  glVertex3f( w+posx, h+posy, l+posz);
  glVertex3f(-w+posx, h+posy, l+posz);
  glVertex3f(-w+posx,-h+posy, l+posz);
  glVertex3f( w+posx,-h+posy, l+posz);
  //1----------------------------
  glVertex3f(-w+posx,-h+posy,-l+posz);
  glVertex3f(-w+posx, h+posy,-l+posz);
  glVertex3f( w+posx, h+posy,-l+posz);
  glVertex3f( w+posx,-h+posy,-l+posz);
  //2----------------------------
  glVertex3f( w+posx, h+posy, l+posz);
  glVertex3f( w+posx, h+posy,-l+posz);
  glVertex3f(-w+posx, h+posy,-l+posz);
  glVertex3f(-w+posx, h+posy, l+posz);
  //3----------------------------
  glVertex3f(-w+posx,-h+posy,-l+posz);
  glVertex3f( w+posx,-h+posy,-l+posz);
  glVertex3f( w+posx,-h+posy, l+posz);
  glVertex3f(-w+posx,-h+posy, l+posz);
  //4----------------------------
  glVertex3f( w+posx, h+posy, l+posz);
  glVertex3f( w+posx,-h+posy, l+posz);
  glVertex3f( w+posx,-h+posy,-l+posz);
  glVertex3f( w+posx, h+posy,-l+posz);
  //5----------------------------
  glVertex3f(-w+posx,-h+posy,-l+posz);
  glVertex3f(-w+posx,-h+posy, l+posz);
  glVertex3f(-w+posx, h+posy, l+posz);
  glVertex3f(-w+posx, h+posy,-l+posz);
  //6----------------------------
  glEnd();
  glFlush();
}

#endif
