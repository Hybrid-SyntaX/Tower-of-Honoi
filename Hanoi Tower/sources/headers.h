
#pragma comment(lib, "headers/GL/freeglut.lib")
#pragma comment(lib, "headers/GL/freeglut_static.lib")
#pragma comment(lib, "headers/AL/OpenAL32.lib")
#pragma comment(lib,"headers/AL/alut.lib")
#pragma comment(lib,"headers/AL/alut.lib")

#pragma comment( compiler )



#ifndef CPP_STL_HEADERS 
#define CPP_STL_HEADERS
	#include <iostream>
	#include <windows.h>
	#include <psapi.h>
	#include <cmath>
	#include <stack>
	#include <vector>
	#include <memory>
	#include <stdio.h>
	#include <stdlib.h>
#endif





//Graphics Headers
#ifndef GL_HEADERS
#define GL_HEADERS
	
#ifdef WIN32
	
	#include "../Headers/GL/glee.h"			
	#include <gl\gl.h>			
	#include <gl\glu.h>	
	#include "../Headers/GL/glut.h"

#endif

#ifdef __APPLE__
	#include <Carbon/Carbon.h>	// Brings in most Apple specific stuff
	#include "glee.h"		// OpenGL Extension "autoloader"
	#include <OpenGL/gl.h>		// Apple OpenGL haders (version depends on OS X SDK version)
	#include <OpenGL/glu.h>		// OpenGL Utilities
	#include <Glut/glut.h>		// Apples Implementation of GLUT

	#define Sleep(x)
#endif

#ifdef linux
	#include "GLee.h"
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <glut.h>
	#include <stdlib.h>

	// Just ignore sleep in linux too
	#define Sleep(x)
#endif

#endif
//Audio Headers

#ifndef AL_HEADERS
#define AL_HEADERS
	#include "../Headers/AL/al.h"
	#include "../Headers/AL/alc.h"
	#include "../Headers/AL/alut.h"
#endif






using namespace std;


