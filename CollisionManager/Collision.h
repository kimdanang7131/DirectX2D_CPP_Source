#pragma once


namespace Collisions
{
	class NonInterative
	{
	public:
		std::vector<Image>       Floor_Down_Col;
		std::vector<Image>       Floor_Col;
		std::vector<Image>        Wall_Col;
		std::vector<Image>        Hang_Col; // º®Â¤±â¶û Ä®²Å±â¶û °°ÀÌÇØ¾ßµÇ³ª?
	};

	class Interactive
	{
	public:
		std::vector<Animation>  Inter_Ani;
		//
		std::vector<Image>       Chest_Col;
		std::vector<Image>      Ladder_Col;
		std::vector<Image>        Warp_Col;


		// ÀÛÀº¹® Å«¹® ÇÒ°Å¸é  
		std::vector<Image>        Door_Col;
	};
}

