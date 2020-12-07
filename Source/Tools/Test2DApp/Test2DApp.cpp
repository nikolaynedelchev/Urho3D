#ifdef URHO3D_ANGELSCRIPT
#include <Urho3D/AngelScript/ScriptFile.h>
#include <Urho3D/AngelScript/Script.h>
#endif
#include <Urho3D/Core/Main.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>
#ifdef URHO3D_LUA
#include <Urho3D/LuaScript/LuaScript.h>
#endif
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/ResourceEvents.h>

#include "Test2DApp.h"
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/DebugNew.h>
#include <iostream>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Urho2D/ParticleEmitter2D.h>

URHO3D_DEFINE_APPLICATION_MAIN(::Egt::Test2D::Test2DApp);

namespace Egt
{
namespace Test2D
{


Test2DApp::Test2DApp(Urho3D::Context* context) :
    Application(context)
{

}

void Test2DApp::Setup()
{
    context_->RegisterSubsystem(new Urho3D::Script(context_));
    context_->RegisterSubsystem(new Urho3D::Log(context_));

    engineParameters_[Urho3D::EP_WINDOW_TITLE] = Urho3D::String("EGT 2D Test");
    engineParameters_[Urho3D::EP_WINDOW_WIDTH] = 1280;
    engineParameters_[Urho3D::EP_WINDOW_HEIGHT] = 960;
    engineParameters_[Urho3D::EP_FULL_SCREEN] = false;
    engineParameters_[Urho3D::EP_BORDERLESS] =false;
    engineParameters_[Urho3D::EP_WINDOW_RESIZABLE] = false;
}

void Test2DApp::Start()
{
    // Subscribe key down event
    SubscribeToEvent(Urho3D::E_KEYUP, URHO3D_HANDLER(Test2DApp, HandleKeyUp));

//    Urho3D::Graphics* graphics = GetSubsystem<Urho3D::Graphics>();
//    graphics->SetMode(1280, 960, false, false, false, false, false, false, 1, 0, 60);
    m_scene = new Urho3D::Scene(context_);

    auto* cache = GetSubsystem<Urho3D::ResourceCache>();
    Urho3D::SharedPtr<Urho3D::File> sceneFile = cache->GetFile("Scenes/test_scene_2.xml");

    if (m_scene->LoadXML(*sceneFile))
    {
        GetSubsystem<Urho3D::Log>()->Write(3, "Scene loaded");
    }
    else
    {
        GetSubsystem<Urho3D::Log>()->Write(3, "Scene ERROR!");
    }

    // Get sprite
    auto* sprite = cache->GetResource<Urho3D::Sprite2D>("Textures/EGT.png");
    if (!sprite)
    {
        return;
    }
    auto* renderer = GetSubsystem<Urho3D::Renderer>();
    auto cameraNode = m_scene->GetChild("Camera");
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    Urho3D::SharedPtr<Urho3D::Viewport> viewport(new Urho3D::Viewport(context_, m_scene, cameraNode->GetComponent<Urho3D::Camera>()));
    renderer->SetViewport(0, viewport);

    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(Urho3D::E_UPDATE, URHO3D_HANDLER(Test2DApp, HandleUpdate));

    // Unsubscribe the SceneUpdate event from base class to prevent camera pitch and yaw in 2D sample
    UnsubscribeFromEvent(Urho3D::E_SCENEUPDATE);
}

void Test2DApp::Stop()
{
}

void Test2DApp::HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData)
{
    auto child = m_scene->GetChild("egt_logo", true);
    auto scale = child->GetScale2D();
    if (scale.x_ > 2.0f)
    {
        scale.x_ = 0.2f;
        scale.y_ = 0.2f;
    }
    else
    {
        scale.x_ += 0.05f;
        scale.y_ += 0.05f;
    }
    //child->SetScale2D(scale);
}

void Test2DApp::HandleKeyUp(Urho3D::StringHash /*eventType*/, Urho3D::VariantMap& eventData)
{
    //using namespace Urho3D::KeyUp;

    int key = eventData[Urho3D::KeyUp::P_KEY].GetInt();

    // Close console (if open) or exit when ESC is pressed
    if (key == Urho3D::KEY_ESCAPE)
    {
        engine_->Exit();
    }
}


}
}
