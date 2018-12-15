#include <GL/glut.h>
#include <stdlib.h>

double rotate_y = 0;
double rotate_x = 0;
float shininess = { 80.0 };
float mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

/* ��������� ��������� ���� */
float mat1_dif[] = { 0.2, 0.2, 0.2 };
float mat1_spec[] = { 0.8, 0.8, 0.8 };


/* ��������� ��������� ������ */
float mat2_dif[] = { 1.0, 1.0, 1.0 };
float mat2_spec[] = { 1.0, 1.0, 1.0 };


/* ��������� ��������� ���� */
float mat3_dif[] = { 0.5, 0.5, 0.5 };
float mat3_spec[] = { 0.8, 0.8, 0.8 };


/* ��������� ��������� ���� */
float mat4_dif[] = { 0.5, 0.5, 0.5 };
float mat4_spec[] = { 0.0, 0.0, 0.0 };


// �������������� ��������� ���������� � ��������� �����
void init(void)
{
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0 }; //black light

	GLfloat light_diffuse1[] = { 0.0, 0.0, 1.0 };//blue
	GLfloat light_specular1[] = { 0.0, 0.0, 1.0 };

	GLfloat light_diffuse2[] = { 0.0, 1.0, 0.0 };//green
	GLfloat light_specular2[] = { 0.0, 1.0, 0.0 };

	GLfloat light_diffuse3[] = { 1.0, 0.0, 0.0 };//red
	GLfloat light_specular3[] = { 1.0, 0.0, 0.0 };

	GLfloat light_position1[] = { 100.0, 0.0, 0.0, 0.0 };
	GLfloat light_position2[] = { -100.0, 0.0, 0.0, 0.0 };
	GLfloat light_position3[] = { 100.0, 100.0, 100.0, 0.0 };


	/* ������������� ��������� ��������� ����� �1 */
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glPopMatrix();

	/* ������������� ��������� ��������� ����� �2 */
	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glPopMatrix();

	/* ������������� ��������� ��������� ����� �3 */
	glPushMatrix();
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular3);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
	glPopMatrix();

	/* �������� z-����� */
	glEnable(GL_DEPTH_TEST);
	/* �������� ��������� � �������� ����� */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);



}

// ������� ���������� ��� ������������� ����������� �����������. � ��� �������������� ���� ����� ���������.
void display(void)
{
	/* ������� ����� ����� � ����� ������� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(20.0, 1.0, 0.0, 0.0);

	// �������� ��� ��������� ������������� �������� rotate_x � rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	/* ���������� ��� */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat1_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat1_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glPushMatrix();
	glTranslatef(-0.75, 0.5, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glutSolidTorus(0.275, 0.85, 100, 100);
	glPopMatrix();

	/* ���������� ����� */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat2_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat2_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glPushMatrix();
	glTranslatef(-0.75, -0.5, 0.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glutSolidCone(1.0, 2.0, 100, 100);
	glPopMatrix();

	/* ���������� ��� */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat3_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat3_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glPushMatrix();
	glTranslatef(1.5, 0.0, -1.0);
	glutSolidSphere(1.0, 100, 100);
	glPopMatrix();

	/* ���������� ��� */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat4_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat4_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glPushMatrix();
	glTranslatef(1.0, 2.0, -1.0);
	glRotatef(45.0, 1.0, 1.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
	/* ������� ����� �� ����� */
	glFlush();
}

// ���������� ��� ��������� ������������� �������� ����
void reshape(int w, int h)
{
	// ������������� ������ ������� ������ ������ ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	/* ������ ������� �������� � ������ �������� ���� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(
		40.0, /* ���� ������ � �������� */
		(GLfloat)w / h, /* ����������� ������ ���� */
		1, 100.0);  /* ���������� �� ���������� ��������� */
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(
		0.0f, 0.0f, 9.0f, /* ��������� ������ */
		0.0f, 0.0f, 0.0f, /* ����� ����� */
		0.0f, 100.0f, 0.0f); /* ������������� ����������� ��� y */
}

/* ���������� ��� ������� ������� �� ���������� */
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27: /* escape */
		exit(0);
		break;
	}
}

void specialKeys(int key, int x, int y) {

	//  ������ ������� - ���������� �������� �� 3 ��������
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 3;

	//  ����� ������� - ���������� �������� �� 3 ��������
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 3;

	else if (key == GLUT_KEY_UP)
		rotate_x -= 3;

	else if (key == GLUT_KEY_DOWN)
		rotate_x += 3;

	//  ������ ���������� ������
	glutPostRedisplay();

}

// ������� ���� ����������. ��������� ����, ��������������� ����� ������ � ������� �������
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CG LR3");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}