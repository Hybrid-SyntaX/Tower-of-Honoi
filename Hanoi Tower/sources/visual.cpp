#include "headers.h"
#include "classes.h"
#include "prototypes.h"

extern auto_ptr<Ring> ActiveRing;
extern Tower TowerA,TowerB,TowerC;
extern int RingStep;
void RenderString(float x, float y, void *font, char *stActiveRing) 
{  
  char *c;
  glColor3f(1.0,1.0,1.0);
  glRasterPos2f(x,y);
  for (c=stActiveRing; *c != '\0'; c++) 
  {
    glutBitmapCharacter(font, *c);
	
  }
}


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(255,255,255);
	//RenderString(0, 90, GLUT_BITMAP_TIMES_ROMAN_24,message);

	//Texture.End
	if(ActiveRing.get()!=NULL && ActiveRing.get()->isFloat)
	{
		ActiveRing->Render();
	}

	RenderTowers();

	

	glutSwapBuffers();
}

void RenderTowers()
{


	glPushMatrix();

		TowerA.RingStep=RingStep;
		TowerA.Render();
		TowerA.RenderRings();

		TowerB.Position->Y=TowerA.Position->Y;
		TowerB.Position->Z=TowerA.Position->Z;
		TowerB.Position->X=TowerA.Position->X+TowerA.Size->Width*15;
		
		TowerC.Position->Y=TowerA.Position->Y;
		TowerC.Position->Z=TowerA.Position->Z;
		TowerC.Position->X=TowerB.Position->X+TowerB.Size->Width*15;

		TowerB.Render();
		TowerB.RenderRings();


		TowerC.Render();
		TowerC.RenderRings();

		//glTranslatef(0,0,0);
	glPopMatrix();

}