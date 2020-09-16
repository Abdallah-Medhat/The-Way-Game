#define STB_IMAGE_IMPLEMENTATION
#include<Windows.h>
#include<gl\glut.h>
#include<iostream>
#include <stdlib.h>
#include <gl/stb_image.h>

////////Updata
static int flag=1;

///////Texture
unsigned int texture;
int width, height, nrChannels;
unsigned char *data = NULL;

///////Ball Position
float pos = 0.0f;
float ballz = 3.0f;

///////Light
float matamb    [] = {1.0f,1.0f,0.0f,1.0f},
	  matshin   [] = {128.0f},
	  lightamb  [] = {0.5,0.5,0.5,1},
	  lightPos  [] = {0.0f,2.0f,5.0f,1};
	  
/////////////Objects
float cupe  = -35.0f, xcupe  = -1.2f, ycupe  = -1.0f, zspeed  = 0.5f;   //middle left
float cupe1 = -50.0f, xcupe1 = -3.0f, ycupe1 = -1.0f, zspeed1 = 0.5f;   //left
float cupe2 = -70.0f, xcupe2 =  3.0f, ycupe2 = -1.0f, zspeed2 = 0.5f;   //right
float cupe3 = -90.0f, xcupe3 =  1.2f, ycupe3 = -1.0f, zspeed3 = 0.5f;   //middle right

void initGL();
void display();
void timer(int);
void reshape(int,int);
void keyboard(unsigned char , int , int);
void specialKeys(int, int , int );
void check (unsigned char *data);
void load ( int );
void setLights();
void update();
void drawStrokeText(char* ,int ,int ,int );
void drawStrokeText2(char* ,int ,int ,int );
void drawStrokeChar(char ,float ,float ,float );

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	glutCreateWindow("The Way");
	initGL();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys); 
	glutMainLoop();
}

void initGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void display()
{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glMatrixMode(GL_MODELVIEW);
	 setLights();
	 
	 ////////////////////////Texture
	 glLoadIdentity();
	 glTranslatef(0,0,-5);

	 ////Ground
	 load(1);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0.0f,0.0f);
	 glVertex3f( 4,-2,10);
	 glTexCoord2d(1.0f,0.0f);
     glVertex3f(-4,-2,10);
	 glTexCoord2d(1.0f,1.0f);
     glVertex3f(-4,-2,-90);
	 glTexCoord2d(0.0f,1.0f);
     glVertex3f(4,-2,-90);
	 glEnd();

	 ////Face
	 /*load(3);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0.0f,0.0f);
	 glVertex3f(-4,-2,-40);
	 glTexCoord2d(1.0f,0.0f);
     glVertex3f(4,-2,-40);
	 glTexCoord2d(1.0f,1.0f);
     glVertex3f(4,6,-40);
	 glTexCoord2d(0.0f,1.0f);
     glVertex3f(-4,6,-40);
	 glEnd();*/

	 ////Left
	 /*load(2);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0.0f,0.0f);
	 glVertex3f( -4,-2,-40);
	 glTexCoord2d(1.0f,0.0f);
	 glVertex3f(-4,-2,10);
	 glTexCoord2d(1.0f,1.0f);
	 glVertex3f(-4,6,10);
	 glTexCoord2d(0.0f,1.0f);
	 glVertex3f(-4,6,-40);
	 glEnd();*/

	 ////Right
	 /*load(2);
	 glBegin(GL_QUADS);
	 glTexCoord2d(0.0f,0.0f);
	 glTexCoord2d(1.0f,0.0f);
	 glVertex3f( 4,-2,-40);
	 glVertex3f(4,-2,10);
	 glTexCoord2d(1.0f,1.0f);
	 glVertex3f(4,6,10);
	 glTexCoord2d(0.0f,1.0f);
	 glVertex3f(4,6,-40);
	 glEnd();*/
	 //////////////////////////////////////
	 
	 //////////////////////Objects
	 //////////cube
	 glLoadIdentity();
	 glTranslatef(xcupe,ycupe,cupe);
	 glBegin(GL_QUADS);
	 glColor3f(0.0f,1.0f,0.0f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,-0.5f);

	 glColor3f(1.0,0.5f,0.0f);
	 glVertex3f(1.0f,-1.0f,0.5f);
     glVertex3f(-1.0f,-1.0f,0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(1.0f,-1.0f,-0.5f);

	 glColor3f(1.0f,0.0f,0.0f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,-1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,0.5f);

	 glColor3f(1.0f,1.0f,0.0f);
	 glVertex3f(1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,-0.5f);

	 glColor3f(0.0f,0.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,0.5f);

	 glColor3f(1.0f,0.0f,1.0f);
	 glVertex3f(1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,-0.5f);
	 glEnd();

	 ///////cube1
	 glLoadIdentity();
     glTranslatef(xcupe1,ycupe1,cupe1);
	 glBegin(GL_QUADS);
	 glColor3f(0.0f,1.0f,0.0f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,-0.5f);

	 glColor3f(1.0,0.5f,0.0f);
	 glVertex3f(1.0f,-1.0f,0.5f);
     glVertex3f(-1.0f,-1.0f,0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(1.0f,-1.0f,-0.5f);

	 glColor3f(1.0f,0.0f,0.0f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,-1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,0.5f);

	 glColor3f(1.0f,1.0f,0.0f);
	 glVertex3f(1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,-0.5f);

	 glColor3f(0.0f,0.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,0.5f);

	 glColor3f(1.0f,0.0f,1.0f);
	 glVertex3f(1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,-0.5f);
	 glEnd();

	 ////////cube2
	 glLoadIdentity();
     glTranslatef(xcupe2,ycupe2,cupe2);
	 glBegin(GL_QUADS);
	 glColor3f(0.0f,1.0f,0.0f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,-0.5f);

	 glColor3f(1.0,0.5f,0.0f);
	 glVertex3f(1.0f,-1.0f,0.5f);
     glVertex3f(-1.0f,-1.0f,0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(1.0f,-1.0f,-0.5f);

	 glColor3f(1.0f,0.0f,0.0f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,-1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,0.5f);

	 glColor3f(1.0f,1.0f,0.0f);
	 glVertex3f(1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,-0.5f);

	 glColor3f(0.0f,0.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,0.5f);

	 glColor3f(1.0f,0.0f,1.0f);
	 glVertex3f(1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,-0.5f);
	 glEnd();

	 ////////cube3
	 glLoadIdentity();
     glTranslatef(xcupe3,ycupe3,cupe3);
	 glBegin(GL_QUADS);
	 glColor3f(0.0f,1.0f,0.0f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,-0.5f);

	 glColor3f(1.0,0.5f,0.0f);
	 glVertex3f(1.0f,-1.0f,0.5f);
     glVertex3f(-1.0f,-1.0f,0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(1.0f,-1.0f,-0.5f);

	 glColor3f(1.0f,0.0f,0.0f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,-1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,0.5f);

	 glColor3f(1.0f,1.0f,0.0f);
	 glVertex3f(1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,-0.5f);

	 glColor3f(0.0f,0.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,0.5f);
	 glVertex3f(-1.0f,1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,-0.5f);
	 glVertex3f(-1.0f,-1.0f,0.5f);

	 glColor3f(1.0f,0.0f,1.0f);
	 glVertex3f(1.0f,1.0f,-0.5f);
	 glVertex3f(1.0f,1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,0.5f);
	 glVertex3f(1.0f,-1.0f,-0.5f);
	 glEnd();
	 /////////////////////////////////////

	 ////////////////////Ball
	 glLoadIdentity();
	 glColor3f(0.5f, 0.5f, 0.5f);
	 glTranslatef(pos ,-1.0f, ballz);
	 glutSolidSphere(0.2f,20,10);
	 //////////////////////////////
	 glColor3f(1.0f,1.0f,1.0f);
	 update();
	 glutSwapBuffers(); 
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(30,timer,0);
}

void reshape(GLsizei width,GLsizei height)
{
	if(height==0) height=1;
	GLfloat aspect=(GLfloat)width / (GLfloat)height;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f,aspect,0.1f,100.0f);
	gluLookAt
		(
			0.0f, 1.5f, 5.0f,
			0.0f, 1.0f, 4.0f,
			0.0f, 1.0f, 0.0f
		);
}

void keyboard(unsigned char key, int x , int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
	}

	//////////////////light
	if( key == 'w')
	{
		lightPos[2] -= 2;
		glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	}
	if( key == 's')
	{
		lightPos[2] += 2;
		glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	}
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_RIGHT: 
			pos += 0.5f;
			if (pos == 3.0f)
			{
				pos=2.5f;
			}
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			pos -=0.5f;
			if (pos == -3.0f)
			{
				pos=-2.5f;
			}
			glutPostRedisplay();
			break;
	}
}

void load ( int imgnum )
{
	if( imgnum == 1)
	{
		data= stbi_load("clean city road straight.bmp", &width, &height, &nrChannels, 0);
		check(data);
	}
	else if( imgnum == 2)
	{
		data= stbi_load("blur-blurred-background-colors-754082.bmp", &width, &height, &nrChannels, 0);
		check(data);
	}
	else if( imgnum == 3)
	{
		data= stbi_load("WhatsApp Image 2019-05-10 at 11.56.24 PM.jpeg", &width, &height, &nrChannels, 0);
		check(data);
	}
}

void check (unsigned char *data)
{
	if( data )
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void setLights()
{
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glLightfv(GL_LIGHT0,GL_AMBIENT, lightamb);
	
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT,GL_AMBIENT,matamb);
	glMaterialfv(GL_FRONT,GL_SHININESS,matshin);
}

void update()
{
	///////////////////////////Objects Position & Collision
	//////cupe
	if(flag)
	{
		cupe += zspeed;
		if( cupe > 4.0f )
		{
			cupe =- 35.0f;
		}
		if(cupe == 3.0f && ballz <= cupe+0.5f && ballz >= cupe-0.5f && pos <= 0.0f && pos >=-2.2f)
		{
			exit(0);
		}
	}

	/////cupe1
	if(flag)
	{
		cupe1 += zspeed1;
		if( cupe1 > 4.0f )
		{
			cupe1 =- 50.0f;
		}
		if(cupe1 == 3.0f && ballz <= cupe1+0.5f && ballz >= cupe1-0.5f && pos >= -2.5f && pos <= -1.5f)
		{
			exit(0);
		}
	}
	 
	/////cupe2
	if(flag)
	{
		cupe2 += zspeed2;
		if( cupe2 > 4.0f )
		{
			cupe2 =- 70.0f;
		}
		if(cupe2 == 3.0f && ballz <= cupe2+0.5f && ballz >= cupe2-0.5f && pos <= 2.5f && pos >= 1.5f)
		{
			exit(0);
		}
	}

	/////cupe3
	if(flag)
	{
		cupe3 += zspeed3;
		if( cupe3 > 4.0f )
		{
			cupe3 =- 90.0f;
		}
		if(cupe3 == 3.0f && ballz <= cupe3+0.5f && ballz >= cupe3-0.5f && pos >= 0.0f && pos <=2.2f)
		{
			exit(0);
		}
	}
	////////////////////////
}





