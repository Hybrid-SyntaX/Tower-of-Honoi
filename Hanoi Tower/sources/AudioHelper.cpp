#include "AudioHelper.h"


AudioHelper::AudioHelper(void)
{
	alutInit(NULL, 0);
}


AudioHelper::~AudioHelper(void)
{
}



ALuint  AudioHelper::BindBuffer(ALint  buffer,ALboolean loop)
{
		// Bind the buffer with the source.
	
		ALuint  source;
		alGenSources(1, &source);

		if(alGetError() != AL_NO_ERROR)
		{
			cout<<alGetError();
			return NULL;
		}
		
		ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

	// Velocity of the source sound.
		ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
		
		alSourcei (source, AL_BUFFER,   buffer   );
		alSourcef (source, AL_PITCH,    1.0      );
		alSourcef (source, AL_GAIN,     1.0      );
		alSourcefv(source, AL_POSITION, SourcePos);
		alSourcefv(source, AL_VELOCITY, SourceVel);
		alSourcei (source, AL_LOOPING,  loop     );

		// Do another error check and return.
		if(alGetError() == AL_NO_ERROR)
		{
			return source;
		}
		
}
ALuint AudioHelper::LoadSoundFile(ALbyte * fileName=NULL)
{
	//	if(fileName!=NULL)
		//	FileName=fileName;

		ALenum format;
		ALsizei size;
		ALvoid* data;
		ALsizei freq;
		ALboolean loop;
		ALuint buffer;

		// Load wav data into a buffer.

		alGenBuffers(1, &buffer);

		if(alGetError() != AL_NO_ERROR)
			return AL_FALSE;
		
		alutLoadWAVFile(fileName, &format, &data, &size, &freq, &loop);
		
		alBufferData(buffer, format, data, size, freq);

	

		alutUnloadWAV(format, data, size, freq);
		
	

		if(alGetError() == AL_NO_ERROR)
			return buffer;
		else
			return NULL;
	
}
void AudioHelper::SetListenerValues()
{
			// Position of the source sound.
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

	// Velocity of the source sound.
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };


	// Position of the Listener.
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

	// Velocity of the Listener.
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

	// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
	// Also note that these should be units of '1'.
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
		alListenerfv(AL_POSITION,   ListenerPos);
		alListenerfv(AL_VELOCITY,    ListenerVel);
		alListenerfv(AL_ORIENTATION, ListenerOri);
}
void AudioHelper::KillALData()
{
		
		//alDeleteBuffers(1, &Buffer);
		//alDeleteSources(1, &Source);
		//alutExit();
}
void AudioHelper::Play()
{
	alutInit(NULL, 0);
	//alGetError();

	// Load the wav data.
	/*
	if(OldLoadALData() == AL_FALSE)
	{
		cout<< "Error loading data.";
	}
	*/

//	OldLoadALData();
	SetListenerValues();

	// Setup an exit procedure.


	alSourcePlay(Source);
}
void AudioHelper::Play(ALuint  buffer,ALboolean loop=FALSE)
{
	//Source=this->BindBuffer(buffer,loop);
	SetListenerValues();
	alSourcePlay(this->BindBuffer(buffer,loop));
}
void AudioHelper::Play(ALbyte * fileName)
{
//	Source=this->InitWav(fileName);
	//this->Play(Source);
}