#include "headers.h"
#include "classes.h"
#include "prototypes.h"

extern auto_ptr<Ring> ActiveRing;
extern Tower TowerA,TowerB,TowerC;
extern int RingStep,Count;
extern char * message;
extern bool Mute;
extern  bool Lock;
extern int Speed;
void WindowsSizeChangedEvent(int w, int h)
{

	GLfloat nRange = 100.0f;

	if(h == 0)
		h = 1;	

	//glMatrixMode(GL_MODELVIEW);



	glMatrixMode(GL_PROJECTION);

	
	glLoadIdentity();

	//// Establish clipping volume (left, right, bottom, Top, near, far)
    
	if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
	
	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SpecialKeyDownEvent(int key,int x,int y)
{
	if(!Lock)
	{
		switch(key)
		{
			case GLUT_KEY_F1: //Select TowerA
			
				SelectTower(TowerA);
				

			break;
			case GLUT_KEY_F2: //Select TowerB

				SelectTower(TowerB);


			break;
			case GLUT_KEY_F3: //Select TowerC

				SelectTower(TowerC);		

			break;
			case GLUT_KEY_PAGE_DOWN:
				if(Speed<30)
				{
					Speed+=5;
					message="Ring speed decreased";
					cout<<Speed<<endl;
				}
			break;
			case GLUT_KEY_PAGE_UP:
				if(Speed >1)
				{
					Speed-=5;
					message="Ring speed increased";
					cout<<Speed<<endl;
				}
			break;
			case GLUT_KEY_F11: //decreaase rings
				Count=Count-1>1 ? Count-1 : 1;
				message="one ring is decreased";
				
				InitializeTowers();
			break;
			case GLUT_KEY_F12: //increase rings
				if(Count<=10)
					Count++;
				message="one ring is increased";
				
				InitializeTowers();

				glutSwapBuffers();
			break;
			case GLUT_KEY_INSERT: //mutes
				if(Mute)
					Mute=false;
				else
					Mute=true;
				
			break;
			case GLUT_KEY_END:
				exit(0);
			break;
		}

	}
	else
	{
			cout<<"\n (!) It's locked\n";
			cout<<"Do you want to unlock it ? ";
			//if(getchar()=='y')
				//Lock=false;

			cout<<"\nIt's unlocked\n";
	}
}

