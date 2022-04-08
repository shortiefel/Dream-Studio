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
#include "Engine/Header/ECS/DreamECS.hpp"

#include <list>
#include <unordered_map>

//Grid will never go negative 
#define GRID_NULL_VALUE -999
//False = fail
#define GRID_NULL_VALUE_CHECK(value) (!(value.x == GRID_NULL_VALUE) && !(value.y == GRID_NULL_VALUE))

//How long one line can (when drawing)
#define MAX_LINE 100
//The number of waypoints
#define MAX_WAYPOINTS 100
//Technically each left turns is about 3 waypoints so MAX_WAYPOINTS / 3
#define MAX_LEFT_TURNS 33

namespace Engine {
	namespace Game {
		enum class CellType {
			Empty = 0,
			Road,
			Structure,
			SpecialStructure,
			None
		};

		enum class CellDirection {
			Left = 0,
			Right,
			Up,
			Down,
			End
		};

		struct Cell {
			CellType ct = CellType::Empty;
			unsigned int entityId = 0;
			Math::ivec2 adjacentCell[4] = {};
			int cellBinary = 0;

			std::list<Math::ivec2> GetAdjacent();
		};

		enum class RouteType {
			HouseToDest = 0,
			DestToHouse
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
			void ResizeGrid(int newWidth, int newHeight);
			/*-----------------------------------------------------
			Deallocate memory allocated for grid
			-----------------------------------------------------*/
			void DestroyGrid();

			int GetCellType(int x, int y);
			void SetCellType(int x, int y, int cellType, unsigned int entityId);
			/*-----------------------------------------------------
			Randomize index of Road points to retrieve a Road position
			-----------------------------------------------------*/
			bool GetRandomRoadPoint(Math::ivec2* pos);
			/*-----------------------------------------------------
			Randomize index of Road points to retrieve a Road position
			-----------------------------------------------------*/
			bool GetRandomSpecialStructurePoint(Math::ivec2* pos);

			bool GetRandomHouseStructurePoint(Math::ivec2* pos);
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

			bool IsWithinGrid(Math::ivec2 pos);
			bool IsPosFree(Math::ivec2 pos);
			bool IsPosRoad(Math::ivec2 pos);
			bool IsSurrounded(Math::ivec2 pos, int type);

			int SetRoads(Math::ivec2 posArr[MAX_LINE], int size);
			int UnsetRoads(Math::ivec2 pos, std::vector<Math::ivec2>* roadRemoved);

			bool UnsetDestination(Math::ivec2 pos, Math::ivec2& posToRemove);

			void RevertGrid();
			void FinalizeGrid();

			void AStarSearch(Math::vec2(&arr)[MAX_WAYPOINTS], int* count, Math::vec2(&leftArr)[MAX_LEFT_TURNS], int* leftArrCount, Math::ivec2* housePos, Math::ivec2 destPos, int routeType);

			void GetAllAdjacentCells(Math::ivec2(&arr)[4], int* count, int x, int y); // Should be private

			void PrintGridOut_Engine();

		private:
			std::list<Math::ivec2> RetryAStar(Math::ivec2& housePos, Math::ivec2 destPos);
			std::list<Math::ivec2> AStarSearchInternal(Math::ivec2 startPosition, Math::ivec2& endPosition, RouteType routeType);
			std::list<Math::ivec2> GetAdjacentCells(Math::ivec2 cell, bool isAgent);

			bool DestinationCheck(Entity_id idTocheck, Math::ivec2 pos);

			//Number of tiles in x and y
			Math::ivec2 mapSize{};
			Math::ivec2 offset{};
			Cell** grid = nullptr;
			//Cell** backupGrid = nullptr;

			std::list<Math::ivec2> roadList;
			std::list<Math::ivec2> houseStructure;
			std::list<Math::ivec2> specialStructure;

			SINGLETON_SETUP(Grid);
		};
	}
}

#endif