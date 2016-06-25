#include "stdafx.h"
#include "TextureBuilder.h"
#include <glut.h>
#include <string.h>
#include <math.h>

using namespace std;

void Display();
void Anim();
void Key(unsigned char key, int x, int y); 
void handleRight();
void handleLeft();

int sign = 0;
char dir1 = ' ';
int dir2 = 0;

double eyeX = 2.0;
double eyeY = -1.0;
double eyeZ = 1.0;

double centerX = -8.0;
double centerY = -1.0;
double centerZ = 1.0;

double temp = 0.0;
int direction = 0;
int stop_walking = 0;
double temp_center = 0.0;
double temp_eye = 0.0;

double speed = 0.0003;
double speed_multiplier = 2.0;

//Summation of these variable gets the score
int object1 = 0;
int object2 = 0;
int object3 = 0;
int object4 = 0;
int object5 = 0;

//int floorColor = 0;
int lost = 0;

bool gameIntro = true;
bool gameStart = false;
bool gameEnd = false; 
int score = 0;
string endOfGameMessage = "";

void printText(int x, int y, string text)
{
  glRasterPos2i(x,y);
  for (int i=0; i<text.size(); i++)
  {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
  }
}

void drawFloor() {
  glPushMatrix();
  GLuint texture = LoadTexture("grass-image.bmp", 275, 183, false);
  glEnable(GL_TEXTURE_2D);    
  glBindTexture(GL_TEXTURE_2D, texture);
  glEnable(GL_CULL_FACE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);  // Set quad normal direction.
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f((float)-13, -1.5, (float)-12);
  glTexCoord2f(0.0f, 5.0f);
  glVertex3f((float)-13, -1.5, (float)12);
  glTexCoord2f(5.0f, 5.0f);
  glVertex3f(13, -1.5, 12);
  glTexCoord2f(5.0f, 0.0f);
  glVertex3f(13, -1.5, -12);
  glEnd();

  glDisable(GL_TEXTURE_2D); 
  glPopMatrix();
}

void drawSphere(float x, float y, float z, float r, float g, float b, float radius) {
  glPushMatrix();
  glTranslated(x, y, z);
  glColor3f(r, g, b);
  glutSolidSphere(radius, 10, 10);
  glPopMatrix();
}

void drawTexturedObject(float x, float y, float z, float radius, const char * textureFile, int textureWidth, int textureHeight) {

  glPushMatrix();
  glTranslated(x, y, z);
  glRotated(90, 1, 0, 0);

  GLuint texture = LoadTexture(textureFile, textureWidth, textureHeight, false);
  GLUquadricObj* rockObject = gluNewQuadric();    
  gluQuadricTexture(rockObject, true);
  gluQuadricNormals(rockObject, GLU_SMOOTH);
  glEnable(GL_TEXTURE_2D);    
  glBindTexture(GL_TEXTURE_2D, texture);
  glEnable(GL_CULL_FACE);
  gluSphere(rockObject, radius, 10, 10);
  gluDeleteQuadric(rockObject);

  glPopMatrix();
}

void Display() {
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0f, 800 / 800, 0.01f, 300.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);

  if(gameIntro) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,1.0f,0.75f,0.0f);
    glPushMatrix();
    glTranslatef(-10.0f,0.0f,0.0f);
    printText(0,0,"Press on 's' key to start :D");
    glPopMatrix();
  }

  if(gameStart) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    if(object1 == 0){
      drawTexturedObject(-2, -1, 1, 0.1, "watermellon-image.bmp", 130, 130);
    }
    if(object2 == 0){
      drawTexturedObject(-3, -1, 0, 0.1, "watermellon-image.bmp", 130, 130);
    }
    if(object3 == 0){
      drawTexturedObject(-3, -1, 2, 0.1, "watermellon-image.bmp", 130, 130);
    }
    if(object4 == 0){
      drawTexturedObject(-2, -1, 3, 0.1, "watermellon-image.bmp", 130, 130);
    }
    if(object5 == 0){
      drawTexturedObject(-1, -1, -2, 0.1, "watermellon-image.bmp", 130, 130);
    }
    if(lost == 0){
      drawTexturedObject(-2, -1, -2, 0.1, "rock-image.ppm", 259, 194);
    }
    drawFloor();
  }

  score = object1 + object2 + object3 + object4 + object5;

  if(gameEnd) {
    if (score == 5) {
      endOfGameMessage = "Awesome! You won with score: " + to_string(score);
    } else {
      endOfGameMessage = "Game Over! Your score is: " + to_string(score);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f,1.0f,0.75f,0.0f);
    glPushMatrix();
    glTranslatef(-10,0,0);
    printText(0,0,endOfGameMessage);
    glPopMatrix();
  }
  glFlush();
}

// Anim method here
//#############################################
// MOVEMENT CODE START - DO NOT TOUCH THIS CODE
//#############################################
void Anim() {
  if(lost == 0 && gameStart){
    if (stop_walking == 0) {
      switch (direction) {
        case 0:
        centerX -= speed * speed_multiplier;
        eyeX -= speed * speed_multiplier;
        break;
        case 1:
        centerZ -= speed * speed_multiplier;
        eyeZ -= speed * speed_multiplier;
        break;
        case 2:
        centerX += speed * speed_multiplier;
        eyeX += speed * speed_multiplier;
        break;
        case 3:
        centerZ += speed * speed_multiplier;
        eyeZ += speed * speed_multiplier;
        break;
      }
    } else {
      if (sign == 1 && dir1 == 'x') {
        centerX += 0.01 * speed_multiplier;
        if (dir2 == 1) {
          centerZ -= 0.01 * speed_multiplier;
        } else {
          centerZ += 0.01 * speed_multiplier;
        }
        if (centerX >= eyeX + 10) {
          stop_walking = 0;
          centerX = eyeX + 10;
          centerZ = eyeZ;
        }
      } else {
        if (sign == -1 && dir1 == 'x') {
          centerX -= 0.01 * speed_multiplier;
          if (dir2 == 1) {
            centerZ += 0.01 * speed_multiplier;
          } else {
            centerZ -= 0.01 * speed_multiplier;
          }
          if (centerX <= eyeX - 10) {
            stop_walking = 0;
            centerX = eyeX - 10;
            centerZ = eyeZ;
          }
        } else {
        if (sign == 1 && dir1 == 'z') {
          centerZ += 0.01 * speed_multiplier;
          if (dir2 == 1) {
            centerX += 0.01 * speed_multiplier;
          } else {
            centerX -= 0.01 * speed_multiplier;
          }
          if (centerZ >= eyeZ + 10) {
            stop_walking = 0;
            centerZ = eyeZ + 10;
            centerX = eyeX;
          }
        } else {
          if (sign == -1 && dir1 == 'z') {
            centerZ -= 0.01 * speed_multiplier;
            if (dir2 == 1) {
              centerX -= 0.01 * speed_multiplier;
            } else {
              centerX += 0.01 * speed_multiplier;
            }
            if (centerZ <= eyeZ - 10) {
              stop_walking = 0;
              centerZ = eyeZ - 10;
              centerX = eyeX;
            }
          }
        }
        }
      }
    }
    //##################
    // MOVEMENT CODE END
    //##################

    if(eyeX >= -2.1 && eyeX <= -1.9 && eyeZ >= 0.9 && eyeZ <= 1.1){
      object1 = 1;
    }
    if(eyeX >= -3.1 && eyeX <= -2.9 && eyeZ >= -0.1 && eyeZ <= 0.1){
      object2 = 1;
    }
    if(eyeX >= -3.1 && eyeX <= -2.9 && eyeZ >= 1.9 && eyeZ <= 2.1){
      object3 = 1;
    }
    if(eyeX >= -2.1 && eyeX <= -1.9 && eyeZ >= 2.9 && eyeZ <= 3.1){
      object4 = 1;
    }
    if(eyeX >= -1.1 && eyeX <= -0.9 && eyeZ >= -2.1 && eyeZ <= -1.9){
      object5 = 1;
    }
    if(eyeX >= -2.1 && eyeX <= -1.9 && eyeZ >= -2.1 && eyeZ <= -1.9){
      //floorColor = 1;
      //lost = 1;
      gameStart = false;
      gameEnd = true;
    }
  }

  if(score == 5 || lost == 1) {
    gameStart = false;
    gameEnd = true;
  }
  
  glutPostRedisplay();
}

//###########################################
// KEY BOARD FUNCTION - DO NOT TOUCH THIS CODE
// --
// USE A & D KEYS TO MOVE LEFT AND RIGHT RESPECTIVELY
//###########################################
void Key(unsigned char key, int x, int y) {
  if (key == 'd' || key == 'D' || key == GLUT_KEY_RIGHT) {
    handleRight();
  }
  if (key == 'a' || key == 'A') {
    handleLeft();
  }
  if (key == 27) { // escape key
  exit(0);
  }
  if (key == 's' ) {
    gameIntro = false;
    gameStart = true;
  }
  glutPostRedisplay();
}

//#############################################
// KEYBOARD HELPER FUNCTIONS - DO NOT TOUCH ALSO
//#############################################
void handleRight() {
  switch (direction) {
    case 0:
      stop_walking = 1;
      sign = -1;
      dir1 = 'z';
      dir2 = 0;
      direction = 1;
      break;
    case 1:
      stop_walking = 1;
      sign = 1;
      dir1 = 'x';
      dir2 = 0;
      direction = 2;
      break;
    case 2:
      stop_walking = 1;
      sign = 1;
      dir1 = 'z';
      dir2 = 0;
      direction = 3;
      break;
    case 3:
      stop_walking = 1;
      sign = -1;
      dir1 = 'x';
      dir2 = 0;
      direction = 0;
      break;
  }
}

void handleLeft() {
  switch (direction) {
    case 0:
      stop_walking = 1;
      sign = 1;
      dir1 = 'z';
      dir2 = 1;
      direction = 3;
      break;
    case 1:
      stop_walking = 1;
      sign = -1;
      dir1 = 'x';
      dir2 = 1;
      direction = 0;
      break;
    case 2:
      stop_walking = 1;
      sign = -1;
      dir1 = 'z';
      dir2 = 1;
      direction = 1;
      break;
    case 3:
      stop_walking = 1;
      sign = 1;
      dir1 = 'x';
      dir2 = 1;
      direction = 2;
      break;
  }
}
//#############################
// KEYBOARD HELPER FUNCTIONS END
//#############################

//####
// MAIN
//####
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(250, 250);
  glutCreateWindow("Maze | Computer Graphics 2016");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_SMOOTH);

  glutDisplayFunc(Display);
  glutIdleFunc(Anim);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutKeyboardFunc(Key);

  glutMainLoop();
}
