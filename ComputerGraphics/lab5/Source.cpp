#include "BmpLoader.h"
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

GLuint theCube;

unsigned int ID;
bool FogAble = false;
float fog_colour[] = {0.5f, 0.5f, 0.5f, 0.0f};
float fog_density = 0.1f;
GLenum fog_mode = GL_EXP;
float far_distance = 10.0f;
float near_distance = 0.05f;

struct Point {
  float x;
  float y;
  float z;
};

Point Points[4][4] = {{{10, 0, 10}, {5, 0, 10}, {-5, 0, 10}, {-10, 0, 10}},
                      {{10, 0, 5}, {5, 6, 5}, {-5, 6, 5}, {-10, 0, 5}},
                      {{10, 0, -5}, {5, 6, -5}, {-5, 6, -5}, {-10, 0, -5}},
                      {{10, 0, -10}, {5, 0, -10}, {-5, 0, -10}, {-10, 0, -10}}};

unsigned int LOD = 83;

Point CalculateU(float t, int row) {
  Point p;
  float it = 1.0f - t;
  float b0 = t * t * t;
  float b1 = 3 * t * t * it;
  float b2 = 3 * t * it * it;
  float b3 = it * it * it;

  p.x = b0 * Points[row][0].x + b1 * Points[row][1].x + b2 * Points[row][2].x +
        b3 * Points[row][3].x;

  p.y = b0 * Points[row][0].y + b1 * Points[row][1].y + b2 * Points[row][2].y +
        b3 * Points[row][3].y;

  p.z = b0 * Points[row][0].z + b1 * Points[row][1].z + b2 * Points[row][2].z +
        b3 * Points[row][3].z;

  return p;
}

Point CalculateV(float t, Point *pnts) {
  Point p;
  float it = 1.0f - t;
  float b0 = t * t * t;
  float b1 = 3 * t * t * it;
  float b2 = 3 * t * it * it;
  float b3 = it * it * it;

  p.x = b0 * pnts[0].x + b1 * pnts[1].x + b2 * pnts[2].x + b3 * pnts[3].x;

  p.y = b0 * pnts[0].y + b1 * pnts[1].y + b2 * pnts[2].y + b3 * pnts[3].y;

  p.z = b0 * pnts[0].z + b1 * pnts[1].z + b2 * pnts[2].z + b3 * pnts[3].z;

  return p;
}

Point Calculate(float u, float v) {

  Point temp[4];

  temp[0] = CalculateU(u, 0);
  temp[1] = CalculateU(u, 1);
  temp[2] = CalculateU(u, 2);
  temp[3] = CalculateU(u, 3);

  return CalculateV(v, temp);
}

void OnReshape(int w, int h) {
  if (h == 0)
    h = 1;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float)w / h, 0.1, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void drawCubes() {
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -10.0);
  glRotatef(120, 1.0, 2.0, 0.0);
  glScalef(0.9, 0.9, 0.9);
  for (int i = 0; i < 6; i++) {
    glPushMatrix();
    if (i == 1) {
      glTranslatef(1.0, 0.0, 0.0);
      glRotatef(90, 0.0, 1.0, 0.0);
      glTranslatef(1.0, 0.0, 0.0);
    } else if (i == 2) {
      glTranslatef(0.0, 0.0, -2.0);
      glRotatef(180.0, 0.0, 1.0, 0.0);
    } else if (i == 3) {
      glTranslatef(-1.0, 0.0, 0.0);
      glRotatef(-90, 0.0, 1.0, 0.0);
      glTranslatef(-1.0, 0.0, 0.0);
    } else if (i == 4) {
      glTranslatef(0.0, 1.0, 0.0);
      glRotatef(-90, 1.0, 0.0, 0.0);
      glTranslatef(0.0, 1.0, 0.0);
    } else if (i == 5) {
      glTranslatef(0.0, -1.0, 0.0);
      glRotatef(90, 1.0, 0.0, 0.0);
      glTranslatef(0.0, -1.0, 0.0);
    }
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glEnd();

    glPopMatrix();
  }
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();
  glTranslatef(7, 2.0, -20.0);
  glRotatef(120, 1.0, 2.0, 0.0);
  glScalef(0.5, 0.5, 0.5);
  for (int i = 0; i < 6; i++) {
    glPushMatrix();
    if (i == 1) {
      glTranslatef(1.0, 0.0, 0.0);
      glRotatef(90, 0.0, 1.0, 0.0);
      glTranslatef(1.0, 0.0, 0.0);
    } else if (i == 2) {
      glTranslatef(0.0, 0.0, -2.0);
      glRotatef(180.0, 0.0, 1.0, 0.0);
    } else if (i == 3) {
      glTranslatef(-1.0, 0.0, 0.0);
      glRotatef(-90, 0.0, 1.0, 0.0);
      glTranslatef(-1.0, 0.0, 0.0);
    } else if (i == 4) {
      glTranslatef(0.0, 1.0, 0.0);
      glRotatef(-90, 1.0, 0.0, 0.0);
      glTranslatef(0.0, 1.0, 0.0);
    } else if (i == 5) {
      glTranslatef(0.0, -1.0, 0.0);
      glRotatef(90, 1.0, 0.0, 0.0);
      glTranslatef(0.0, -1.0, 0.0);
    }
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glEnd();

    glPopMatrix();
  }
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void display() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glFogi(GL_FOG_MODE, fog_mode);
  if (FogAble) {
    glEnable(GL_FOG);
  } else {
    glDisable(GL_FOG);
  }

  glLoadIdentity();

  gluLookAt(4, 30, 20, 0, 0, 0, 0, 1, 0);

  glPushMatrix();

  glColor3f(1, 0, 1);
  glPushMatrix();
  glBegin(GL_LINES);

  for (int i = 0; i != LOD; ++i) {

    float u = (float)i / (LOD - 1);

    for (int j = 0; j != LOD; ++j) {

      float v = (float)j / (LOD - 1);

      Point p = Calculate(u, v);
      Point q =
          Calculate((float)(i + 1) / (LOD - 1), (float)(j + 1) / (LOD - 1));

      glVertex3f(p.x, p.y, p.z);
      glVertex3f(q.x, q.y, q.z);
    }
  }

  glEnd();
  glPopMatrix();

  glCallList(theCube);

  glPopMatrix();

  glutSwapBuffers();
}

void Init() {

  theCube = glGenLists(1);
  glNewList(theCube, GL_COMPILE);
  drawCubes();
  glEndList();

  glFogf(GL_FOG_START, near_distance);
  glFogf(GL_FOG_END, far_distance);
  glFogfv(GL_FOG_COLOR, fog_colour);
  glFogf(GL_FOG_DENSITY, fog_density);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void LoadTexture(const char *filename) {
  BmpLoader bl(filename);
  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB,
                    GL_UNSIGNED_BYTE, bl.textureData);
}

void Keyboard(unsigned char key, int, int) {
  if (key == 'f') {
    FogAble = !FogAble;
  } else if (key == '1') {
    fog_mode = GL_LINEAR;
  } else if (key == '2') {
    fog_mode = GL_EXP;
  } else if (key == '3') {
    fog_mode = GL_EXP2;
  }
  std::cout << FogAble << std::endl;
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Lab_5");
  LoadTexture("image.bmp");
  glutDisplayFunc(display);
  glutReshapeFunc(OnReshape);
  glutKeyboardFunc(Keyboard);
  Init();
  glutMainLoop();
  return 0;
}
