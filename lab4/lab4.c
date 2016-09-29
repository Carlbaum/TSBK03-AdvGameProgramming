// Demo of heavily simplified sprite engine
// by Ingemar Ragnemalm 2009
// used as base for lab 4 in TSBK03.
// OpenGL 3 conversion 2013.

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
	// uses framework Cocoa
#else
	#include <GL/gl.h>
	#include "MicroGlut.h"
#endif

#include <stdlib.h>
#include "LoadTGA.h"
#include "SpriteLight.h"
#include "GL_utilities.h"

// L�gg till egna globaler h�r efter behov.
int number_of_sprites;
float kCohesionWeight = 0.0005f;
float kAlignmentWeight = 0.01f;

float distance(FPoint p1, FPoint p2 ) {
	return sqrt(pow(p1.h - p2.h, 2) + pow(p1.v - p2.v, 2));
}

FPoint vec2Sub(FPoint p1, FPoint p2) {
  FPoint diff;
  diff.h = p1.h-p2.h;
  diff.v = p1.v-p2.v;
  return diff;
}


void SpriteBehavior() // Din kod!
{
// L�gg till din labbkod h�r. Det g�r bra att �ndra var som helst i
// koden i �vrigt, men mycket kan samlas h�r. Du kan utg� fr�n den
// globala listroten, gSpriteRoot, f�r att kontrollera alla sprites
// hastigheter och positioner, eller arbeta fr�n egna globaler.

// 1. Flocking steg 1: Cohesion
// Sök alla varelser inom visst avstånd, beräkna tyngdpunkt, gå mot denna.
  SpritePtr current = gSpriteRoot;
  //center_of_mass will eventually store the offset from one boids' position to a mass center
  FPoint center_of_mass[number_of_sprites];
  // FPoint speed_difference[number_of_sprites];
  int idx = 0;
  do {
    int count = 0;
    center_of_mass[idx].h = 0;
    center_of_mass[idx].v = 0;

    SpritePtr other = gSpriteRoot;
    do {
      if ( current == other ) {
        other = other->next;
        continue;
      }
      if ( distance(current->position, other->position) < 200 ) {
        center_of_mass[idx].h += other->position.h;
        center_of_mass[idx].v += other->position.v;
        // speed_difference[idx] = vec2Sub(other->speed, current->speed);
        count++;
      }
      other = other->next;
    } while (other != NULL);

    if ( count > 0 ) {
      // speed_difference[idx].h /= count;
      // speed_difference[idx].v /= count;
      center_of_mass[idx].h /= count;
      center_of_mass[idx].v /= count;
    } else {
      center_of_mass[idx].h = current->position.h;
      center_of_mass[idx].v = current->position.v;
    }

    //make center_of_mass store the local offset instead of world coord
    center_of_mass[idx].h = center_of_mass[idx].h - current->position.h;
    center_of_mass[idx].v = center_of_mass[idx].v - current->position.v;
    current = current->next;
    idx++;

    printf("%d's neighbours: %d\n",idx,count);
    printf("%d's avg. posit: %f,%f\n",idx,center_of_mass[idx].h,center_of_mass[idx].v);
  } while (current != NULL);

  current = gSpriteRoot;
  idx = 0;
  do {
    current->speed.h += /*speed_difference[idx].h*kAlignmentWeight + */center_of_mass[idx].h * kCohesionWeight;
    current->speed.v += /*speed_difference[idx].v*kAlignmentWeight + */center_of_mass[idx].v * kCohesionWeight;
    printf("%d current->speed = %f,%f\n",idx,current->speed.h,current->speed.v );
    idx++;
    current = current->next;
  } while (current != NULL);
}

// Drawing routine
void Display()
{
	SpritePtr sp;

	glClearColor(0, 0, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	DrawBackground();

	SpriteBehavior(); // Din kod!

// Loop though all sprites. (Several loops in real engine.)
	sp = gSpriteRoot;
	do
	{
		HandleSprite(sp); // Callback in a real engine
		DrawSprite(sp);
		sp = sp->next;
	} while (sp != NULL);

	glutSwapBuffers();
}

void Reshape(int h, int v)
{
	glViewport(0, 0, h, v);
	gWidth = h;
	gHeight = v;
}

void Timer(int value)
{
	glutTimerFunc(20, Timer, 0);
	glutPostRedisplay();
}

// Example of user controllable parameter
float someValue = 0.0;

void Key(unsigned char key,
         __attribute__((unused)) int x,
         __attribute__((unused)) int y)
{
  switch (key)
  {
    case '+':
    	someValue += 0.1;
    	printf("someValue = %f\n", someValue);
    	break;
    case '-':
    	someValue -= 0.1;
    	printf("someValue = %f\n", someValue);
    	break;
    case 0x1b:
      exit(0);
  }
}

void Init()
{
	TextureData *sheepFace, *blackFace, *dogFace, *foodFace;

	LoadTGATextureSimple("bilder/leaves.tga", &backgroundTexID); // Bakgrund

	sheepFace = GetFace("bilder/sheep.tga"); // Ett f�r
	blackFace = GetFace("bilder/blackie.tga"); // Ett svart f�r
	dogFace = GetFace("bilder/dog.tga"); // En hund
	foodFace = GetFace("bilder/mat.tga"); // Mat

  NewSprite(blackFace, 150, 150, -1, 1.5);
	NewSprite(sheepFace, 100, 200, 1, 1);
	NewSprite(sheepFace, 200, 100, 1.5, -1);
	NewSprite(sheepFace, 600, 200, -1, 1.5);
  NewSprite(foodFace, 550, 300, 1, 1.0);
  NewSprite(dogFace, 700, 500, -1, 0.1);
  SpritePtr temp = gSpriteRoot;
  int counter = 0;
  do {
    temp = temp->next;
    counter++;
  } while ( temp != NULL );
  number_of_sprites = counter;
  printf("Number of Sprites = %d\n",number_of_sprites);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitContextVersion(3, 2);
	glutCreateWindow("SpriteLight demo / Flocking");

	glutDisplayFunc(Display);
	glutTimerFunc(20, Timer, 0); // Should match the screen synch
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);

	InitSpriteLight();
	Init();

	glutMainLoop();
	return 0;
}
