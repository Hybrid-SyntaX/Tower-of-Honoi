#include "Ring.h"


Ring::Ring()
{

	this->Size->Height=5;
	this->Size->Width=10;
	this->Position->Offset=1;
	this->isFloat=false;
	std::cout<<"Ring @ "<<this <<" Is created"<<endl;
}

Ring& Ring::operator=(const Ring & ring) {
	if (this == &ring)
		return *this;  
}
Ring::~Ring(void)
{	
	std::cout<<"Ring @ "<<this <<" Is destroyed"<<endl;
}

Ring::Ring(const Ring& ring)
{
	
	this->Color=ring.Color;
//	this->Color.reset(ring.Color.get());
	this->Position.reset(ring.Position.get());
	this->Size.reset(ring.Size.get());
//	this->Texture.reset(ring.Texture.get());
	this->Texture=ring.Texture;
	

	this->isFloat=ring.isFloat;
	this->Offset=ring.Offset;
	this->Value=ring.Value;
	this->state=ring.state;
	this->Tag=ring.Tag;
	
}

void Ring::RenderAt(float X,float Y,float Z)
{
	
	glPushMatrix();
		
		this->Color->Render();

		this->Position->MoveTo(X,Y,Z);
		this->Position->RotateAround(90,'x');

		Texture.BindTexture("Textures/wood.tga");

//Torus.Start
		GLfloat majorRadius=this->Size->Width;
		GLfloat minorRadius=this->Size->Height;
		GLint numMajor=30;
		GLint numMinor=37;
		float vNormal[3];
			
    double majorStep = 2.0f*3.14159265358979323846 / numMajor;
    double minorStep = 2.0f*3.14159265358979323846 / numMinor;
    int i, j;
	
    for (i=0; i<numMajor; ++i) 
		{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		GLfloat x0 = (GLfloat) cos(a0);
		GLfloat y0 = (GLfloat) sin(a0);
		GLfloat x1 = (GLfloat) cos(a1);
		GLfloat y1 = (GLfloat) sin(a1);
		
		glBegin(GL_TRIANGLE_STRIP);
		for (j=0; j<=numMinor; ++j) 
			{
			double b = j * minorStep;
			GLfloat c = (GLfloat) cos(b);
			GLfloat r = minorRadius * c + majorRadius;
			GLfloat z = minorRadius * (GLfloat) sin(b);
			
			// First point
			glTexCoord2f((float)(i)/(float)(numMajor), (float)(j)/(float)(numMinor));
			vNormal[0] = x0*c;
			vNormal[1] = y0*c;
			vNormal[2] = z/minorRadius;
			glNormal3fv(vNormal);
			glVertex3f(x0*r, y0*r, z);
			
			glTexCoord2f((float)(i+1)/(float)(numMajor), (float)(j)/(float)(numMinor));
			vNormal[0] = x1*c;
			vNormal[1] = y1*c;
			vNormal[2] = z/minorRadius;
			glNormal3fv(vNormal);
			glVertex3f(x1*r, y1*r, z);
			}
		glEnd();
		}

//Torus.End
	glPopMatrix();
}
void Ring::Render(void)
{
	this->RenderAt(this->Position->X,this->Position->Y,this->Position->Z);
}
Ring * Ring::Clone()
{
	return new Ring(*this); //works fine
}
void Ring::Log()
{
	cout<<"&Ring"<<this->Value<<"= "<<this<<endl;
}
#pragma region Animation

void Ring::MoveUp()
{
	glPushMatrix();
		this->Position->Y+=this->Position->Offset;
		this->Position->MoveTo(this->Position->X,this->Position->Y,this->Position->Z);
	glPopMatrix();
}
void Ring::MoveDown()
{
	glPushMatrix();
		this->Position->Y-=this->Position->Offset;
		this->Position->MoveTo(this->Position->X,this->Position->Y,this->Position->Z);
	glPopMatrix();
}
void Ring::MoveLeft()
{
	glPushMatrix();
		this->Position->X-=this->Position->Offset;
		this->Position->MoveTo(this->Position->X,this->Position->Y,this->Position->Z);
	glPopMatrix();
}
void Ring::MoveRight()
{
	glPushMatrix();
		this->Position->X+=this->Position->Offset;
		this->Position->MoveTo(this->Position->X,this->Position->Y,this->Position->Z);
	glPopMatrix();
}
#pragma endregion