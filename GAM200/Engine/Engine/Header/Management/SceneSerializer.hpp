#ifndef SCENE_SERIALIZER_HPP
#define SCENE_SERIALIZER_HPP

namespace Engine {
	class SceneSerializer {
	public:
		//From scene to a file
		void Serialize();

		//From file to a scene
		void Deserialize();
	};
}
#endif