#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "imageloader.h"
#include "glm.h"


#define PI 3.14

double eye[] = {0, 0, 10.0};
double center[] = {0, 0, 0};
double up[] = {0, 1, 0};

int moving, startx, starty;

static int elbow[] = { 0, 0 };
static int arm[] = { -90, 90 };
static int armZ[] = { 0, 0 };
static int legX[] = { -5, 5 };
static int legZ[] = { 0, 0 };
static int knee[] = { 0, 0 };
static int fingers[] = { 0, 0 };
static int flang[] = { 0, 0 };

static int bend_angle = 0;
static float vacum_pos = 2.2;

static float xCarpet = 0;
static float yCarpet = 0;
static float zCarpet = 0.3;

int poses_number = 5;
// poses for armZ[1], bend_angle, vacum_pos , legX[1]
float poses[5][4] = {{-60, 35, 2.2, 10}, {-65, 35, 2.41, 10}, {-75, 40, 2.6, 5}, {-80, 45, 2.74, 0}, {-85, 45, 2.83, 0}};

// const char* Carpet = "data/carpet.obj";
// const char* Vacum = "data/aspirateur.obj";

// const char *Carpet = "data/carpet.obj";
GLMmodel* Vacum = glmReadOBJ("data/aspirateur.obj");
GLMmodel* Sofa = glmReadOBJ("data/clicClac.obj");



GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

GLuint _textureId; //The id of the texture
GLuint _textureId1; //The id of the texture

// RGBA
GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
// x , y, z, w
GLfloat light_position[] = {0.5, 5.0, 0.0, 1.0};
GLfloat lightPos1[] = {-0.5, -5.0, -2.0, 1.0};





//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image *image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);			 //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,				  //Always GL_TEXTURE_2D
				 0,							  //0 for now
				 GL_RGB,					  //Format OpenGL uses for image
				 image->width, image->height, //Width and height
				 0,							  //The border of the image
				 GL_RGB,					  //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
											  //as unsigned numbers
				 image->pixels);			  //The actual pixel data
	return textureId;						  //Returns the id of the texture
}


//Initializes 3D rendering
void initRendering(const char* bmbImg, GLuint & textureId){
    // Loading a Texture
    Image *image = loadBMP(bmbImg);
    textureId = loadTexture(image);
    delete image;

    // Turn on the power
	glEnable(GL_LIGHTING);
	// Flip light switch
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	// assign light parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	// Material Properties
	GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	// glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
	glEnable(GL_NORMALIZE);

    //Enable smooth shading
   glShadeModel(GL_SMOOTH);

   // Enable Depth buffer
   glEnable(GL_DEPTH_TEST);


}


void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta) * p[0];
	temp[1] += cos(theta) * p[1];
	temp[2] += cos(theta) * p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}
void turnLeft()
{
	double theta = -PI / 100;
	rotatePoint(up, theta, eye);
}

void turnRight()
{
	double theta = PI / 100;
	rotatePoint(up, theta, eye);
}

void moveUp()
{
	double horizontal[3];
	double look[] = {center[0] - eye[0], center[1] - eye[1], center[2] - eye[2]};
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, PI / 100, eye);
	rotatePoint(horizontal, PI / 100, up);
}

void moveDown()
{

	double horizontal[3];
	double look[] = {center[0] - eye[0], center[1] - eye[1], center[2] - eye[2]};
	crossProduct(up, look, horizontal);
	normalize(horizontal);
	rotatePoint(horizontal, -PI / 100, eye);
	rotatePoint(horizontal, -PI / 100, up);
}

void moveForward()
{

	double speed = 0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];
	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}

void moveBack()
{

	double speed = -0.1;
	double direction[3];
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	normalize(direction);

	eye[0] += direction[0] * speed;
	eye[2] += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[2] += direction[2] * speed;
}

void DrawModel(GLMmodel* Object, GLfloat Scale, GLfloat Angle)
{

    if (!Object) exit(0);
    glmUnitize(Object);
    glmFacetNormals(Object);
    glmVertexNormals(Object, Angle);
    glmScale(Object, Scale);
    glmDraw(Object, GLM_SMOOTH|GLM_MATERIAL);
//    glmDraw(Object, GLM_SMOOTH|GLM_MATERIAL);
}

// void drawmodel(char *filename)
// {
// 	GLMmodel *model = glmReadOBJ(filename);
// 	glmUnitize(model);
// 	glmFacetNormals(model);
// 	glmVertexNormals(model, 90.0);
// 	glmScale(model, .15);
// 	glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
// }

void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Clear Depth and Color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();

    glPushMatrix();
    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        up[0], up[1], up[2]);

    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    //floor
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-25, -2.25, 25);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(25, -2.25, 25);
    glTexCoord2f(5.0f, 20.0f);
    glVertex3f(25, -2.25, -25);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-25, -2.25, -25);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, -1.3, 4);
    DrawModel(Sofa, 2, 90.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9, -1, vacum_pos);
    glRotatef(90.0, 0.0 ,1.0 ,0);
    DrawModel(Vacum, 2, 90.0);
    glPopMatrix();

    // START OF RIGHT LEG
    glPushMatrix();

    glTranslatef(0.5, 0.0, 0.0);
    glRotatef((GLfloat)legZ[0], 0.0, 0.0, 1.0);
    glTranslatef(-0.5, 0.0, 0.0);

    glRotatef((GLfloat)legX[0], 1.0, 0.0, 0.0);
    glTranslatef(0.5, -0.5, 0.0);

    glPushMatrix();
    glScalef(0.5, 1.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();


    glTranslatef(0.0, -0.5, 0.0);
    glRotatef((GLfloat)knee[0], 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.5, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glTranslatef(0.0, -0.625, 0.0);
    glPushMatrix();
    glScalef(0.75, 0.25, 0.75);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
    // END OF RIGHT LEG


    // START OF LEFT LEG
    glPushMatrix();

    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef((GLfloat)legZ[1], 0.0, 0.0, 1.0);
    glTranslatef(+0.5, 0.0, 0.0);

    glRotatef((GLfloat)legX[1], 1.0, 0.0, 0.0);
    glTranslatef(-0.5, -0.5, 0.0);

    glPushMatrix();
    glScalef(0.5, 1.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();


    glTranslatef(0.0, -0.5, 0.0);
    glRotatef((GLfloat)knee[1], 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.5, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glTranslatef(0.0, -0.625, 0.0);
    glPushMatrix();
    glScalef(0.75, 0.25, 0.75);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
    // END OF LEFT LEG

    // start of upper body
    glPushMatrix();
    glRotatef(bend_angle,1,0,0);

    // START OF TRUNK
    glPushMatrix();
    glTranslatef(0.0, 1, 0.0);
    glScalef(1.5, 2.0, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();
    // END OF TRUNK

    // // START OF STOMACH
    // glPushMatrix();
    // glTranslatef(0.0, 1.25, 0.0);
    // glScalef(1, 1, 0.5);
    // glutSolidCube(1.0);
    // glPopMatrix();
    // // END OF STOMACH

    // START OF HEAD
    glPushMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    glutWireSphere(0.35, 16, 16);
    glPopMatrix();
    // END OF HEAD


    // START OF RIGHT ARM

    glPushMatrix();



    glTranslatef(1.25, 1.85, 0.0);


    glRotatef((GLfloat)armZ[0], 1.0, 0.0, 0.0);


    glTranslatef(-0.375, 0, 0);
    glRotatef(arm[0], 0.0, 0.0, 1.0);
    glTranslatef(0.375, 0, 0);

    // Draw the limb
    // The shoulder is centered in origin and has 1, 1, 1 dimensions
    glPushMatrix();
    glScalef(0.75, 0.3, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glTranslatef(0.75, 0, 0);

    glTranslatef(-0.375, 0, 0.0);
    glRotatef((GLfloat)elbow[0], 0.0, 0.0, 1.0);
    glTranslatef(0.375, 0, 0.0);
    glPushMatrix();
    glScalef(0.75, 0.3, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // START OF FINGER 1
    glPushMatrix();

    glTranslatef(0.475, 0.05, 0.1125);

    glTranslatef(-0.1, 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 1


    // START OF FINGER 2
    glPushMatrix();

    glTranslatef(0.475, 0.05, 0.0375);

    glTranslatef(-0.1, 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 2

    // START OF FINGER 3
    glPushMatrix();

    glTranslatef(0.475, 0.05, -0.0375);
    glTranslatef(-0.1, 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 3


    // START OF FINGER 4
    glPushMatrix();

    glTranslatef(0.475, 0.05, -0.1125);

    glTranslatef(-0.1, 0, 0);
    glRotatef(flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glRotatef(fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 4


    // START OF FINGER 5
    glPushMatrix();

    glTranslatef(0.475, -0.1, 0);

    glTranslatef(-0.1, 0, 0);
    glRotatef(-flang[0], 0, 0, 1);
    glTranslatef(0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, 0, 0);
    glTranslatef(-0.05, 0, 0);
    glRotatef(-fingers[0], 0, 0, 1);
    glTranslatef(0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 5

    glPopMatrix();


    // END OF RIGHT ARM


    // START OF LEFT ARM

    glPushMatrix();

    glTranslatef(-1.25, 1.85, 0.0);
    glRotatef((GLfloat)armZ[1], 1.0, 0.0, 0.0);
    glTranslatef(0.375, 0, 0);
    glRotatef(arm[1], 0.0, 0.0, 1.0);
    glTranslatef(-0.375, 0, 0);

    // Draw the limb
    // The shoulder is centered in origin and has 1, 1, 1 dimensions
    glPushMatrix();
    glScalef(0.75, 0.3, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glTranslatef(-0.75, 0, 0);

    glTranslatef(0.375, 0, 0.0);
    glRotatef((GLfloat)elbow[1], 0.0, 0.0, 1.0);
    glTranslatef(-0.375, 0, 0.0);
    glPushMatrix();
    glScalef(0.75, 0.3, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // START OF FINGER 1
    glPushMatrix();

    glTranslatef(-0.475, 0.05, 0.1125);

    glTranslatef(0.1, 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 1


    // START OF FINGER 2
    glPushMatrix();

    glTranslatef(-0.475, 0.05, 0.0375);
    glTranslatef(0.1, 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 2

    // START OF FINGER 3
    glPushMatrix();

    glTranslatef(-0.475, 0.05, -0.0375);

    glTranslatef(0.1, 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 3


    // START OF FINGER 4
    glPushMatrix();

    glTranslatef(-0.475, 0.05, -0.1125);

    glTranslatef(0.1, 0, 0);
    glRotatef(flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 4


    // START OF FINGER 5
    glPushMatrix();

    glTranslatef(-0.475, -0.1, 0);

    glTranslatef(0.1, 0, 0);
    glRotatef(-flang[1], 0, 0, 1);
    glTranslatef(-0.1, 0, 0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1, 0, 0);
    glTranslatef(0.05, 0, 0);
    glRotatef(-fingers[1], 0, 0, 1);
    glTranslatef(-0.05, 0, 0);
    glScalef(0.1, 0.1, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // END OF FINGER 5

    glPopMatrix();

    // END OF LEFT ARM

    glPopMatrix();
    // end of upper body

    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    glutSwapBuffers();

}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		turnLeft();
		break;
	case GLUT_KEY_RIGHT:
		turnRight();
		break;
	case GLUT_KEY_UP:
		if (center[1] <= 1.5)
			moveUp();
		break;
	case GLUT_KEY_DOWN:
		if (center[1] >= -1.5)
			moveDown();
		break;
	}
	glutPostRedisplay();
}


void Keyboard(unsigned char Key, int x, int y)
{

	switch (Key)
	{

	case 'T':
		moveForward();
		break;
	case 't':
		moveBack();
		break;

	case 27:
		exit(0);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void main_menu(int id)
{

	switch (id)
	{
	case 1:
		initRendering("images/floor.bmp",_textureId);
		break;

	case 2:
		initRendering("images/floor2.bmp",_textureId);
		break;

	case 3:
		initRendering("images/floor3.bmp",_textureId);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void set_poses(int f)
{
    armZ[1] = poses[f][0];
    bend_angle = poses[f][1];
    vacum_pos = poses[f][2];
}


static int f  = 0;
static int dec = 0;
void timer(int v)
{
    if(f == poses_number)
        dec = 1;
    else if(f == 1) 
        dec = 0;

    if(dec)
        f--;
    else
        f++;
    set_poses(f - 1);

    glutPostRedisplay();
    glutTimerFunc(200,timer,0);

}


int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Floor");
	initRendering("images/floor.bmp", _textureId);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, 1.0, 0.1, 20);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(display);
    glutTimerFunc(0,timer,0);
	glutCreateMenu(main_menu);
	glutAddMenuEntry("Floor", 1);
	glutAddMenuEntry("floor2", 2);
	glutAddMenuEntry("floor3", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
