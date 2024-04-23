#pragma once

#define Animation Rendering::Animation::Component
#define Image     Rendering::Image::Component



enum class P_ANI_TYPE { IDLE, JUMP, HANG, DODGE, CROUCH, ATTACK, PARRY, LADDER, KNEEL, GETHIT, RUN, POTION, DEATH};

enum class MONSTER_TYPE { ELDER, LIONHEAD, SHIELD_MON, FOIL_MON };

enum class ELDER_ANI_TYPE { IDLE, ATTACK, JUMP , DEATH  , BEAM};
enum class LIONHEAD_ANI_TYPE { IDLE, ATTACK, WALK, DEATH };
enum class SHIELD_ANI_TYPE { IDLE, ATTACK, WALK, PARRY, DEATH };
enum class FOIL_ANI_TYPE { IDLE, ATTACK, PARRY, HURT, DEATH };


class AActor abstract
{
private:
	std::string mon_str, str;
	size_t      mon_first, first;
	size_t      mon_last, last;




public:
	AActor();
	virtual ~AActor();

	virtual void Start()  abstract;
	virtual void Update() abstract;
	virtual void End()    abstract;


protected:
	bool Release = true;
	virtual void ADebugCollider() abstract;
	virtual void ADrawCollider() abstract;

protected:
	vector<2> Location = { 0,0 };
	vector<3> Rotation = { 0,0,0 };
	vector<2> Scale = { 0,0 };



protected:
	virtual void SetActorTransform(Image) final;
	virtual void SetActorTransform(Animation) final;

	void SetNowAnim(AActor& Owner, Animation anim);



public:
	bool isWarped = false;

	bool isDecreasedHp = false;
	bool isIncreasedHp = false;
	int attkDmg = 0;


public:
	const vector<2> GetActorLocation() const
	{
		return Location;
	}
	const vector<3> GetActorRotation() const
	{
		return Rotation;
	}
	const vector<2> GetActorScale() const
	{
		return Scale;
	}

	Animation P_Effect_Anim;
	Animation P_Anim;

	Animation M_Effect_Anim;
	Animation M_Anim; // 몬스터 이름 넣어서


public:
	// Battle System에서 사용할 것들
	bool P_TYPE_CHK(P_ANI_TYPE PLAYER_ANIM);

	bool MONSTER_TYPE_CHK(MONSTER_TYPE MONSTER);
	bool ELDER_TYPE_CHK(ELDER_ANI_TYPE ELDER_ANIM);
	bool SHIELD_TYPE_CHK(SHIELD_ANI_TYPE SHIELD_ANIM);
	bool LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE LIONHEAD_ANIM);
	bool FOIL_TYPE_CHK(FOIL_ANI_TYPE FOIL_ANIM);


	//bool M_TYPE_CHK(P_ANI_TYPE PLAYER_ANIM);

	Animation GetNowPlayerAnim();
	Animation GetNowMonsterAnim();



public:
	bool RR_Col_Chk(Image& LHS, float LHS_Angle, Image& RHS, float RHS_Angle);
	bool PR_Col_Chk(float LHS_Location_X, float LHS_Location_Y, Image& RHS, float RHS_Angle);
	bool RC_Col_Chk(Image& LHS, float LHS_Angle, Image& RHS);
	bool PC_Col_Chk(float LHS_Location_X, float LHS_Location_Y, Image& RHS);

};



