/* Start Header**********************************************************************************/
/*
@file    GridInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
@date    06/11/2021
\brief
#include "Engine/Header/Script/InternalCall/GridInternalCall.hpp"
This file contain the definition of GridInternalCall


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Script/InternalCall/GridInternalCall.hpp"
#include "Engine/Header/Grid/Grid.hpp"

#include <mono/jit/jit.h>

namespace Engine {
	/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/
	//Function calls are used to link to C# (functions from Grid.hpp)
	void CreateGrid_Engine(int width, int height);
	void ResizeGrid_Engine(int newWidth, int newHeight);
	int GetCellType_Engine(int x, int y);
	void SetCellType_Engine(int x, int y, int cellType, unsigned int entityId);
	bool GetRandomRoadPoint_Engine(Math::ivec2* point);
	bool GetRandomSpecialStructurePoint_Engine(Math::ivec2* point);
	bool GetRandomHouseStructurePoint_Engine(Math::ivec2* point);
	void GetAllAdjacentCells_Engine(MonoArray* monoArray, int* count, int x, int y);
	void GetWalkableAdjacentCells_Engine(MonoArray* monoArray, int* count, int x, int y, bool isAgent);
	void GetAdjacentCellsOfType_Engine(MonoArray* monoArray, int* count, int x, int y, int type);
	void GetAllAdjacentCellTypes_Engine(MonoArray* monoArray, int x, int y);

	int SetRoad_Engine(MonoArray* monoArray, int size);
	bool UnsetRoad_Engine(Math::ivec2 pos);

	void RevertGrid_Engine();
	void FinalizeGrid_Engine();

	bool IsWithinGrid_Engine(Math::ivec2 pos);
	bool IsPosFree_Engine(Math::ivec2 pos);
	bool IsSurrounded_Engine(Math::ivec2 pos);

	void AStarSearch_Engine(MonoArray* monoArray, int* count, Math::ivec2 startPosition, Math::ivec2 endPosition, Math::ivec2 housePos, Math::ivec2 destPos, bool isAgent);

	void PrintGridOut_Engine();
	/*-----------------------------------------------------------------------------------------------------------------------------------------------------*/

	void RegisterGridInternalCall() {
		mono_add_internal_call("Grid::CreateGrid_Engine", CreateGrid_Engine);
		mono_add_internal_call("Grid::ResizeGrid_Engine", ResizeGrid_Engine);
		mono_add_internal_call("Grid::GetCellType_Engine", GetCellType_Engine);
		mono_add_internal_call("Grid::SetCellType_Engine", SetCellType_Engine);
		mono_add_internal_call("Grid::GetRandomRoadPoint_Engine", GetRandomRoadPoint_Engine);
		mono_add_internal_call("Grid::GetRandomSpecialStructurePoint_Engine", GetRandomSpecialStructurePoint_Engine);
		mono_add_internal_call("Grid::GetRandomHouseStructurePoint_Engine", GetRandomHouseStructurePoint_Engine);
		mono_add_internal_call("Grid::GetAllAdjacentCells_Engine", GetAllAdjacentCells_Engine);
		mono_add_internal_call("Grid::GetWalkableAdjacentCells_Engine", GetWalkableAdjacentCells_Engine);
		mono_add_internal_call("Grid::GetAdjacentCellsOfType_Engine", GetAdjacentCellsOfType_Engine);
		mono_add_internal_call("Grid::GetAllAdjacentCellTypes_Engine", GetAllAdjacentCellTypes_Engine);
		
		mono_add_internal_call("Grid::SetRoad_Engine", SetRoad_Engine);
		mono_add_internal_call("Grid::UnsetRoad_Engine", UnsetRoad_Engine);
		
		mono_add_internal_call("Grid::RevertGrid_Engine", RevertGrid_Engine);
		mono_add_internal_call("Grid::FinalizeGrid_Engine", FinalizeGrid_Engine);
		
		mono_add_internal_call("Grid::IsWithinGrid_Engine", IsWithinGrid_Engine);
		mono_add_internal_call("Grid::IsPosFree_Engine", IsPosFree_Engine);
		mono_add_internal_call("Grid::IsSurrounded_Engine", IsSurrounded_Engine);

		mono_add_internal_call("GridSearch::AStarSearch_Engine", AStarSearch_Engine);
		mono_add_internal_call("Grid::PrintGridOut_Engine", PrintGridOut_Engine);
	}

	void CreateGrid_Engine(int width, int height) {
		std::cout << " Calling first this \n";
		Game::Grid::GetInstance().CreateGrid(width, height);
	}

	void ResizeGrid_Engine(int newWidth, int newHeight) {
		std::cout << " Calling this \n";
		Game::Grid::GetInstance().ResizeGrid(newWidth, newHeight);
	}

	int GetCellType_Engine(int x, int y) {
		return Game::Grid::GetInstance().GetCellType(x, y);
	}
	void SetCellType_Engine(int x, int y, int cellType, unsigned int entityId) {
		Game::Grid::GetInstance().SetCellType(x, y, cellType, entityId);
	}
	bool GetRandomRoadPoint_Engine(Math::ivec2* point) {
		return Game::Grid::GetInstance().GetRandomRoadPoint(point);
	}
	bool GetRandomSpecialStructurePoint_Engine(Math::ivec2* point) {
		return Game::Grid::GetInstance().GetRandomSpecialStructurePoint(point);
	}

	bool GetRandomHouseStructurePoint_Engine(Math::ivec2* point) {
		return Game::Grid::GetInstance().GetRandomHouseStructurePoint(point);
	}
	void GetAllAdjacentCells_Engine(MonoArray* monoArray, int* count, int x, int y) {
		Math::ivec2 arr[4];
		Game::Grid::GetInstance().GetAllAdjacentCells(arr, count, x, y);
		int loop = *count;
		for (int i = 0; i < loop; i++) {
			mono_array_set(monoArray, Math::ivec2, i, (arr[i]));
		}
	}
	void GetWalkableAdjacentCells_Engine(MonoArray* monoArray, int* count, int x, int y, bool isAgent) {
		Math::ivec2 arr[4];
		Game::Grid::GetInstance().GetWalkableAdjacentCells(arr, count, x, y, isAgent);
		int loop = *count;
		for (int i = 0; i < loop; i++) {
			mono_array_set(monoArray, Math::ivec2, i, (arr[i]));
		}
	}
	void GetAdjacentCellsOfType_Engine(MonoArray* monoArray, int* count, int x, int y, int type) {
		/*Math::ivec2 arr[4];
		Game::Grid::GetInstance().GetAdjacentCellsOfType(arr, count, x, y, type);
		int loop = *count;
		for (int i = 0, int index = 0; i < loop; i++) {
			if (GRID_NULL_VALUE_CHECK(arr[i].x) && GRID_NULL_VALUE_CHECK(arr[i].y)) {
				mono_array_set(monoArray, Math::ivec2, index, (arr[i]));
				index++;
			}
		}*/
		Math::ivec2 arr[4];
		Game::Grid::GetInstance().GetAdjacentCellsOfType(arr, count, x, y, type);
		int loop = *count;
		for (int i = 0; i < loop; i++) {
			mono_array_set(monoArray, Math::ivec2, i, (arr[i]));
		}
	}

	void GetAllAdjacentCellTypes_Engine(MonoArray* monoArray, int x, int y) {
		int arr[4];
		Game::Grid::GetInstance().GetAllAdjacentCellTypes(arr, x, y);
		for (int i = 0; i < 4; i++) {
			mono_array_set(monoArray, int, i, (arr[i]));
		}
	}


	int SetRoad_Engine(MonoArray* monoArray, int size) {
		Math::ivec2 posArr[MAX_LINE]{};

		if (size > MAX_LINE) std::cout << "SetRoad_Engine size is more than MAX_LINE\n";

		for (int i = 0; i < size; i++) {
			posArr[i] = mono_array_get(monoArray, Math::ivec2, i);
		}
		return Game::Grid::GetInstance().SetRoads(posArr, size);
	}

	bool UnsetRoad_Engine(Math::ivec2 pos) {
		return Game::Grid::GetInstance().UnsetRoads(pos);
	}

	void RevertGrid_Engine() {
		Game::Grid::GetInstance().RevertGrid();
	}

	void FinalizeGrid_Engine() {
		Game::Grid::GetInstance().FinalizeGrid();
	}

	bool IsWithinGrid_Engine(Math::ivec2 pos) {
		return Game::Grid::GetInstance().IsWithinGrid(pos);
	}

	bool IsPosFree_Engine(Math::ivec2 pos) {
		return Game::Grid::GetInstance().IsPosFree(pos);
	}

	bool IsSurrounded_Engine(Math::ivec2 pos) {
		return Game::Grid::GetInstance().IsSurrounded(pos);
	}

	void AStarSearch_Engine(MonoArray* monoArray, int* count, Math::ivec2 startPosition, Math::ivec2 endPosition, Math::ivec2 housePos, Math::ivec2 destPos, bool isAgent) {
		Math::vec2 arr[MAX_WAYPOINTS];
		Game::Grid::GetInstance().AStarSearch(arr, count, startPosition, endPosition, housePos, destPos, isAgent);
		int loop = *count;
		for (int i = 0; i < loop; i++) {
			std::cout << arr[i] << " before\n";
			mono_array_set(monoArray, Math::vec2, i, (arr[i]));
		}
	}

	void PrintGridOut_Engine() {
		Game::Grid::GetInstance().PrintGridOut_Engine();
	}
}