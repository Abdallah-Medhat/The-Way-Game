#define STB_IMAGE_IMPLEMENTATION
#include<Windows.h>
#include<gl\glut.h>
#include<iostream>
#include <gl/stb_image.h>

////////Display Screen
int START = 0;

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
	  lightPos  [] = {0.0f,2.0f,0.0f,1};
	  
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
void draw();
void frontscreen(void);
void goverscreen(void);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	glutCreateWindow("The Way");
	initGL();
	glutDisplayFunc(display);
	PlaySound("back.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
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
	 glLoadIdentity();

	 if(START==0)
	 {
		 frontscreen();
	 }
	 else if(START==2)
	 {
		 goverscreen();
	 }
	 else if(START==1)
	 {
		 draw();
		 update();
	 }
	
	 glutSwapBuffers(); 
}

void draw()
{
	drawStrokeText("LEFT: <-, RIGHT: ->, MAIN MENU: Esc ",-4,4,-5);
	drawStrokeText("brightness-> HIGH: PageUp, LOW: PageDown ",-4,3,-3);

	////////////////////////Texture
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
		case 'q':
			exit(0);
			break;
		case 13:
            START=1;
            break;
        case 27:
            START=0;
            break;
	}
	glutPostRedisplay();
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

		case GLUT_KEY_PAGE_UP:
			lightPos[2] -= 2;
			glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
			break;

		case GLUT_KEY_PAGE_DOWN:
			lightPos[2] += 2;
			glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
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
			//goverscreen();
			START=2;
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
			START=2;
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
			START=2;
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
			START=2;
		}
	}
	////////////////////////
}

void drawStrokeText(char* str,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y,z);
	  glScalef(0.002f,0.002f,z);
	  for (c=str; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}

void drawStrokeText2(char* str,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y,z);
	  glScalef(0.005f,0.005f,z);
	  for (c=str; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}

void drawStrokeChar(char c,float x,float y,float z)
{
	  glPushMatrix();
          glTranslatef(x, y,z);
          glScalef(0.002f,0.002f,z);
          glutStrokeCharacter(GLUT_STROKE_ROMAN , c);
	  glPopMatrix();
}

void frontscreen(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	drawStrokeText2("The Way Game",-2,0,0);
    drawStrokeText("Press Enter to Start",-1,-1,0);
    drawStrokeText("Press Q to Exit",-1,-2,0);
	glFlush();
}

void goverscreen(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	drawStrokeText2("Game Over",-2,0,0);
    drawStrokeText("Press Enter to Start Again",-2,-1,0);
    drawStrokeText("Press Q to Exit",-2,-2,0);
	glFlush();
}