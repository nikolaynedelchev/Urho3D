
#pragma once

#include <Urho3D/Scene/Component.h>
#include <string>
#include <Urho3D/Core/Variant.h>
#include <Urho3D/Urho2D/Drawable2D.h>
namespace Egt
{

namespace Presenter
{


/// Urho3DPlayer application runs a script specified on the command line.
class TestComponent : public Urho3D::Drawable2D
{
    URHO3D_OBJECT(TestComponent, ::Urho3D::Component);

public:
    /// Construct.
    explicit TestComponent(::Urho3D::Context* context);
    static void RegisterObject(::Urho3D::Context* context);


    int GetMyValue() const;
    void SetMyValue(int v);

    bool GetIsOk() const;
    void SetIsOk(bool isOk);

    Urho3D::VariantMap GetMyMap() const;
    void SetMyMap(Urho3D::VariantMap myMap);

private:
    int m_myValue = 666;
    bool m_isOk = true;
    Urho3D::VariantMap m_myMap;

    // Drawable interface
protected:
    void OnWorldBoundingBoxUpdate() override;

    // Drawable2D interface
protected:
    void OnDrawOrderChanged() override;
    void UpdateSourceBatches() override;
};

}
}
