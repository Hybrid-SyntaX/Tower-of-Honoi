#pragma once
#include "base3dobject.h"
#include "Texture.h"
#include "headers.h"
enum State{Attached,Detached,Rejected};

class Ring :
	public Base3DObject
{

public:
	
	Ring();
	Ring(const Ring& ring);


	~Ring();
	void Render();
	void RenderAt(float X,float Y,float Z);
	Ring * Clone();
	void Log();


	Ring& operator=(const Ring & ring);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	short Value;
	float Offset;

	


	bool isFloat;
	State state;
	
	int * Tag;

};

