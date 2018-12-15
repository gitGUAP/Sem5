
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GL/glut.h>

GLuint program;
GLint attribute_coord2d;

GLfloat triangle_vertices[] = {
    -0.8, 0.8, -0.8, -0.8, 0.8, -0.8, 0.8, 0.8,
};

void onDisplay() {

  GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  const char *vs_source =
      "#version 120\n" // OpenGL 2.1
      "attribute vec2 coord2d;                  "
      "void main(void) {                        "
      "  gl_Position = vec4(coord2d, 0.0, 1.0); "
      "}";
  glShaderSource(vs, 1, &vs_source, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
  if (0 == compile_ok) {
    fprintf(stderr, "Error in vertex shader\n");
  }

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fs_source =
      "#version 120           \n"
      "void main(void) {        "
      "gl_FragColor[0] = gl_FragCoord.x / 640.0 ;"
      "gl_FragColor[1] = gl_FragCoord.y / 480.0;"
      "gl_FragColor[3] = noise1(gl_FragCoord.x / 640.0) * 0.5 + 0.5;"

      "}";
  glShaderSource(fs, 1, &fs_source, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
  if (!compile_ok) {
    fprintf(stderr, "Error in fragment shader\n");
  }

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
  }
  const char *attribute_name = "coord2d";
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (attribute_coord2d == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
  }

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(program);
  glEnableVertexAttribArray(attribute_coord2d);

  glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0,
                        triangle_vertices);

  glDrawArrays(GL_QUADS, 0, 4);
  glDisableVertexAttribArray(attribute_coord2d);

  glutSwapBuffers();
}

void free_resources() { glDeleteProgram(program); }

GLfloat Mz[2][2] = {{1, -0.001}, {0.001, 1}};

void idle(void) {
  triangle_vertices[0] =
      triangle_vertices[0] * Mz[0][0] + triangle_vertices[1] * Mz[0][1];
  triangle_vertices[1] =
      triangle_vertices[0] * Mz[1][0] + triangle_vertices[1] * Mz[1][1];

  triangle_vertices[2] =
      triangle_vertices[2] * Mz[0][0] + triangle_vertices[3] * Mz[0][1];
  triangle_vertices[3] =
      triangle_vertices[2] * Mz[1][0] + triangle_vertices[3] * Mz[1][1];

  triangle_vertices[4] =
      triangle_vertices[4] * Mz[0][0] + triangle_vertices[5] * Mz[0][1];
  triangle_vertices[5] =
      triangle_vertices[4] * Mz[1][0] + triangle_vertices[5] * Mz[1][1];
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutCreateWindow("LR7");

  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
    return EXIT_FAILURE;
  }
  glutIdleFunc(idle);

  glutDisplayFunc(onDisplay);
  glutMainLoop();

  free_resources();
  return EXIT_SUCCESS;
}
