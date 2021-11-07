/* Start Header**********************************************************************************/
/*
@file    GridInternalCall.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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
	void CreateGrid_Engine(int width, int height);
	int GetCellType_Engine(int x, int y);
	void SetCellType_Engine(int x, int y, int cellType);
	void GetRandomRoadPoint_Engine(Math::ivec2* point);
	void GetRandomSpecialStructurePoint_Engine(Math::ivec2* point);
	void GetAllAdjacentCells_Engine(MonoArray* monoArray, int* count, int x, int y);
	void GetWalkableAdjacentCells_Engine(MonoArray* monoArray, int* count, int x, int y, bool isAgent);
	void GetAdjacentCellsOfType_Engine(MonoArray* monoArray, int* count, int x, int y, int type);
	void GetAllAdjacentCellTypes_Engine(MonoArray* monoArray, int x, int y);

	void AStarSearch_Engine(MonoArray* monoArray, int* count, Math::ivec2 startPosition, Math::ivec2 endPosition, bool isAgent);

	void RegisterGridInternalCall() {
		/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
		Grid
		----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
		mono_add_internal_call("Grid::CreateGrid_Engine", CreateGrid_Engine);
		mono_add_internal_call("Grid::GetCellType_Engine", GetCellType_Engine);
		mono_add_internal_call("Grid::SetCellType_Engine", SetCellType_Engine);
		mono_add_internal_call("Grid::GetRandomRoadPoint_Engine", GetRandomRoadPoint_Engine);
		mono_add_internal_call("Grid::GetRandomSpecialStructurePoint_Engine", GetRandomSpecialStructurePoint_Engine);
		mono_add_internal_call("Grid::GetAllAdjacentCells_Engine", GetAllAdjacentCells_Engine);
		mono_add_internal_call("Grid::GetWalkableAdjacentCells_Engine", GetWalkableAdjacentCells_Engine);
		mono_add_internal_call("Grid::GetAdjacentCellsOfType_Engine", GetAdjacentCellsOfType_Engine);
		mono_add_internal_call("Grid::GetAllAdjacentCellTypes_Engine", GetAllAdjacentCellTypes_Engine);

		mono_add_internal_call("GridSearch::AStarSearch_Engine", AStarSearch_Engine);
	}

	void CreateGrid_Engine(int width, int height) {
		Game::Grid::GetInstance().CreateGrid(width, height);
	}
	int GetCellType_Engine(int x, int y) {
		return Game::Grid::GetInstance().GetCellType(x, y);
	}
	void SetCellType_Engine(int x, int y, int cellType) {
		Game::Grid::GetInstance().SetCellType(x, y, cellType);
	}
	void GetRandomRoadPoint_Engine(Math::ivec2* point) {
		Game::Grid::GetInstance().GetRandomRoadPoint(point);
	}
	void GetRandomSpecialStructurePoint_Engine(Math::ivec2* point) {
		Game::Grid::GetInstance().GetRandomSpecialStructurePoint(point);
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

	void AStarSearch_Engine(MonoArray* monoArray, int* count, Math::ivec2 startPosition, Math::ivec2 endPosition, bool isAgent) {
		Math::ivec2 arr[MAX_LINE];
		Game::Grid::GetInstance().AStarSearch(arr, count, startPosition, endPosition, isAgent);
		int loop = *count;
		for (int i = 0; i < loop; i++) {
			mono_array_set(monoArray, Math::ivec2, i, (arr[i]));
		}
	}
}