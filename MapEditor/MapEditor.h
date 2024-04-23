#pragma once
#include "Scene/Scene.h"

class MapEditor final : public Scene
{
    enum class VectorType
    {
        Images,
        Floors,
        Walls
    };


public:
    virtual void Start() override;
    virtual bool Update() override;
    virtual void End() override;

    virtual void DebugCollider() override;
    virtual void DrawCollider() override;

private:
    std::vector<Image>* Vector;
    std::vector<Image>  Objects;
    std::vector<Image>  Floor_Collisions;
    std::vector<Image>  Wall_Collisions;

   // Rendering::Camera Camera;
    Rendering::Text::Component Text;

    bool bSnapping = true;

private:
    VectorType Type;

    int scope_V = 0;


    float SnappingValue;
    float Value;
    std::string Str;

private:
    void Print() const;
    void ChangeImage();
    void ChangeTransform();
    void Create();
    void ChangeType();
    void TextDraw();

    __forceinline float GetValue()
    {
        if (bSnapping)
            return SnappingValue;
        else
            return Value;
    }


    __forceinline void GetCameraVScope()
    {
        if (!Input::Get::Wheel::V())
        {
            scope_V = static_cast <int>(0);
            return;
        }
        else
            scope_V += -1 * static_cast<int>(Input::Get::Wheel::V()) * 1;
    }

    void ChangeValue();

    bool Input(size_t code) const;

};

