#pragma once
#include "headers.h"
class AudioHelper
{
public:
	AudioHelper(void);
	~AudioHelper(void);

	ALuint  Buffer;
	ALuint  Source;
	ALbyte * FileName;


	void Play();
	void Play(ALbyte * fileName);
	void Play(ALuint  buffer,ALboolean loop);

	ALuint LoadSoundFile(ALbyte * fileName);
	ALboolean OldLoadALData();
	ALuint  BindBuffer(ALint  buffer,ALboolean loop);
	ALuint InitWav(ALbyte * fileName);

	void SetListenerValues();
	void KillALData();
	void KillALData(ALuint buffer,ALuint source);
};

