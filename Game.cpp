#include <GL\glew.h>  
#include <stdlib.h>
#include <GL\freeglut.h>   
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
GLuint myTexture1;
GLuint myTexture2;
GLuint myTexture3;

char image1Path[] = "C:/Users/Wasan/Downloads/stop.bmp";
char image2Path[] = "C:/Users/Wasan/Downloads/game6.bmp";
char image3Path[] = "C:/Users/Wasan/Downloads/green.bmp";
float xtm = 0.0, ytm = 0.0,
scl = 1.0, xcr = -50.0;

GLint win_width = 500,
win_hight = 500;

float transValueX;
float transValueY;
float transValueZ;

GLfloat light_ambiant[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightX = 1.1, lightY = 0.0, lightZ = 0.3;
GLfloat light_position[] = { lightX, lightY, lightZ, 1.0 };

GLfloat light_ambiant1[] = { 0.9, 0.0, 0.0, 1.0 };
GLfloat light_diffuse1[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat lightX1 = -39, lightY1 = -10, lightZ1 = 0;
GLfloat light_position1[] = { lightX1, lightY1, lightZ1, 1.0 };

GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat shininess[] = { 128 };


GLuint LoadTexture(const char* filename, int width, int height)
{
    GLuint texture;
    unsigned char* data;
    FILE* file;

    //The following code will read in our RAW file
    file = fopen(filename, "rb");

    if (file == NULL)
    {
        cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
        exit(0);
        return 0;
    }

    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);

    fclose(file);


    // reorder the image colors to RGB not BGR
    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;

    }

    glGenTextures(1, &texture);            //generate the texture with the loaded data
    glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //set texture environment parameters

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);


    free(data); //free the texture array

    if (glGetError() != GL_NO_ERROR)
        printf("GLError in genTexture()\n");

    return texture; //return whether it was successfull
}



void Init(void)
{

    transValueX = 3.5;
    transValueY = 2.0;
    transValueZ = 2.0;

    myTexture1 = LoadTexture(image1Path, 1280, 582);
    if (myTexture1 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture1 << endl;

    myTexture2 = LoadTexture(image2Path, 800, 600);

    if (myTexture2 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture2 << endl;

    myTexture3 = LoadTexture(image3Path, 612, 408);

    if (myTexture3 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture3 << endl;
    glClearColor(0.8, 1, 0.9, 0.0); // Set background color to black and opaque

    glMatrixMode(GL_PROJECTION);
    gluPerspective(65, (win_width / win_hight), 0.01, 50);
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

}

//-----------------------------------------   Draw2d   --------------------------------------------

void Draw2d() {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture3);
    glBegin(GL_QUADS);
    glColor3d(1, 0, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-200, -25, 10);
    glTexCoord2f(1, 0);
    glVertex3f(200, -25, 10);
    glTexCoord2f(1, 1);
    glVertex3f(100, -150, 10);
    glTexCoord2f(0, 1);
    glVertex3f(-100, -150, 10);
    glDisable(GL_TEXTURE_2D);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture2);
    glBegin(GL_QUADS);
    glColor3d(1, 1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-200, -25, 10);
    glTexCoord2f(1, 0);
    glVertex3f(200, -25, 10);
    glTexCoord2f(1, 1);
    glVertex3f(100, 150, 10);
    glTexCoord2f(0, 1);
    glVertex3f(-100, 150, 10);
    glDisable(GL_TEXTURE_2D);
    glEnd();
    glDisable(GL_TEXTURE_2D);



}

//-----------------------------------------   Keybord   --------------------------------------------

void Keybord(unsigned char ch, int x, int y) {

    switch (ch) {
    case '-':

        scl -= 0.2;
        break;
    case '+':
        scl += 0.2;
        break;
    case 'd':
        if (xcr < 26)
        {
            xcr += 2.00;
        }
        break;
    case 'D':
        xcr -= 2.00;
        break;


    case 'X':
        if (lightX >= 5) {
            lightX = 0;
        }
        else {
            lightX += 0.1;

        }
        cout << "Light X: " << lightX << endl;
        break;
    case 'Y':
        if (lightY >= 5) {
            lightY = 0;
        }
        else {
            lightY += 0.1;

        }
        cout << "Light Y: " << lightY << endl;
        break;
    case 'Z':
        if (lightZ >= 10) {
            lightZ = 0;
        }
        else {
            lightZ += 0.1;

        }
        cout << "Light Z: " << lightZ << endl;
        break;


    case 'f':
        glShadeModel(GL_SMOOTH);
        break;
    case 'F':
        glShadeModel(GL_FLAT);
        break;


        /////////////////////////////////////////


    case 'q':
    case 27:
        exit(0);
        break;

    default:
        fprintf(stderr, "\nKeyboard commands:\n\n"
            "q, <esc> - Quit\n");
        break;

        //----------------------
    }
}
//------------------------------------------   special   ---------------------------------------------


static void special(int key, int x, int y)
{
    //handle special keys
    switch (key) {

    case GLUT_KEY_HOME:

        break;
    case GLUT_KEY_LEFT:
        transValueX -= .1;
        cout << " translate x:" << transValueX << endl;
        break;
    case GLUT_KEY_RIGHT:
        transValueX += .1;
        cout << " translate x:" << transValueX << endl;
        break;
    case GLUT_KEY_UP:
        transValueY += .1;
        cout << " translate y:" << transValueY << endl;
        break;
    case GLUT_KEY_DOWN:
        transValueY -= .1;
        cout << " translate y:" << transValueY << endl;
        break;
    default:
        break;
        //----------------------
    }
}
//------------------------------------------   play   ---------------------------------------------

static void play(void)
{
    glutPostRedisplay();
}
void reshapeFunc(GLint new_width, GLint new_hight)
{
    glViewport(0, 0, new_width, new_hight);
    win_width = new_width;
    win_hight = new_hight;
}
void Motion(int x, int y)
{}

//---------------------------------------   Init   ------------------------------------------


//----------------------------------------   Draw_Road   -------------------------------------------

void Draw_Road(void)
{

    glColor3f(0.0, 0.0, 0.2);
    glPushMatrix();
    glTranslatef(0.0, -25.0, 0.0);
    glScalef(20.0, 0.3, 3.0);
    glutSolidCube(-20.0f);
    glPopMatrix();
}

//---------------------------------------   Render_Wheel   -----------------------------------------

void Render_Wheel(int xt, int yt, int zt)
{
    glPushMatrix();
    glTranslatef(xt, yt, zt);
    glutSolidTorus(2, 5, 12, 36);
    glPopMatrix();
}

//-----------------------------------------   Draw_Car   -------------------------------------------

void Draw_Car(void)
{

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);

    glVertex3s(-40, 0, 15);
    glVertex3f(40, 0, 15);
    glVertex3f(40, -15, 15);
    glVertex3f(-40, -15, 15);
    glEnd();
    // left



    glBegin(GL_QUADS);
    glVertex3s(-40, 0, -15);
    glVertex3s(40, 0, -15);
    glVertex3s(40, -15, -15);
    glVertex3s(-40, -15, -15);
    glEnd();
    // right

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3s(40, 0, -15);
    glVertex3s(40, 0, 15);
    glVertex3s(40, -15, 15);
    glVertex3s(40, -15, -15);
    glEnd();
    // back

    glBegin(GL_QUADS);
    glVertex3s(-40, 0, -15);
    glVertex3s(-40, 0, 15);
    glVertex3s(-40, -15, 15);
    glVertex3s(-40, -15, -15);
    glEnd();
    // front


    glBegin(GL_QUADS);
    glVertex3s(-40, 0, 15);
    glVertex3s(-40, 0, -15);
    glVertex3s(40, 0, -15);
    glVertex3s(40, 0, 15);
    glEnd();
    // trunks

    glBegin(GL_QUADS);
    glVertex3s(-10, 10, 15);
    glVertex3s(-10, 10, -15);
    glVertex3s(20, 10, -15);
    glVertex3s(20, 10, 15);
    glEnd();
    // roof

    glBegin(GL_QUADS);
    glVertex3s(-20, 0, 15);
    glVertex3s(-10, 10, 15);
    glVertex3s(20, 10, 15);
    glVertex3s(25, 0, 15);
    glEnd();
    // window l


    glBegin(GL_QUADS);
    glVertex3s(-20, 0, -15);
    glVertex3s(-10, 10, -15);
    glVertex3s(20, 10, -15);
    glVertex3s(25, 0, -15);
    glEnd();
    // window r

    glColor3d(0, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3s(5, 0, 16);
    glVertex3s(5, 10, 16);
    glEnd();
    // between windows

    glBegin(GL_QUADS);
    glVertex3s(-5, -2, 16);
    glVertex3s(0, -2, 16);
    glVertex3s(0, -4, 16);
    glVertex3s(-5, -4, 16);
    glEnd();
    //door handle 1

    glBegin(GL_QUADS);
    glVertex3s(15, -2, 16);
    glVertex3s(20, -2, 16);
    glVertex3s(20, -4, 16);
    glVertex3s(15, -4, 16);
    glEnd();
    //door handle 2

    glBegin(GL_QUADS);
    glVertex3s(-10, 10, 15);
    glVertex3s(-20, 0, 15);
    glVertex3s(-20, 0, -15);
    glVertex3s(-10, 10, -15);
    glEnd();
    // windshield

    glBegin(GL_QUADS);
    glVertex3s(20, 10, 15);
    glVertex3s(20, 10, -15);
    glVertex3s(25, 0, -15);
    glVertex3s(25, 0, 15);
    glEnd();
    // rear window

    glBegin(GL_QUADS);

    glVertex3s(-40, -15, 15);
    glVertex3s(-40, -15, -15);
    glVertex3s(40, -15, -15);
    glVertex3s(40, -15, 15);
    glEnd();
    // Render wheels using torus's .

    glColor3f(0.3, 0.3, 0.3);
    Render_Wheel(-20, -15, 15);
    Render_Wheel(20, -15, 15);
    Render_Wheel(-20, -15, -15);
    Render_Wheel(20, -15, -15);

    glColor3d(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex3s(-39, -10, 16);
    glVertex3f(-35, -10, 16);
    glVertex3f(-35, -13, 16);
    glVertex3f(-39, -13, 16);
    glEnd();
    // car light
}

void stop()
{
    glBegin(GL_POLYGON);
    glColor3f(0.7254901, 0, 0.070588);
    glVertex3s(-80, 15, 15);
    glVertex3s(-90, 25, 15);
    glVertex3s(-90, 35, 15);
    glVertex3s(-80, 45, 15);
    glVertex3s(-70, 45, 15);
    glVertex3s(-60, 35, 15);
    glVertex3s(-60, 25, 15);
    glVertex3s(-70, 15, 15);
    glVertex3s(-80, 15, 15);
    glEnd();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture1);
    glColor3f(0.7254901, 0, 0.070588);
    glBegin(GL_QUADS);
    //glColor3d(1, 1, );
    glTexCoord2f(0, 0);
    glVertex3s(-85, 25, 16);
    glTexCoord2f(0, 1);
    glVertex3s(-85, 35, 16);
    glTexCoord2f(1, 1);
    glVertex3s(-65, 35, 16);
    glTexCoord2f(1, 0);
    glVertex3s(-65, 25, 16);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glColor3d(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3s(-73.5, 15, 16);
    glVertex3s(-76.5, 15, 16);
    glVertex3s(-76.5, -21, 16);
    glVertex3s(-73.5, -21, 16);
    glEnd();
}

//------------------------------------------   Display   ----------------------------------

void Display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambiant);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    light_position[0] = { lightX };
    light_position[1] = { lightY };
    light_position[2] = { lightZ };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambiant1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
    light_position1[0] = { lightX1 + xcr };
    light_position1[1] = { lightY1 };
    light_position1[2] = { lightZ1 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glShadeModel(GL_FLAT);
    gluPerspective(60.0, 1.0, 1.0, 10.0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);  // enable the z-buffer
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPushMatrix();
    glTranslatef(xtm, ytm, -4.0);       // Place objects between near and far clipping planes.
    glScalef(scl, scl, scl);       // Scale world relative to its origin.
    glScalef(0.02, 0.02, 0.02);
    stop();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    Draw2d();

    stop();
    glDisable(GL_LIGHT1);
    glTranslatef(-xcr, 0.0, 0.0);
    Draw_Car();
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHTING);
    //Draw_Tree();

    glPopMatrix();
    glDisable(GL_DEPTH_TEST); // disable the z-buffer
    glFlush();
    glutSwapBuffers();

}

//------------------------------------------   main   ----------------------------------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(800, 200);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CAR MOVING: ");
    Init();
    glutIdleFunc(play);
    glutKeyboardFunc(Keybord);
    glutReshapeFunc(reshapeFunc);
    glutDisplayFunc(Display);
    glutMotionFunc(Motion);
    glutSpecialFunc(special);

    glutMainLoop();                   // Enter the infinitely event-processing loop

    return (0);
}