#include <GL/glut.h>
#include <stdlib.h>

//Вращение объектов
GLfloat x_angle = 0;
GLfloat y_angle = 0;

//Вращение источинков света 
GLfloat y1_angle = 0;
GLfloat x1_angle = 0;
GLfloat y2_angle = 0;
GLfloat x2_angle = 0;
GLfloat y3_angle = 0;
GLfloat x3_angle = 0;

int active_light = 0;
GLfloat h = 4;
float shininess = { 80.0 };
float mat_ambient[] = { 0.2, 0.2, 0.2, 0.5 };
float mat_dif[] = { 0.5, 0.5, 0.5 };
float mat_spec[] = { 0.8, 0.8, 0.8 };


void light(void)
{
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0 };

	GLfloat light_diffuse1[] = { 1.0, 1.0, 1.0 };
	GLfloat light_specular1[] = { 1.0, 0.0, 1.0 };

	GLfloat light_diffuse2[] = { 1.0, 1.0, 1.0 };
	GLfloat light_specular2[] = { 0.0, 1.0, 1.0 };

	GLfloat light_diffuse3[] = { 1.0, 1.0, 0.0 };
	GLfloat light_specular3[] = { 1.0, 1.0, 0.0 };

	GLfloat light_position1[] = { 100.0, 0.0, 0.0, 0.0 };
	GLfloat light_position2[] = { -100.0, 0.0, 0.0, 0.0 };
	GLfloat light_position3[] = { 100.0, 100.0, 100.0, 0.0 };


	glPushMatrix();
	glRotatef(x1_angle, 1.0, 0.0, 0.0);
	glRotatef(y1_angle, 0.0, 1.0, 0.0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);

	glPopMatrix();

	glPushMatrix();
	glRotatef(x2_angle, 1.0, 0.0, 0.0);
	glRotatef(y2_angle, 0.0, 1.0, 0.0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glPopMatrix();


	glPushMatrix();
	glRotatef(x3_angle, 1.0, 0.0, 0.0);
	glRotatef(y3_angle, 0.0, 1.0, 0.0);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular3);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);



}

void myCubes() {
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glPushMatrix();
	glutSolidCube(1);
	glTranslatef(-0.5,-0.5,-0.5);
	glutSolidCube(1);


	glPopMatrix();

}

void display(void)
{
	light();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	glRotatef(x_angle, 1.0, 0.0, 0.0);
	glRotatef(y_angle, 0.0, 1.0, 0.0);
	glRotatef(45.0, 1.0, 1.0, 1.0);
	myCubes();

	glPopMatrix();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / h, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 9.0f,0.0f, 0.0f, 0.0f,0.0f, 100.0f, 0.0f);
}

void keyboard(unsigned char key, int x, int y)
{
	if (active_light == 0) {
		switch (key)
		{
		case 'd': y1_angle += h; break;
		case 'a': y1_angle -= h; break;
		case 'w': x1_angle -= h; break;
		case 's': x1_angle += h; break;
		}
	}
	else if (active_light == 1) {
		switch (key)
		{
		case 'd': y2_angle += h; break;
		case 'a': y2_angle -= h; break;
		case 'w': x2_angle -= h; break;
		case 's': x2_angle += h; break;
		}
	}
	else if (active_light == 2) {
		switch (key)
		{
		case 'd': y3_angle += h; break;
		case 'a': y3_angle -= h; break;
		case 'w': x3_angle -= h; break;
		case 's': x3_angle += h; break;
		}
	}
	
	switch (key) {
	case '1':
		active_light = 0; break;
	case '2':
		active_light = 1; break;
	case '3':
		active_light = 2; break;
	}

	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {

	
	
	if (key == GLUT_KEY_RIGHT)
		y_angle += h;

	else if (key == GLUT_KEY_LEFT)
		y_angle -= h;

	else if (key == GLUT_KEY_UP)
		x_angle -= h;

	else if (key == GLUT_KEY_DOWN)
		x_angle += h;

	glutPostRedisplay();

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("LR4");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}