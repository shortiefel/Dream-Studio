#ifndef SCENE_SERIALIZER_HPP
#define SCENE_SERIALIZER_HPP

#include <string>

namespace Engine {
	class SceneSerializer {
	public:
		//From scene to a file
		static void Serialize(std::string filename);

		//From file to a scene
		static void Deserialize(std::string filename);
	};
}
#endif