#pragma once
#include "vector.h"

namespace Rendering
{
	class Camera final
	{
	public :
		void Set() const;

	public :
		vector<2> Length   = { 1280 , 720 };
		float     Angle    = 0;
		vector<2> Location = { 0 , 0 };
	};

	namespace Text
	{
		class Component final
		{
		public :
			void Draw();

		public :
			char const* str = nullptr;

			struct
			{
				char const* Content       = nullptr;
				unsigned    Size          = 0;
				bool        Bold          = false;
				bool        Italic        = false;
				bool        Underlined    = false;
				bool        StrikeThrough = false;
			}Font;

			struct
			{
				unsigned __int8 Red   = 0;
				unsigned __int8 Green = 0;
				unsigned __int8 Blue  = 0;
			}Color;

		public :
			vector<2> Location = { 0.0f , 0.0f };
		};
	}

	namespace Image
	{
		class Component final
		{
		public :
			void Draw();

		public :
			char const* Content = nullptr;

		public :
			vector<2> Length   = { 0 , 0 };
			vector<3> Angle    = { 0 , 0 , 0 };
			vector<2> Location = { 0 , 0 };
			float     Alpha    = 1.0f;
			float RGBA[4]      = { 1.0f ,0, 0, 0 };
		};
	}


	namespace Animation
	{
		class Component final
		{
		public:
			void Draw();

		public:
			char const* Content = nullptr;

			float Playback = 0;
			float Duration = 0;
			bool  Loop     = true;
			bool  End      = false;
			float Alpha    = 1.0f;
			float RGBA[4]  = { 1.0f ,0, 0, 0 };

		public:
			vector<2> Length   = { 0 , 0 };
			vector<3> Angle    = { 0 , 0 , 0 };
			vector<2> Location = { 0 , 0 };
		};
	}
};

