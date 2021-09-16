#include "Engine/Header/ECS/Component/Physics/RigidBodyComponent.hpp"

namespace Engine {
	RigidBody::RigidBody(Entity ID, bool active) : IComponent{ ID }, isActive{ active } {}

	RigidBody RigidBody::Deserialize(const Serializer& serializer) {
		isActive = serializer.GetValue<bool>("IsActive");
		return *this;
	}

	void RigidBody::Serialize(const Serializer& serializer) {

	}
}