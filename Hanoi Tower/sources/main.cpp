#include "headers.h"
#include "classes.h"
#include "prototypes.h"

struct Deadlock
{
public:
	 bool Up;
	 bool Down;
	 bool Left;
	 bool Right;
};
struct Sound
{
public:
	 ALuint Popping;
	 ALuint Pushing;
	 ALuint Pushed;
};


#define AUTOPTR 0



  //const   auto_ptr<Tower> TowerA (new Tower);
 Tower TowerA;
 Tower TowerB;
 Tower TowerC;


auto_ptr<Tower> ActiveTower;

 auto_ptr<Ring> ActiveRing; //-> Active and detached ActiveRing

 int Count;
int RingStep=5;
int Speed=1;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
bool Mute=false;
 bool Lock=false;

char * message;


Deadlock deadlock;
AudioHelper audioHelper;
Sound sound;


#pragma region Initializations

int main(int argc, char* argv[])
{	

	
		sound.Popping=audioHelper.LoadSoundFile("Sounds/Popping.wav");
		sound.Pushing=audioHelper.LoadSoundFile("Sounds/Pushing.wav");
		sound.Pushed=audioHelper.LoadSoundFile("Sounds/Pushed.wav");

		Count=3;
		message="Welcome to Tower of Honoi\0";



		cout<<"Instructions \n"
			<<"\t Rules \n"
			<<"\t -------- \n"
			<<"\t 1) Each ring must be placed on the bigger ring \n"
			<<"\t 2) Rings must be moved from first tower into third tower \n"
			<<"\t 3) Only one ring can be moved at a time \n"
			<<endl
			<<"\t Keys \n"
			<<"\t -------- \n"
			<<"\t [F1] : Select first tower \n"
			<<"\t [F2] : Select second tower \n"
			<<"\t [F3] : Select third tower \n"
			<<"\t \n"
			<<"\t [Page Up] : Incrase the speed \n"
			<<"\t [Page Up] : Decrease the speed \n"
			<<"\t [F12] : Incrase rings \n"
			<<"\t [F11] : Decrease rings \n"
			<<"\t [End] : Exit \n"
			<<"\t [Ins] : Mute \n"
			;

		InitializeTowers();

		deadlock.Up=false;
		deadlock.Down=true;
		deadlock.Right=true;
		deadlock.Left=true;

	
		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

		glutInitWindowSize(800,600);
		glutCreateWindow("Tower of Honoi");
	
		InitializeScene();
		glutReshapeFunc(WindowsSizeChangedEvent);

	
		glutDisplayFunc(RenderScene);

		glutSpecialUpFunc(SpecialKeyDownEvent);

	
	glutMainLoop();
	

	return 0;
}

void InitializeTowers()
{

	
	TowerA.Name="TowerA";
	TowerB.Name="TowerB";
	TowerC.Name="TowerC";

	TowerA.RingStep=RingStep;

	TowerA.Position->X=-75;
	TowerA.Log=false;
	
	TowerB.Count=TowerC.Count=TowerA.Count=Count;


	TowerA.Initialize();
	TowerB.Size->Height=TowerA.Size->Height;
	TowerC.Size->Height=TowerA.Size->Height;
	

}
void InitializeScene()
{
	    // Light values and coordinates
	glClearColor(0.0,0.0,0.0,0.0);

    GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    glDisable(GL_CULL_FACE);		// Do not calculate inside of jet
		
	glEnable(GL_DEPTH_TEST);


    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
	
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // All materials hereafter have full specular reflectivity
    // with a high shine
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
    

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);

	
}
#pragma endregion



#pragma region Controls
void SwapRings()
{
	
	if(ActiveRing.get()!=NULL && ActiveRing->isFloat) // && ActiveRing->state==State::Detached
	{
		glutTimerFunc(Speed,Animate,60);	
	}
	else
	{
		if(!ActiveTower->empty() && ActiveRing.get()==NULL) //first time
		{

			ActiveRing.reset(new Ring(ActiveTower->Top()));  
			

			glutTimerFunc(Speed,Animate,60);
		}
		else
		{
			message="Selected Tower is empty";
			Lock=false;
		}
	}
}

void SelectTower(Tower & tower)
{
		//ActiveTower.release();
		//ActiveTower.reset(tower);
		ActiveTower.release();
		
		//ActiveTower.release(); //WTF !? O_o It's Essential !

		ActiveTower.reset(&tower);

		message=ActiveTower->Name;
				
		Lock=true;
		SwapRings();
		glutPostRedisplay();
}

void Animate(int value)
{
	glPushMatrix();

#pragma region Up
		
	if(deadlock.Up ==false)
	{
		if(ActiveTower->empty())
		{
			Lock=false;
			return;
		}
		else if(ActiveTower->Size->Height > ActiveRing->Position->Y)
		{
			ActiveRing->MoveUp();
			if(!Mute)
				audioHelper.Play(sound.Popping,FALSE);
		}
		else if(ActiveTower->Size->Height <= ActiveRing->Position->Y)
		{
			
			
			ActiveTower->pop(); // the ActiveRing is detached and animation is completed
			ActiveRing->isFloat=true;
		
		//	ActiveRing->state=Detached;
			//ActiveRing->isFloat=true;
			

			deadlock.Up=true;
			deadlock.Down=false;

			deadlock.Right=false;
			deadlock.Left=true;

			Lock=false;
			return;
		}
	}

			
#pragma endregion

#pragma region Left & Right
	if(ActiveTower.get()==&TowerC)
	{
		if(TowerC.Position->X>ActiveRing->Position->X)
		{
			deadlock.Down=true;
			ActiveRing->MoveRight();
		}
		else
		{
			deadlock.Down=false;
		}
	}
	else if(ActiveTower.get()==&TowerA)
	{
		if(TowerA.Position->X<ActiveRing->Position->X)
		{
			deadlock.Down=true;
			ActiveRing->MoveLeft();
		}
		else
		{
			deadlock.Down=false;
		}
	}
	else if(ActiveTower.get()==&TowerB)
	{
			if(ActiveRing->Position->X != TowerC.Position->X && !deadlock.Right) //goes left
			{
				if(TowerB.Position->X >= ActiveRing->Position->X+5)
				{
					deadlock.Down=true;
					deadlock.Left=true;
					ActiveRing->MoveRight();
				}
				else
				{
					deadlock.Down=false;
				}
		
			}
			else if(ActiveRing->Position->X <= TowerC.Position->X || !deadlock.Left) // ActiveRing wasn't at TowerA
			{
				if(TowerB.Position->X<=ActiveRing->Position->X-5)
				{
					deadlock.Down=true;
					deadlock.Right=true;
					ActiveRing->MoveLeft();
				}
				else
				{
					deadlock.Down=false;
				}
			}
		
		
	}	
		
#pragma endregion

#pragma region Down

			if(deadlock.Up && !deadlock.Down) //push 
			{
					if(!ActiveTower->empty() && ActiveTower->Top().Value<ActiveRing->Value ) //checks if the ActiveRing is smaller than the toppest ActiveRing in the tower
					{
						message="bigger rings cannot be put on smaller rings";
						
						Lock=false;
						return;

						glutPostRedisplay();
					}
					if(!ActiveTower->empty() && ActiveRing->Position->Y > ActiveTower->Top().Position->Y+10)
					{
						ActiveRing->MoveDown();
						if(!Mute){
							audioHelper.Play(sound.Pushing,FALSE);
						}
					}
					else if (ActiveTower->empty() && ActiveTower->Position->Y<ActiveRing->Position->Y+25) // no idea what is that 25 ......
					{
						ActiveRing->MoveDown();
						
						if(!Mute){
							audioHelper.Play(sound.Pushing,FALSE);
						}
					}
					else 
					{
						
						//ActiveRing->state=Attached;
						deadlock.Up=false;
						deadlock.Right=true;
						deadlock.Left=true;
						deadlock.Down=true;
						
						ActiveRing->isFloat=false;
						ActiveTower->push(*ActiveRing);
						ActiveRing.reset(NULL);

//						delete ActiveRing;

						//ActiveRing.release();
						//ActiveRing.reset(NULL);

						if(!Mute){
							audioHelper.Play(sound.Pushed,FALSE);
						}
						
					
						Lock=false;

						return;

					}
				
			}

#pragma endregion



	glPopMatrix();
	glutPostRedisplay();
	glutTimerFunc(Speed,Animate,value);
}
void SolveTower()
{

	
}

#pragma endregion