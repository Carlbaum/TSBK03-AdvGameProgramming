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

#include <math.h>

// L�gg till egna globaler h�r efter behov.
int number_of_sprites;
float cohesian_distance = 200.f;
float separation_distance = 150.f;
float kCohesionWeight = 0.005f;
float kAvoidanceWeight = 0.005f;
float kAlignmentWeight = 0.01f;

float vec2Norm(FPoint p1) {
  return sqrt(p1.h * p1.h + p1.v * p1.v);
}

FPoint vec2Scale(FPoint vec, float factor) {
  vec.h *= factor;
  vec.v *= factor;
  return vec;
}

FPoint vec2Normalize(FPoint p1) {
  return vec2Scale(p1,vec2Norm(p1) == 0.0f ? 1.f : 1.f/vec2Norm(p1));
}

FPoint vec2Add(FPoint p1, FPoint p2) {
  p1.h += p2.h;
  p1.v += p2.v;
  return p1;
}

FPoint vec2Sub(FPoint p1, FPoint p2) {
  p1.h -= p2.h;
  p1.v -= p2.v;
  return p1;
}

float distance(FPoint p1, FPoint p2 ) {
	return vec2Norm(vec2Sub(p1,p2));
}

FPoint vec2SetAll(float val) {
  FPoint v;
  v.h = val;
  v.v = val;
  return v;
}

void vec2Print(FPoint v) {
  printf("(%f,%f)\n",v.h,v.v );
}

void SpriteBehavior() // Din kod!
{
// L�gg till din labbkod h�r. Det g�r bra att �ndra var som helst i
// koden i �vrigt, men mycket kan samlas h�r. Du kan utg� fr�n den
// globala listroten, gSpriteRoot, f�r att kontrollera alla sprites
// hastigheter och positioner, eller arbeta fr�n egna globaler.

// Flocking
// Step 1: Cohesion - DONE!
// Step 2: Separation - DONE!
// Step 3: Alignment - IN PROGRESS!
// Step 4: Noise & Personality - NOT STARTED!
  SpritePtr current = gSpriteRoot;
  FPoint cohesion_direction[number_of_sprites];
  FPoint separation_direction[number_of_sprites];
  // FPoint speed_difference[number_of_sprites];
  int idx = 0;
  while (current != NULL) {
    int count_neighbours = 0;
    FPoint cp = current->position;
    FPoint gathering_direction = {0.f,0.f};
    separation_direction[idx] = vec2SetAll(0.0f);

    SpritePtr other = gSpriteRoot;
    while (other != NULL) {
      // Don't compare one boid with itself
      if ( current == other ) {
        other = other->next;
        continue;
      }

      FPoint op = other->position;
			FPoint offset = vec2Sub(op,cp);
      float dist = vec2Norm(offset);
			// if the boid senses another one within a radius=cohesian_distance
      if ( dist < cohesian_distance ) {
        gathering_direction = vec2Add(gathering_direction, offset);
        if ( dist < separation_distance) {
          separation_direction[idx] = vec2Add(separation_direction[idx],vec2Scale(vec2Normalize(vec2Scale(offset,-1.f)),separation_distance-dist));
        }
        // speed_difference[idx] = vec2Sub(other->speed, current->speed);
        count_neighbours++;
      }
      other = other->next;
    }

    // take the averages
    if ( count_neighbours > 0 ) {
      // speed_difference[idx] = vec2Scale(speed_difference[idx],1.0f/count_neighbours);
      cohesion_direction[idx] = vec2Scale(gathering_direction, 1.0f/count_neighbours);
      separation_direction[idx] = vec2Scale(separation_direction[idx], 1.0f/count_neighbours);
    } else { //no neighbours found => no contribution to speed
      cohesion_direction[idx] = vec2SetAll(0.0f);
      separation_direction[idx] = vec2SetAll(0.0f);
    }

		current = current->next;
    idx++;
	}

  current = gSpriteRoot;
  idx = 0;
  while (current != NULL) {
    FPoint new_speed = vec2Add(/*vec2Add(vec2Scale(speed_difference[idx], kAlignmentWeight), */
                        vec2Scale(cohesion_direction[idx], kCohesionWeight)/*)*/,
                        vec2Scale(separation_direction[idx], kAvoidanceWeight));
    current->speed = vec2Add(new_speed,current->speed);
    idx++;
    current = current->next;
  }
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
    case '.':
    	kCohesionWeight += 0.001;
    	printf("kCohesionWeight = %f\n", kCohesionWeight);
    	break;
    case ',':
    	kCohesionWeight -= 0.001;
    	printf("kCohesionWeight = %f\n", kCohesionWeight);
    	break;
    case 'l':
    	kAvoidanceWeight += 0.001;
    	printf("kAvoidanceWeight = %f\n", kAvoidanceWeight);
    	break;
    case 'k':
    	kAvoidanceWeight -= 0.001;
    	printf("kAvoidanceWeight = %f\n", kAvoidanceWeight);
    	break;
    case 'o':
    	kAlignmentWeight += 0.001;
    	printf("kAlignmentWeight = %f\n", kAlignmentWeight);
    	break;
    case 'i':
    	kAlignmentWeight -= 0.001;
    	printf("kAlignmentWeight = %f\n", kAlignmentWeight);
    	break;
    case 'm':
    	cohesian_distance += 5;
    	printf("cohesian_distance = %f\n", cohesian_distance);
    	break;
    case 'n':
    	cohesian_distance -= 5;
    	printf("cohesian_distance = %f\n", cohesian_distance);
    	break;
    case 'j':
    	separation_distance += 5;
    	printf("separation_distance = %f\n", separation_distance);
    	break;
    case 'h':
    	separation_distance -= 5;
    	printf("separation_distance = %f\n", separation_distance);
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

  NewSprite(sheepFace, 350.f, 300.f, -1.f, 0.1f);
	NewSprite(sheepFace, 450.f, 300.f, 1.f, -0.1f);
	NewSprite(sheepFace, 400.f, 350.f, -0.1f, 1.f);
	NewSprite(sheepFace, 400.f, 250.f, 0.1f, -1.f);
  // NewSprite(foodFace, 550, 300, 1, 1.0);
  // NewSprite(dogFace, 700, 500, -1, 0.1);
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
