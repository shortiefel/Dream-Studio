/* Start Header**********************************************************************************/
/*
@file    Grid.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu   	100%
@date    29/10/2021
\brief
#include "Engine/Header/Grid/Grid.hpp"
This file contain the definition of Grid


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Grid/Grid.hpp"
#include "Engine/Header/Random/Random.hpp"

#include <map>

namespace Engine {
    namespace Game {
        void Grid::CreateGrid(int width, int height) {
            if (grid != nullptr) return;
            mapSize = { width, height };
            grid = new CellType[static_cast<size_t>(width) * static_cast<size_t>(height)]();
        }

        void Grid::DestroyGrid() {
            if (grid != nullptr)
                delete[] grid;

            grid = nullptr;
        }

        int Grid::GetCellType(int x, int y) {
            
            return static_cast<int>(*(grid + x + (static_cast<size_t>(y) * mapSize.x)));
        }

        void Grid::SetCellType(int x, int y, int cellType) {
            CellType value = static_cast<CellType>(cellType);

            if (value == CellType::Road)
            {
                roadList.emplace_back(Math::ivec2{ x,y });
            }
            /*else
            {
                roadList.remove(Math::ivec2{ x,y });
            }*/
            if (value == CellType::Structure)
            {
                houseStructure.emplace_back(Math::ivec2{ x,y });
            }
            /*else
            {
                houseStructure.remove(Math::ivec2{ x,y });
            }*/
            if (value == CellType::SpecialStructure)
            {
                specialStructure.emplace_back(Math::ivec2{ x,y });
            }
            /*else
            {
                specialStructure.remove(Math::ivec2{ x,y });
            }*/
            *(grid + x + (static_cast<size_t>(y) * mapSize.x)) = value;
        }

        bool IsCellWalkable(CellType cellType, bool aiAgent = false) {
            if (aiAgent) return cellType == CellType::Road;
            return cellType == CellType::Empty || cellType == CellType::Road;
        }

        void Grid::GetRandomRoadPoint(Math::ivec2* pos) {
            int num;
            Random::Range(0, static_cast<int>(roadList.size()) - 1, &num);
            std::list<Math::ivec2>::iterator it = roadList.begin();
            for (int i = 0; i < num; i++) {
                it++;
            }
            *pos = *it;
        }

        void Grid::GetRandomSpecialStructurePoint(Math::ivec2* pos) {
            int num;
            Random::Range(0, static_cast<int>(roadList.size()) - 1, &num);
            std::list<Math::ivec2>::iterator it = roadList.begin();
            for (int i = 0; i < num; i++) {
                it++;
            }
            *pos = *it;
        }

        void Grid::GetAllAdjacentCells(Math::ivec2(&arr)[4], int* count, int x, int y) {
            *count = 0;
            if (x > 0)
            {
                arr[*count] = Math::ivec2{ x - 1, y };
                (*count)++;
            }
            if (x < mapSize.x - 1)
            {
                arr[*count] = Math::ivec2{ x + 1, y };
                (*count)++;
            }
            if (y > 0)
            {
                arr[*count] = Math::ivec2{ x, y - 1 };
                (*count)++;
            }
            if (y < mapSize.y - 1)
            {
                arr[*count] = Math::ivec2{ x, y + 1 };
                (*count)++;
            }
        }

        void Grid::GetWalkableAdjacentCells(Math::ivec2(&arr)[4], int* count, int x, int y, bool isAgent) {
            Math::ivec2 temp[4];
            GetAllAdjacentCells(temp, count, x, y);
            int num = *count;
            int index = 0;
            for (int i = 0; i < num; i++) {
                if (IsCellWalkable(*(grid + (temp[i].x) + (static_cast<size_t>(temp[i].y) * mapSize.x)), isAgent) == true) {
                    arr[index] = temp[i];
                    index++;
                }
            }

            *count = index;
        }

        void Grid::GetAdjacentCellsOfType(Math::ivec2(&arr)[4], int* count, int x, int y, int _type) {
            Math::ivec2 temp[4];
            GetAllAdjacentCells(temp, count, x, y);
            int num = *count;
            int index = 0;
            for (int i = 0; i < num; i++) {
                if (static_cast<int>(*(grid + (temp[i].x) + (static_cast<size_t>(temp[i].y) * mapSize.x))) == _type) {
                    arr[index] = temp[i];
                    index++;
                }
            }

            *count = index;
        }

        void Grid::GetAllAdjacentCellTypes(int (&arr)[4], int x, int y) {
            int none = static_cast<int>(CellType::None);
            arr[0] = none; arr[1] = none; arr[2] = none; arr[3] = none;

            if (x > 0) {
                arr[0] = static_cast<int>(*(grid + (static_cast<size_t>(x) - 1) + (static_cast<size_t>(y) * mapSize.x)));
            }
            if (x < mapSize.x - 1) {
                arr[2] = static_cast<int>(*(grid + (static_cast<size_t>(x) + 1) + (static_cast<size_t>(y) * mapSize.x)));
            }
            if (y > 0) {
                arr[3] = static_cast<int>(*(grid + x + ((static_cast<size_t>(y) - 1) * mapSize.x)));
            }
            if (y < mapSize.y - 1) {
                arr[1] = static_cast<int>(*(grid + x + ((static_cast<size_t>(y) + 1) * mapSize.x)));
            }
        }

        float GetCostOfEnteringCell(Math::ivec2)
        {
            return 1;
        }

        /*----------------------------------------------------------------------------------------------------------------------------------------
        AI
        ----------------------------------------------------------------------------------------------------------------------------------------*/
        Math::ivec2 GetClosestVertex(std::list<Math::ivec2>& list, std::map<Math::ivec2, float> distanceMap) {
            Math::ivec2 candidate = list.front();
            for (const Math::ivec2& vertex : list)
            {
                if (distanceMap[vertex] < distanceMap[candidate])
                {
                    candidate = vertex;
                }
            }
            return candidate;
        }

        float ManhattanDistance(Math::ivec2 endPos, Math::ivec2 point) {
            return static_cast<float>(std::abs(endPos.x - point.x) + std::abs(endPos.y - point.y));
        }

        std::list<Math::ivec2> Grid::GetAdjacentCells(Math::ivec2 cell, bool isAgent) {
            Math::ivec2 arr[4]; 
            int count;
            GetWalkableAdjacentCells(arr, &count, cell.x, cell.y, isAgent);
            std::list<Math::ivec2> ivecList;
            for (int i = 0; i < count; i++) {
                ivecList.emplace_back(arr[i]);
            }
            return ivecList;
        }

        std::list<Math::ivec2> GeneratePath(std::map<Math::ivec2, Math::ivec2>& parentMap, Math::ivec2 endState) {
            std::list<Math::ivec2> path;
            Math::ivec2 parent = endState;
            //while (parent != null && parentMap.find(parent) != parentMap.end())
            while (GRID_NULL_VALUE_CHECK(parent) && parentMap.find(parent) != parentMap.end()) {
                path.emplace_back(parent);
                parent = parentMap[parent];
            }
            return path;
        }

        void Grid::AStarSearch(Math::ivec2(&arr)[MAX_LINE], int* count, Math::ivec2 startPosition, Math::ivec2 endPosition, bool isAgent) {
            const auto& vlist = AStarSearchInternal(startPosition, endPosition, isAgent);
            int index = 0;
            for (auto& i : vlist) {
                arr[index] = i;
                index++;
            }
            *count = index;
        }

        std::list<Math::ivec2> Grid::AStarSearchInternal(Math::ivec2 startPosition, Math::ivec2 endPosition, bool isAgent) {
            std::list<Math::ivec2> path;
            std::list<Math::ivec2> positionsTocheck;
            std::map<Math::ivec2, float> costDictionary;
            std::map<Math::ivec2, float> priorityDictionary;
            std::map<Math::ivec2, Math::ivec2> parentsDictionary;

            positionsTocheck.emplace_back(startPosition);
            priorityDictionary.emplace(startPosition, 0.f);
            costDictionary.emplace(startPosition, 0.f);
            parentsDictionary.emplace(startPosition, Math::ivec2{ GRID_NULL_VALUE, GRID_NULL_VALUE });

            while (positionsTocheck.size() > 0) {
                Math::ivec2 current = GetClosestVertex(positionsTocheck, priorityDictionary);
                positionsTocheck.remove(current);
                //std::cout << "Check " << current << " " << endPosition << "\n";;
                if (current == (endPosition)) {
                    path = GeneratePath(parentsDictionary, current);
                    return path;
                }

                std::list<Math::ivec2> temp = GetAdjacentCells(current, isAgent);
                for (Math::ivec2& neighbour : temp) {
                    float newCost = costDictionary[current] + GetCostOfEnteringCell(neighbour);
                    //if (!costDictionary.ContainsKey(neighbour) || newCost < costDictionary[neighbour])
                    if ((costDictionary.find(neighbour) == costDictionary.end()) || newCost < costDictionary[neighbour])
                    {
                        costDictionary[neighbour] = newCost;

                        float priority = newCost + ManhattanDistance(endPosition, neighbour);
                        positionsTocheck.emplace_back(neighbour);
                        priorityDictionary[neighbour] = priority;

                        parentsDictionary[neighbour] = current;
                    }
                }
            }
            std::cout << "Actually ending \n";
            return path;
        }
    }
}
