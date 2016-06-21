#include <glut.h>
#include <math.h>

void Display();
void Anim();

//##################################################
// USE A & D KEYS TO MOVE LEFT AND RIGHT RESPECTIVELY
//##################################################
void Key(unsigned char key, int x, int y);
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
void handleRight();
void handleLeft();

double speed = 0.0003;
double speed_multiplier = 2.0;


//##########################################
//Summation of these variable gets the score
//##########################################
int object1 = 0;
int object2 = 0;
int object3 = 0;
int object4 = 0;
int object5 = 0;

int floorColor = 0;
int lost = 0;

void drawFloor() {
  glPushMatrix();
  glBegin(GL_QUADS);
  if (floorColor == 0){
	glColor3f(1.0f, 1.0f, 1.0f);
  }else{
	glColor3f(1.0f, 0.0f, 0.0f);
  }
  glVertex3f((float)-13, -1.5, (float)-12);
  glVertex3f((float)-13, -1.5, (float)12);
  glVertex3f(13, -1.5, 12);
  glVertex3f(13, -1.5, -12);
  glEnd();
  glPopMatrix();
}

void drawSphere(float x, float y, float z, float r, float g, float b,
                float radius) {
  glPushMatrix();
  glTranslated(x, y, z);
  glColor3f(r, g, b);
  glutSolidSphere(radius, 10, 10);
  glPopMatrix();
}
void Display() {



  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.0f, 800 / 800, 0.01f, 300.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(object1 == 0){
	drawSphere(-2, -1, 1, 0, 0, 1, 0.1);
  }
  if(object2 == 0){
	drawSphere(-3, -1, 0, 0, 0, 1, 0.1);
  }
  if(object3 == 0){
	drawSphere(-3, -1, 2, 0, 0, 1, 0.1);
  }
  if(object4 == 0){
	drawSphere(-2, -1, 3, 0, 0, 1, 0.1);
  }
  if(object5 == 0){
	drawSphere(-1, -1, -2, 0, 0, 1, 0.1);
  }
  if(lost == 0){
	drawSphere(-2, -1, -2, 1, 0, 0, 0.1);
  }
  drawFloor();
  glFlush();
}

// Anim method here
void Anim() {
  //#############################################
  // MOVEMENT CODE START - DO NOT TOUCH THIS CODE
  //#############################################
	if(lost == 0){
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
		  floorColor = 1;
		  lost = 1;
	  }
	}
  glutPostRedisplay();
}

//####
// MAIN
//####
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(250, 250);
  glutCreateWindow("Maze");

  glutDisplayFunc(Display);
  glutIdleFunc(Anim);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glutKeyboardFunc(Key);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHTING);

  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_SMOOTH);

  glutMainLoop();
}
//###########################################
// KEY BOARD FUNCTION - DO NOT TOUCH THIS CODE
//###########################################
void Key(unsigned char key, int x, int y) {
  if (key == 'd' || key == 'D' || key == GLUT_KEY_RIGHT) {
    handleRight();
  }
  if (key == 'a' || key == 'A') {
    handleLeft();
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
