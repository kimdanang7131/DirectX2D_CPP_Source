#include "stdafx.h"
#include "Actor.h"

using namespace Collision;

AActor::AActor()
{
    //GameManager->AddActor(this);
}


AActor::~AActor()
{
    //GameManager->DeleteActor(this);
}

void AActor::SetActorTransform(Image image)
{
    Location = image.Location;
    Rotation = image.Angle;
    Scale = image.Length;
}

void AActor::SetActorTransform(Animation animation)
{
    Location = animation.Location;
    Rotation = animation.Angle;
    Scale = animation.Length;
}


void AActor::SetNowAnim(AActor& Owner, Animation anim)
{
    if (Owner.P_Anim.Content == anim.Content)
        P_Anim = anim;

    if (Owner.M_Anim.Content == anim.Content)
        M_Anim = anim;
}


Animation AActor::GetNowPlayerAnim()
{
    return P_Anim;
}

Animation AActor::GetNowMonsterAnim()
{
    return M_Anim;
}


bool AActor::P_TYPE_CHK(P_ANI_TYPE PLAYER_ANIM)
{
    str = P_Anim.Content;
    first = str.find_first_of('/') + sizeof(char);
    last = str.find_last_of('/');
    str = str.substr(first, last - first);
    //Player /
    switch (PLAYER_ANIM)
    {
    case P_ANI_TYPE::IDLE:
        if (str == "IDLE")
            return true;
        break;

    case P_ANI_TYPE::JUMP:
        if (str == "JUMP")
            return true;
        break;

    case P_ANI_TYPE::HANG:
        if (str == "HANG")
            return true;
        break;

    case P_ANI_TYPE::DODGE:
        if (str == "DODGE")
            return true;
        break;

    case P_ANI_TYPE::CROUCH:
        if (str == "CROUCH")
            return true;
        break;

    case P_ANI_TYPE::ATTACK:
        if (str == "ATTACK")
            return true;
        break;

    case P_ANI_TYPE::PARRY:
        if (str == "PARRY")
            return true;
        break;

    case P_ANI_TYPE::LADDER:
        if (str == "LADDER")
            return true;
        break;

    case P_ANI_TYPE::KNEEL:
        if (str == "KNEEL")
            return true;
        break;

    case P_ANI_TYPE::GETHIT:
        if (str == "GETHIT")
            return true;
        break;

    case P_ANI_TYPE::RUN:
        if (str == "RUN")
            return true;
        break;

    case P_ANI_TYPE::POTION:
        if (str == "POTION")
            return true;
        break;

    case P_ANI_TYPE::DEATH:
        if (str == "DEATH")
            return true;
        break;

    default:
        break;
    }
    return false;
}

bool AActor::MONSTER_TYPE_CHK(MONSTER_TYPE MONSTER)
{
    mon_str = M_Anim.Content;
    mon_first = mon_str.find_first_of('_') + sizeof(char);
    mon_last = mon_str.find_first_of('/');
    mon_str = mon_str.substr(mon_first, mon_last - mon_first);

    switch (MONSTER)
    {
    case MONSTER_TYPE::ELDER:
        if (mon_str == "Elder")
            return true;
        break;
    case MONSTER_TYPE::LIONHEAD:
        if (mon_str == "LionHead")
            return true;
        break;
    case MONSTER_TYPE::SHIELD_MON:
        if (mon_str == "Shield")
            return true;
        break;
    case MONSTER_TYPE::FOIL_MON:
        if (mon_str == "Foil")
            return true;
        break;
    default:
        break;
    }

    return false;
}

bool AActor::ELDER_TYPE_CHK(ELDER_ANI_TYPE ELDER_ANIM)
{
    std::string str = M_Anim.Content;
    size_t first = str.find_first_of('/') + sizeof(char);
    size_t last = str.find_last_of('/');
    str = str.substr(first, last - first);


    switch (ELDER_ANIM)
    {
    case ELDER_ANI_TYPE::IDLE:
        if (str == "IDLE")
            return true;
        break;
    case ELDER_ANI_TYPE::ATTACK:
        if (str == "ATTACK")
            return true;
        break;
    case ELDER_ANI_TYPE::JUMP:
        if (str == "JUMP")
            return true;
        break;
    case ELDER_ANI_TYPE::DEATH:
        if (str == "DEATH")
            return true;
        break;
    case ELDER_ANI_TYPE::BEAM:
        if (str == "BEAM")
            return true;
        break;
    default:
        break;
    }


    return false;
}

bool AActor::SHIELD_TYPE_CHK(SHIELD_ANI_TYPE SHIELD_ANIM)
{
    std::string str = M_Anim.Content;
    size_t first = str.find_first_of('/') + sizeof(char);
    size_t last = str.find_last_of('/');
    str = str.substr(first, last - first);


    switch (SHIELD_ANIM)
    {
    case SHIELD_ANI_TYPE::IDLE:
        if (str == "IDLE")
            return true;
        break;
    case SHIELD_ANI_TYPE::ATTACK:
        if (str == "ATTACK")
            return true;
        break;
    case SHIELD_ANI_TYPE::WALK:
        if (str == "WALK")
            return true;
        break;
    case SHIELD_ANI_TYPE::PARRY:
        if (str == "PARRY")
            return true;
        break;
    case SHIELD_ANI_TYPE::DEATH:
        if (str == "DEATH")
            return true;
        break;
    default:
        break;
    }


    return false;
}

bool AActor::LIONHEAD_TYPE_CHK(LIONHEAD_ANI_TYPE LIONHEAD_ANIM)
{
    std::string str = M_Anim.Content;
    size_t first = str.find_first_of('/') + sizeof(char);
    size_t last = str.find_last_of('/');
    str = str.substr(first, last - first);

    switch (LIONHEAD_ANIM)
    {
    case LIONHEAD_ANI_TYPE::IDLE:
        if (str == "IDLE")
            return true;
        break;
    case LIONHEAD_ANI_TYPE::ATTACK:
        if (str == "ATTACK")
            return true;
        break;
    case LIONHEAD_ANI_TYPE::WALK:
        if (str == "WALK")
            return true;
        break;
    case LIONHEAD_ANI_TYPE::DEATH:
        if (str == "DEATH")
            return true;
        break;
    default:
        break;
    }

    return false;
}

bool AActor::FOIL_TYPE_CHK(FOIL_ANI_TYPE FOIL_ANIM)
{
    std::string str = M_Anim.Content;
    size_t first = str.find_first_of('/') + sizeof(char);
    size_t last = str.find_last_of('/');
    str = str.substr(first, last - first);

    switch (FOIL_ANIM)
    {
    case FOIL_ANI_TYPE::IDLE:
        if (str == "IDLE")
            return true;
        break;
    case FOIL_ANI_TYPE::ATTACK:
        if (str == "ATTACK")
            return true;
        break;
    case FOIL_ANI_TYPE::PARRY:
        if (str == "PARRY")
            return true;
        break;
    case FOIL_ANI_TYPE::HURT:
        if (str == "HURT")
            return true;
        break;
    case FOIL_ANI_TYPE::DEATH:
        if (str == "DEATH")
            return true;
        break;

    default:
        break;
    }

    return false;
}


bool AActor::RR_Col_Chk(Image& LHS, float LHS_Angle, Image& RHS, float RHS_Angle)
{
    return Collide(
        RectAngle{ LHS.Length , LHS_Angle , LHS.Location },
        RectAngle{ RHS.Length , RHS_Angle , RHS.Location });
}

bool AActor::PR_Col_Chk(float LHS_Location_X, float LHS_Location_Y, Image& RHS, float RHS_Angle)
{
    return Collide(
        Point{ { LHS_Location_X ,LHS_Location_Y } },
        RectAngle{ RHS.Length , RHS_Angle , RHS.Location });
}

bool AActor::PC_Col_Chk(float LHS_Location_X, float LHS_Location_Y, Image& RHS)
{
    return Collide(
        Point{ { LHS_Location_X ,LHS_Location_Y } },
        Circle{ RHS.Length[0] ,RHS.Location });
}

bool AActor::RC_Col_Chk(Image& LHS, float LHS_Angle, Image& RHS)
{
    return Collide(
        RectAngle{ LHS.Length , LHS_Angle , LHS.Location },
        Circle{ RHS.Length[0] ,RHS.Location });
}
