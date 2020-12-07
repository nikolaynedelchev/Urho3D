#include "TestComponent.h"
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Attribute.h>



namespace Urho3D
{
    extern const char* URHO2D_CATEGORY;
}

namespace Egt
{
const char* EGT_URHO_CATEGORY = "Egt";


namespace Presenter
{



TestComponent::TestComponent(Urho3D::Context *context)
    : Urho3D::Drawable2D(context)

{
}

void TestComponent::RegisterObject(Urho3D::Context *context)
{

    context->RegisterFactory<TestComponent>(EGT_URHO_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(Drawable2D);
    URHO3D_ACCESSOR_ATTRIBUTE("My Test Value", GetMyValue, SetMyValue, int, 666, Urho3D::AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("Is OK", GetIsOk, SetIsOk, bool, true, Urho3D::AM_DEFAULT);
    URHO3D_ACCESSOR_ATTRIBUTE("My VarMap",GetMyMap, SetMyMap, Urho3D::VariantMap, Urho3D::Variant::emptyVariantMap, Urho3D::AM_DEFAULT);

}

int TestComponent::GetMyValue() const
{
    return m_myValue;
}

void TestComponent::SetMyValue(int v)
{
    m_myValue = v * 3;
}

bool TestComponent::GetIsOk() const
{
    return m_isOk;
}

void TestComponent::SetIsOk(bool isOk)
{
    m_isOk = isOk;
}

Urho3D::VariantMap TestComponent::GetMyMap() const
{
    return m_myMap;
}

void TestComponent::SetMyMap(Urho3D::VariantMap myMap)
{
    m_myMap = std::move(myMap);
}

void TestComponent::OnWorldBoundingBoxUpdate()
{

}

void TestComponent::OnDrawOrderChanged()
{

}

void TestComponent::UpdateSourceBatches()
{

}


}
}
