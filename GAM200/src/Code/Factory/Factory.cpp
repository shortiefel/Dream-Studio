#include "Factory/Factory.hpp"

#include "Coordinator/Coordinator.hpp"

//Components
#include "Component/Graphics/TransformComponent.hpp"
#include "Component/Physics/ColliderComponent.hpp"
#include "Component/Graphics/RendererComponent.hpp"

//Systems
#include "System/GraphicSystem.hpp"
#include "System/PhysicSystem.hpp"
//#include "Graphic/Camera.hpp"

//Entity ent;
//Entity ent2;
//Entity camera;
//std::shared_ptr<GraphicSystem> graphicSystem;
//std::shared_ptr<PhysicSystem> physicSystem;
Coordinator gCoordinator;

void Factory::SetUp() {
    gCoordinator.Init();
    gCoordinator.RegisterComponent<Collider>();
    gCoordinator.RegisterComponent<Transform>();
    gCoordinator.RegisterComponent<Renderer2D>();

    GraphicSystem::Create(gCoordinator.RegSystem<GraphicSystem>());
    PhysicSystem::Create(gCoordinator.RegSystem<PhysicSystem>());
    
    Signature signature;
    signature.set(gCoordinator.GetComType<Transform>());
    signature.set(gCoordinator.GetComType<Renderer2D>());
    gCoordinator.setSystemSignature<GraphicSystem>(signature);

    signature.reset();
    signature.set(gCoordinator.GetComType<Transform>());
    signature.set(gCoordinator.GetComType<Collider>());
    gCoordinator.setSystemSignature<PhysicSystem>(signature);
}

void CreateSquare(MathD::Vec2 pos = MathD::Vec2{ 0.f, 0.f }, MathD::Vec2 scale = MathD::Vec2{ 20.f, 20.f }, bool isMoveable = false) {

}
