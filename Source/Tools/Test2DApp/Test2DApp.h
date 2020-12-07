#pragma once

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Core/Variant.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Container/Ptr.h>
namespace Egt
{
namespace Test2D
{

/// Urho3DPlayer application runs a script specified on the command line.
class Test2DApp : public Urho3D::Application
{
    URHO3D_OBJECT(Test2DApp, Application);

public:
    /// Construct.
    explicit Test2DApp(Urho3D::Context* context);

    /// Setup before engine initialization. Verify that a script file has been specified.
    void Setup() override;
    /// Setup after engine initialization. Load the script and execute its start function.
    void Start() override;
    /// Cleanup after the main loop. Run the script's stop function if it exists.
    void Stop() override;

private:

    void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
    void HandleKeyUp(Urho3D::StringHash /*eventType*/, Urho3D::VariantMap& eventData);

    Urho3D::SharedPtr<Urho3D::Scene> m_scene;
};

}
}
