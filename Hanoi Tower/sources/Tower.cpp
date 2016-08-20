#include "Tower.h"


Tower::Tower(void)
{

	this->Ceiling=0;
	this->Floor=0;
	this->Count=0;
	this->Name="unnamed";
	this->RingSize=0;
	this->RingStep=0;
	this->Log=false;
	//this->Position=new _Position();
//	this->Color=new _Color();
	//this->Size=new _Size();



}
Tower::Tower(const Tower& tower)
{
	this->Color=tower.Color;
//	this->Color->reset(tower.Color->get());
	this->Position.reset(tower.Position.get());
	this->Size.reset(tower.Size.get());
	this->Texture=tower.Texture;
	//this->Texture.reset(tower.Texture.get());

	this->Ceiling=tower.Ceiling;
	this->Floor=tower.Floor;
	this->Count=tower.Count;
	this->Name=tower.Name;
	this->RingSize=tower.RingSize;
	this->RingStep=tower.RingStep;
	this->c=tower.c;
	
}
Tower::~Tower(void)
{
	//std::cout<<"Tower is destroyed"<<endl;
	/*
	delete &this->c;
	delete this->Name;
	*/
}
void Tower::Initialize()
{
	/*
	for(int i=0;i<this->Count;i++)
	{
		//push(Ring());
		//this->c.emplace_back(*new  Ring());
		//Ring *ring=new Ring();
		//this->push(*ring);
		this->push(*new Ring());
		this->_Get_container()[i].Position->Offset=float(RingStep);
		

		this->_Get_container()[i].Position->Y=(this->Position->Y-25)+(float(i*10));
		this->_Get_container()[i].Position->X=this->Position->X;
		this->_Get_container()[i].Position->Z=this->Position->Z;

		this->_Get_container()[i].Color->set(rand(),rand(),rand());
		
		if(this->_Get_container()[i].Size->Width-(i*2) > 1){
			this->_Get_container()[i].Size->Width-=float((i)*.75);
		}
		else 
			return;
		
		//this->_Get_container()[i].Value=this->Count-i;

		//this->_Get_container()[i].Tag=(int *)this;
		//ring->state=Attached;
		//const Ring ring2;
	//	this->push(*ring);
	
		RingSize=int((2*this->_Get_container()[i].Size->Height)+(this->_Get_container()[i].Size->Height+10));
		this->Size->Height=float(RingSize*this->Count);
		cout<<"Ring address in Tower "<<&this->_Get_container()[i]<<endl;
	}

	*/

	for(int i=0;i<this->Count;i++)
	{

#if 1
		//auto_ptr<Ring> ring(new Ring());
		Ring * ring=new Ring();
		
		ring->Position->Offset=float(RingStep);
		

		ring->Position->Y=(this->Position->Y-25)+(float(i*10));
		ring->Position->X=this->Position->X;
		ring->Position->Z=this->Position->Z;

		ring->Color->set(rand(),rand(),rand());
		
		if(ring->Size->Width-(i*2) > 1){
			ring->Size->Width-=float((i)*.75);
		}
		else 
			return;
		
		ring->Value=this->Count-i;

		ring->Tag=(int *)this;
		ring->state=Attached;
		//const Ring ring2;
		this->push(*ring);
	
		RingSize=int((2*ring->Size->Height)+(ring->Size->Height+10));
		this->Size->Height=float(RingSize*this->Count);
		cout<<"Ring address in Tower "<<&this->_Get_container()[i]<<endl;
#else
		Ring ring;

		ring.Position->Offset=float(RingStep);
		

		ring.Position->Y=(this->Position->Y-25)+(float(i*10));
		ring.Position->X=this->Position->X;
		ring.Position->Z=this->Position->Z;

		ring.Color->set(rand(),rand(),rand());
		
		//if(ring->Size->Width-(i*2) > 1){
			ring.Size->Width-=float((i)*.75);
		//}
		//else 
		//	return;
		
		ring.Value=this->Count-i;

		ring.Tag=(int *)this;
		ring.state=Attached;
		this->push(ring);

		RingSize=int((2*ring.Size->Height)+(ring.Size->Height+10));
		this->Size->Height=float(RingSize*this->Count);
		
#endif
	}
	
}
Tower& Tower::operator=(const Tower & tower) {
	if (this == &tower)
		return *this;  
}
void Tower::RenderAt(float X,float Y,float Z)
{
	this->Color->set(0,128,254);
//	this->Size->Height=30;
	this->Size->Width=5;

	glPushMatrix();
		
		this->Position->RotateAround(90,'x');
	
		this->Color->Render();

		this->Floor=30;
		
		//glTranslatef(X,Y,Z+Floor);

		glPushMatrix();
		glTranslatef(X,Y,(Z+Floor)-this->Size->Height);
			gluCylinder(gluNewQuadric(),this->Size->Width,this->Size->Width,this->Size->Height,80,80);//pillar
		glPopMatrix();

		glTranslatef(X,Y,Z+Floor);
		gluCylinder(gluNewQuadric(),this->Size->Width+10,this->Size->Width+10,5,80,80); //floor
	glPopMatrix();
}
void Tower::Render(void)
{
	this->RenderAt(this->Position->X,this->Position->Y,this->Position->Z);
}

void Tower::RenderRings()
{
	int i=RingSize;

#if 1
		for(unsigned int i=0;i<this->_Get_container().size();i++)
		{
			glPushMatrix();
#if 0
				auto_ptr<Ring> ring (new Ring(this->_Get_container()[i]));
				ring->Position->X=this->Position->X;
				ring->Render();
#else

				_Get_container()[i].Position->X=this->Position->X;
				((Ring &)_Get_container()[i]).Render();
				cout<<"Ring "<<i<<"address : "<<&_Get_container()[i]<<endl;
			
#endif
			glPopMatrix();
		}
#else
		
		for each( Ring  ring in this->_Get_container())
		{
			glPushMatrix();

			ring.Position->X=this->Position->X;
			ring.Render();	

			
			glPopMatrix();
			i+=RingSize;


		}
		
#endif		
}
void Tower::Push(Ring & ring)
{
	//this->c._Mysize++;
	this->push(ring);	
}
void Tower::Pop()
{
	//this->c._Mysize--;
	this->pop();
}
Ring & Tower::Top()
{
		return this->top();
}

