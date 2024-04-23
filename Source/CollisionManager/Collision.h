#pragma once


namespace Collisions
{
	class NonInterative
	{
	public:
		std::vector<Image>       Floor_Down_Col;
		std::vector<Image>       Floor_Col;
		std::vector<Image>        Wall_Col;
		std::vector<Image>        Hang_Col; // ��¤��� Į�ű�� �����ؾߵǳ�?
	};

	class Interactive
	{
	public:
		std::vector<Animation>  Inter_Ani;
		//
		std::vector<Image>       Chest_Col;
		std::vector<Image>      Ladder_Col;
		std::vector<Image>        Warp_Col;


		// ������ ū�� �ҰŸ�  
		std::vector<Image>        Door_Col;
	};
}

