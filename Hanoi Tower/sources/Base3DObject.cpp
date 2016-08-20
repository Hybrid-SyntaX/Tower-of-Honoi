#include "Base3DObject.h"


Base3DObject::Base3DObject(void)
{
	Color=new _Color();
//	Color=_Color();
	//Color=new _Color();
	//Texture=auto_ptr<_Texture>(new _Texture);
	//Color=auto_ptr<_Color>(new _Color());
	Position=auto_ptr<_Position>(new _Position());
	Size=auto_ptr<_Size>(new _Size());

}


Base3DObject::~Base3DObject(void)
{
	

//	 this->Texture.release();
//	 this->Color.release();
	 this->Position.release();
	 this->Size.release();

	 
}

void _Position::MoveTo(float X,float Y,float Z)
{
			this->Set(X,Y,Z);

			glTranslatef(this->X,this->Y,this->Z);
}
void _Position::Set(float X,float Y,float Z)
{
			this->X=X;
			this->Y=Y;
			this->Z=Z;
}
void _Position::RotateAround(float Angle,char Direction)
{
	this->Angle=Angle;

	switch(Direction)
	{
		case 'x':glRotatef(Angle,1.0,0.0,0.0);
		break;
		case 'y':glRotatef(Angle,0.0,1.0,0.0);
		break;
		case 'z':glRotatef(Angle,0.0,0.0,1.0);
		break;
	}
			
}
_Color::_Color()
{
	cout<<"Color @ " <<this<<" is created"<<endl;
	this->Red=0;
	this->Green=0;
	this->Alpha=0;
	this->Blue=0;
}
_Color::~_Color()
{
	cout<<"Color @ " <<this<<" is Destroyed"<<endl;
}
_Color::_Color(const _Color& color)
{
	this->Alpha=color.Alpha;
	this->Blue=color.Blue;
	this->Green=color.Green;
	this->Red=color.Red;
}

_Color & _Color::operator=(const _Color & color) {
	if (this == &color)
		return *this;  
}

void _Color::set(GLubyte Red,GLubyte Green,GLubyte Blue)
{
	this->set(Red,Green,Blue,0);
}
void _Color::set(GLubyte Red,GLubyte Green,GLubyte Blue,GLubyte Alpha)
{
	this->Red=Red;
	this->Green=Green;
	this->Blue=Blue;
	this->Alpha=Alpha;	
}
void _Color::Render()
{
	glColor4ub(this->Red,this->Green,this->Blue,this->Alpha);
			
}