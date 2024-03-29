/* Start Header**********************************************************************************/
/*
@file    EditorStartPoint.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu	100%
@date    23/07/2021
\brief
This file contain the EditorStartPoint declaration

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef EDITOR_START_POINT_HPP
#define EDITOR_START_POINT_HPP

namespace Editor {
	class EditorStartPoint {
	public:
		static void Create();
		static void Update(float _dt);
		static void Destroy();

	private:
	};
}

#endif