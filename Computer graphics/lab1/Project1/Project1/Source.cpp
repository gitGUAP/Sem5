#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double PI_ = 3.141592653589793238463;
GLuint theTorus;

void torus(int numc, int numt) {
  int i, j, k;
  double s, t, x, y, z, twopi;

  twopi = 2 * PI_;
  for (i = 0; i < numc; i++) {
    glBegin(GL_LINE_STRIP);
    for (j = 0; j <= numt; j++) {
      for (k = 1; k >= 0; k--) {
        s = (i + k) % numc + 0.5;
        t = j % numt;

        x = (1 + 0.1 * cos(s * twopi / numc)) * cos(t * twopi / numt);
        y = (1 + 0.1 * cos(s * twopi / numc)) * sin(t * twopi / numt);
        z = 0.1 * sin(s * twopi / numc);
        glVertex3f(x, y, z);
      }
    }
    glEnd();
  }
}

static void init(void) {
  theTorus = glGenLists(1);
  glNewList(theTorus, GL_COMPILE);
  torus(30, 40);
  glEndList();

  glShadeModel(GL_SMOOTH);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glRotatef(30.0, 1.0, 1.0, 0.0);
  glCallList(theTorus);
  glFlush();
}

int main(int argc, char **argv) {
  glutInitWindowSize(500, 500);
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Lab1");
  init();

  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
