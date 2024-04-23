#pragma once
namespace Sound
{
	class Sound final
	{
	public :
		void Play();
		void Stop();
		void Pause();

	public :
		char const * Content = nullptr;

	public :
		float Volume = 0.0f;
		bool  Loop   = false;


	public:
		bool bPause = false;

	};

};

