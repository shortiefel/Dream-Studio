/* Start Header**********************************************************************************/
/*
@file    Grid.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    29/10/2021
\brief
#include "Engine/Header/Grid/Grid.hpp"
This file contain the declaration of Grid


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GRID_H
#define GRID_H

#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"

#include <list>

//Grid will never go negative 
#define GRID_NULL_VALUE -999
//False = fail
#define GRID_NULL_VALUE_CHECK(value) (!(value.x < 0) && !(value.y < 0))

//How long one line can (when drawing)
#define MAX_LINE 100

namespace Engine {
	namespace Game {
		enum class CellType {
			Empty = 0,
			Road,
			Structure,
			SpecialStructure,
			None
		};

		class Grid : public Singleton<Grid> {
		public:
			/*-----------------------------------------------------
			Get grid size
			-----------------------------------------------------*/
			Math::ivec2 GetGridSize();
			Math::ivec2 GetStartPoint();
			/*-----------------------------------------------------
			Create grid with width and height
			-----------------------------------------------------*/
			void CreateGrid(int width, int height);
			void ResizeGrid(int startX, int startY, int newWidth, int newHeight);
			/*-----------------------------------------------------
			Deallocate memory allocated for grid
			-----------------------------------------------------*/
			void DestroyGrid();

			int GetCellType(int x, int y);
			void SetCellType(int x, int y, int cellType);
			/*-----------------------------------------------------
			Randomize index of Road points to retrieve a Road position
			-----------------------------------------------------*/
			bool GetRandomRoadPoint(Math::ivec2* pos);
			/*-----------------------------------------------------
			Randomize index of Road points to retrieve a Road position
			-----------------------------------------------------*/
			bool GetRandomSpecialStructurePoint(Math::ivec2* pos);
			/*-----------------------------------------------------
			Get adjacent cells that the specific object(isAgent) can walk on
			-----------------------------------------------------*/
			void GetWalkableAdjacentCells(Math::ivec2(&arr)[4], int* count, int x, int y, bool isAgent);
			/*-----------------------------------------------------
			Get count of _type around x and y position
			-----------------------------------------------------*/
			void GetAdjacentCellsOfType(Math::ivec2(&arr)[4], int* count, int x, int y, int _type);
			/*-----------------------------------------------------
			Get count of all adjacent cells of any type
			-----------------------------------------------------*/
			void GetAllAdjacentCellTypes(int(&arr)[4], int x, int y);

			void AStarSearch(Math::ivec2(&arr)[MAX_LINE], int* count, Math::ivec2 startPosition, Math::ivec2 endPosition, bool isAgent);

			void GetAllAdjacentCells(Math::ivec2(&arr)[4], int* count, int x, int y); // Should be private

			void PrintGridOut_Engine();

		private:
			std::list<Math::ivec2> AStarSearchInternal(Math::ivec2 startPosition, Math::ivec2 endPosition, bool isAgent);
			std::list<Math::ivec2> GetAdjacentCells(Math::ivec2 cell, bool isAgent);

			//Number of tiles in x and y
			Math::ivec2 mapSize{};
			Math::ivec2 offset{};
			CellType* grid = nullptr;

			std::list<Math::ivec2> roadList;
			std::list<Math::ivec2> houseStructure;
			std::list<Math::ivec2> specialStructure;

			SINGLETON_SETUP(Grid);
		};
	}
}

#endif