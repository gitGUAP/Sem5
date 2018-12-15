#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

//static int useRGB = 1;
//static int useLighting = 1;
//static int useFog = 0;
//static int useDB = 1;
//static int useLogo = 0;
//static int useQuads = 1;

static int tick = -1;
static int moving = 1;

static float materialColor[8][4] =
{
	{ 0.8, 0.8, 0.8, 1.0 },
	{ 0.8, 0.0, 0.0, 1.0 },
	{ 0.0, 0.8, 0.0, 1.0 },
	{ 0.0, 0.0, 0.8, 1.0 },
	{ 0.0, 0.8, 0.8, 1.0 },
	{ 0.8, 0.0, 0.8, 1.0 },
	{ 0.8, 0.8, 0.0, 1.0 },
	{ 0.0, 0.0, 0.0, 0.6 },
};

static float lightPos[4] =
{ 2.0, 4.0, 2.0, 1.0 };
//#if 0
//static float lightDir[4] =
//{ -2.0, -4.0, -2.0, 1.0 };
//#endif
static float lightAmb[4] =
{ 0.2, 0.2, 0.2, 1.0 };
static float lightDiff[4] =
{ 0.8, 0.8, 0.8, 1.0 };
static float lightSpec[4] =
{ 0.4, 0.4, 0.4, 1.0 };

static float groundPlane[4] =
{ 0.0, 1.0, 0.0, 1.499 };
static float backPlane[4] =
{ 0.0, 0.0, 1.0, 0.899 };

static float fogColor[4] =
{ 0.0, 0.0, 0.0, 0.0 };
static float fogIndex[1] =
{ 0.0 };

static unsigned char shadowPattern[128] =
{
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,  /* 50% Grey */
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
	0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55
};



static float cube_vertexes[6][4][4] =
{
	{
		{ -1.0, -1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0, 1.0 },
		{ -1.0, 1.0, 1.0, 1.0 },
		{ -1.0, 1.0, -1.0, 1.0 } },

		{
			{ 1.0, 1.0, 1.0, 1.0 },
			{ 1.0, -1.0, 1.0, 1.0 },
			{ 1.0, -1.0, -1.0, 1.0 },
			{ 1.0, 1.0, -1.0, 1.0 } },

			{
				{ -1.0, -1.0, -1.0, 1.0 },
				{ 1.0, -1.0, -1.0, 1.0 },
				{ 1.0, -1.0, 1.0, 1.0 },
				{ -1.0, -1.0, 1.0, 1.0 } },

				{
					{ 1.0, 1.0, 1.0, 1.0 },
					{ 1.0, 1.0, -1.0, 1.0 },
					{ -1.0, 1.0, -1.0, 1.0 },
					{ -1.0, 1.0, 1.0, 1.0 } },

					{
						{ -1.0, -1.0, -1.0, 1.0 },
						{ -1.0, 1.0, -1.0, 1.0 },
						{ 1.0, 1.0, -1.0, 1.0 },
						{ 1.0, -1.0, -1.0, 1.0 } },

						{
							{ 1.0, 1.0, 1.0, 1.0 },
							{ -1.0, 1.0, 1.0, 1.0 },
							{ -1.0, -1.0, 1.0, 1.0 },
							{ 1.0, -1.0, 1.0, 1.0 } }
};

static float cube_normals[6][4] =
{
	{ -1.0, 0.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0, 0.0 },
	{ 0.0, -1.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, -1.0, 0.0 },
	{ 0.0, 0.0, 1.0, 0.0 }
};

GLfloat koord_flat[4][4] = { 
	{-1, 1 , 0, 1}, 
	{ -1, -1 , 0, 1 },
	{ 1, -1 , 0, 1 },
	{ 1, 1 , 0, 1 },
};



static void drawCube(int color)
{
	int i;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &materialColor[color][0]);

	for (i = 0; i < 6; ++i) {
		glNormal3fv(&cube_normals[i][0]);
		glBegin(GL_POLYGON);
		glVertex4fv(&cube_vertexes[i][0][0]);
		glVertex4fv(&cube_vertexes[i][1][0]);
		glVertex4fv(&cube_vertexes[i][2][0]);
		glVertex4fv(&cube_vertexes[i][3][0]);
		glEnd();
	}
}



static void myShadowMatrix(float ground[4], float light[4])
{
	float dot;
	float shadowMat[4][4];

	dot = ground[0] * light[0] +
		ground[1] * light[1] +
		ground[2] * light[2] +
		ground[3] * light[3];

	shadowMat[0][0] = dot - light[0] * ground[0];
	shadowMat[1][0] = 0.0 - light[0] * ground[1];
	shadowMat[2][0] = 0.0 - light[0] * ground[2];
	shadowMat[3][0] = 0.0 - light[0] * ground[3];

	shadowMat[0][1] = 0.0 - light[1] * ground[0];
	shadowMat[1][1] = dot - light[1] * ground[1];
	shadowMat[2][1] = 0.0 - light[1] * ground[2];
	shadowMat[3][1] = 0.0 - light[1] * ground[3];

	shadowMat[0][2] = 0.0 - light[2] * ground[0];
	shadowMat[1][2] = 0.0 - light[2] * ground[1];
	shadowMat[2][2] = dot - light[2] * ground[2];
	shadowMat[3][2] = 0.0 - light[2] * ground[3];

	shadowMat[0][3] = 0.0 - light[3] * ground[0];
	shadowMat[1][3] = 0.0 - light[3] * ground[1];
	shadowMat[2][3] = 0.0 - light[3] * ground[2];
	shadowMat[3][3] = dot - light[3] * ground[3];

	glMultMatrixf((const GLfloat *)shadowMat);
}

void
idle(void)
{
	tick+=1;
	/*if (tick >= 120) {
		tick = 0;
	}*/
	glutPostRedisplay();
}

void display(void)
{
	GLfloat cubeXform[4][4];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(-0.5, -0.5, -0.9);
	glScalef(2.0, 2.0, 2.0);
	glMaterialfv(GL_FRONT_AND_BACK,
		GL_AMBIENT_AND_DIFFUSE, &materialColor[0][0]);
	glBegin(GL_POLYGON);

	glVertex4fv(&koord_flat[0][0]);
	glVertex4fv(&koord_flat[1][0]);
	glVertex4fv(&koord_flat[2][0]);
	glVertex4fv(&koord_flat[3][0]);
	glEnd();

	//drawCheck(6, 6, BLUE, YELLOW);  /* draw back */
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glRotatef((360.0 / (30 * 10)) * tick * 0.1, 1, 1, 1);
	glScalef(1.0, 2.0, 1.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)cubeXform);

	drawCube(3);
	glutSolidCube(2);        /* draw cube */
	glPopMatrix();

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);

	glPushMatrix();
	myShadowMatrix(backPlane, lightPos);
	glTranslatef(0.0, 0.0, 2.0);
	glMultMatrixf((const GLfloat *)cubeXform);

	drawCube(7);      /* draw back shadow */
	glPopMatrix();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glutSwapBuffers();
	
}



void visible(int state)
{
	if (state == GLUT_VISIBLE) {
		if (moving)
			glutIdleFunc(idle);
	}
	else {
		if (moving)
			glutIdleFunc(NULL);
	}
}

int main(int argc, char **argv)
{
	glutInitWindowSize(600, 600);
	glutInit(&argc, argv);
	
	/* choose visual */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		
	glutCreateWindow("Lab 6");

	glutDisplayFunc(display);
	glutVisibilityFunc(visible);


	/* setup context */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluLookAt(-0.3, 0.5, 0.5, 1.0, 4.0, -3.0, 1.0, 1.0, -1.0);
	//gluLookAt(-0.3, 0.5, 0.5, 1.0, 4.0, -3.0, 1.0, 1.0, -1.0);

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 3.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

	glEnable(GL_NORMALIZE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glShadeModel(GL_SMOOTH);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glPolygonStipple((const GLubyte *)shadowPattern);

	glClearColor(0.0, 0.0, 0.0, 1);
	glClearIndex(0);
	glClearDepth(1);

	glutMainLoop();
	return 0;           
}