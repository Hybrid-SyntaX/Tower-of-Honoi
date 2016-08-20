#pragma once
#include "headers.h"
#include "Ring.h"

class Tower :
	public stack<Ring>,public Base3DObject
{
public:
	Tower(void);

	~Tower(void);
	
	float Floor;
	void RenderAt(float X,float Y,float Z);
	void Render();
	
	Tower(const Tower& tower);
	Tower& operator=(const Tower & tower);
	
	char * Name;
	short Count;
	short Ceiling;
	int RingSize;
	int RingStep;
	bool Log;

	void Initialize();
	void RenderRings();


	void Push(Ring & ring);
	void Pop();
	Ring & Top();

};

