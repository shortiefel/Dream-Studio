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

#include "Engine/Header/ECS/DreamECS.hpp"

#include <map>

namespace Engine {
    namespace Game {
        Cell** CreateCellPtr(int width, int height) {
            //Cell* grid = new Cell[static_cast<size_t>(width) * static_cast<size_t>(height)]();
            //
            //for (int y = 0; y < height; y++) {
            //    for (int x = 0; x < width; x++) {
            //        *(grid + (y * width) + x) = Cell{};
            //    }
            //}

            Cell** newGrid = new Cell*[static_cast<size_t>(width)]();
            
            for (int x = 0; x < width; x++) {
                *(newGrid + x) = new Cell[static_cast<size_t>(height)]();
                for (int y = 0; y < height; y++) {
                    *(*(newGrid + x) + y) = Cell{};
                }
            }

            return newGrid;
        }

        void DeleteCellPtr(Cell** cellPtr, int width) {
            for (int x = 0; x < width; x++) {
                delete[] *(cellPtr + x);
            }

            delete[] cellPtr;
        }

        Math::ivec2 Grid::GetGridSize() {
            return mapSize;
        }

        Math::ivec2 Grid::GetStartPoint() {
            return offset;
        }

        void Grid::CreateGrid(int width, int height) {
            if (grid != nullptr) return;
            mapSize = { width, height };
            offset = { 0, 0 };

            grid = CreateCellPtr(width, height);
            //grid = new Cell[static_cast<size_t>(width) * static_cast<size_t>(height)]();
            //
            //for (int y = 0; y < mapSize.y; y++) {
            //    for (int x = 0; x < mapSize.x; x++) {
            //        *(grid + (y * mapSize.x) + x) = Cell{};
            //    }
            //}
        }

        void Grid::ResizeGrid(int newWidth, int newHeight) {
            int xTem = (newWidth - mapSize.x) / 2;
            int yTem = (newHeight - mapSize.y) / 2;

            //int xOffset = _startX + xTem;
            //int yOffset = _startY + yTem;
            


            /*int xOffset = xTem;
            int yOffset = yTem;
            xOffset -= _startX;
            yOffset -= _startY;
            _startX = xTem;
            _startY = yTem;*/

            Cell** temGrid = CreateCellPtr(newWidth, newHeight);

            //Offset and store into the new grid
            for (int y = 0; y < mapSize.y; y++) {
                for (int x = 0; x < mapSize.x; x++) {
                    *(*(temGrid + x + xTem) + (y + yTem)) = *(*(grid + x) + y);
                }
            }
            DeleteCellPtr(grid, mapSize.x);
            grid = temGrid;
            temGrid = nullptr;

            mapSize.x = newWidth;
            mapSize.y = newHeight;


            offset.x -= xTem;
            offset.y -= yTem;

            std::cout << "offset " << offset.x << " " << offset.y << "-------------------------------------\n";
            std::cout << mapSize.x << " " << mapSize.y << "\n";
            mapSize = { newWidth, newHeight };

        }

        void Grid::DestroyGrid() {
            if (grid != nullptr)
                DeleteCellPtr(grid, mapSize.x);
            grid = nullptr;

            mapSize = { -1, -1 };
        }

        int Grid::GetCellType(int x, int y) {

            //return static_cast<int>((grid + x + (static_cast<size_t>(y) * mapSize.x))->ct);
            return static_cast<int>((*(grid + x ) + static_cast<size_t>(y))->ct);
        }

        void Grid::SetCellType(int x, int y, int cellType, unsigned int entityId) {
            //y = mapSize.y - 1 - y + offset.y;
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


            //*(grid + (x - offset.x) + (static_cast<size_t>(y - offset.y) * mapSize.x)) = Cell{value, entityId };
            *(*(grid + x - offset.x) + y - offset.y) = Cell{value, entityId };


            //Store the entityId to the points
            //posToId()
        }

        bool IsCellWalkable(CellType cellType, bool aiAgent = false) {
            if (aiAgent) return cellType == CellType::Road;
            return cellType == CellType::Empty || cellType == CellType::Road;
        }

        bool Grid::GetRandomRoadPoint(Math::ivec2* pos) {
            int count = static_cast<int>(roadList.size()) - 1;
            if (count < 0) return false;
            /*int n = Random.Range(0, count);
            return _roadList[n];*/

            int num;
            Random::Range(0, count, &num);
            std::list<Math::ivec2>::iterator it = roadList.begin();
            for (int i = 0; i < num; i++) {
                it++;
            }
            *pos = *it;

            return true;
        }

        bool Grid::GetRandomSpecialStructurePoint(Math::ivec2* pos) {
            int count = static_cast<int>(specialStructure.size()) - 1;
            if (count < 0) return false;

            int num;
            Random::Range(0, count, &num);
            std::list<Math::ivec2>::iterator it = specialStructure.begin();
            for (int i = 0; i < num; i++) {
                it++;
            }
            *pos = *it;

            return true;
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
                //if (IsCellWalkable((grid + (temp[i].x) + (static_cast<size_t>(temp[i].y) * mapSize.x))->ct, isAgent) == true) {
                if (IsCellWalkable((*(grid + temp[i].x) + static_cast<size_t>(temp[i].y))->ct, isAgent) == true) {
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
                //if (static_cast<int>((grid + (temp[i].x) + (static_cast<size_t>(temp[i].y) * mapSize.x))->ct) == _type) {
                if (static_cast<int>((*(grid + temp[i].x) + static_cast<size_t>(temp[i].y))->ct) == _type) {
                    arr[index] = temp[i];
                    index++;
                }
            }

            *count = index;
        }

        void Grid::GetAllAdjacentCellTypes(int(&arr)[4], int x, int y) {
            int none = static_cast<int>(CellType::None);
            arr[0] = none; arr[1] = none; arr[2] = none; arr[3] = none;

            if (x > 0) {
                //arr[0] = static_cast<int>((grid + (static_cast<size_t>(x) - 1) + (static_cast<size_t>(y) * mapSize.x))->ct);
                arr[0] = static_cast<int>((*(grid + static_cast<size_t>(x) - 1) + static_cast<size_t>(y))->ct);
            }
            if (x < mapSize.x - 1) {
                //arr[2] = static_cast<int>((grid + (static_cast<size_t>(x) + 1) + (static_cast<size_t>(y) * mapSize.x))->ct);
                arr[2] = static_cast<int>((*(grid + static_cast<size_t>(x) + 1) + static_cast<size_t>(y))->ct);
            }
            if (y > 0) {
                //arr[3] = static_cast<int>((grid + x + ((static_cast<size_t>(y) - 1) * mapSize.x))->ct);
                arr[3] = static_cast<int>((*(grid + x) + (static_cast<size_t>(y) - 1))->ct);
            }
            if (y < mapSize.y - 1) {
                //arr[1] = static_cast<int>((grid + x + ((static_cast<size_t>(y) + 1) * mapSize.x))->ct);
                arr[1] = static_cast<int>((*(grid + x) + (static_cast<size_t>(y) + 1))->ct);
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

        void Grid::PrintGridOut_Engine() {
            std::cout << "C++ print new map \n";
            
            for (int y = mapSize.y - 1; y >= 0; y--) {
                for (int x = 0; x < mapSize.x; x++) {
                    //if ((int)(((grid + (y * mapSize.x) + x))->ct) == 0) std::cout << "- ";
                    //else std::cout << (int)(((grid + (y * mapSize.x) + x))->ct) << " ";
                    if ((int)(  (*(grid + x) + y)->ct   ) == 0) std::cout << "- ";
                    else std::cout << (int)(    (*(grid + x) + y)->ct   ) << " ";
                }
                std::cout << "\n";
            }

            std::cout << "\n";
        }

        void Grid::AStarSearch(Math::vec2(&arr)[MAX_LINE], int* count, Math::ivec2 startPosition, Math::ivec2 endPosition, Math::ivec2 housePos, Math::ivec2 destPos, bool isAgent) {
            std::list<Math::ivec2> vlist = AStarSearchInternal(startPosition, endPosition, isAgent);
            vlist.reverse();
            
            int index = 0;
            std::cout << "\n Starting of A Star (C++)-----------------------------------\n";

            //How it works vlist contains the roads the car will have to follow
            //to get the individual routes u need to know which direction the car is going
            //1. In each road prefab, there could be multiple route(list of list of points)
            //2. In those route(inner list), the first position and last position are the position of where the car is coming from and where it is going to respectively
            //Example: A B C are the prefabs in game and We are currently looking at one possible route in B 
            //           D     Route: A 1 2 3 4 5 C are the lists of points for prefab B (first and last are the direction it would be going)
            //                 Another possible Route: A 6 7 8 9 D are the lists of points for prefab B (first and last are the direction it would be going) (this is going right and down)
            //3. To get the correct route, check the first prev position and the next position.
#if 1
            std::array<Math::vec2, 100> path{};

            //path[index] = housePos;
            //index++;

            Math::ivec2 prevPosition = housePos;
            Math::ivec2 nextPosition{};
            while(vlist.size() > 0) {
                Math::ivec2 pos = vlist.front();
                auto& entId = (*(grid + pos.x) + pos.y)->entityId;

                //path[index] = vlist.front();
                //index++;
                vlist.pop_front();

                bool added = false;
                auto& wp = dreamECSGame->GetComponent<WaypointComponent>(entId);
                if (!wp.updated) {
                    TransformComponent& tc = dreamECSGame->GetComponent<TransformComponent>(entId);
                    float angle = tc.angle;
                    Math::vec2 position = tc.position;
                
                    float cosX = Math::cosDeg(angle);
                    float sinX = Math::sinDeg(angle);
                    Math::mat3 rotationAndTranslate{ cosX, sinX, 0.f, -sinX, cosX, 0.f, position.x, position.y, 1.f };
                
                    for (auto& listWP : wp.temWaypoint) {
                        int c = 0;
                        for (auto& t : listWP) {
                            Math::vec3 temVec{ t.x, t.y, 1.f };
                            temVec = rotationAndTranslate * temVec;
                            if (c == 0 || c == 1) {
                                temVec.x = round(temVec.x);
                                temVec.y = round(temVec.y);
                            }
                            t.x = temVec.x;
                            t.y = temVec.y;
                            c++;
                        }
                    }
                
                    wp.updated = true;
                }
                
                auto wpList = std::list<std::list<Math::vec2>>{ wp.temWaypoint };
                
                for (auto& t : wpList) {
                    
                    if (prevPosition == Math::ivec2{ (int)t.front().x, (int)t.front().y }) t.pop_front();
                    else continue;
                    if (vlist.size() == 0)
                        nextPosition = destPos;
                    else
                        nextPosition = vlist.front();
                
                    
                    if(nextPosition == Math::ivec2{ (int)t.front().x, (int)t.front().y }) t.pop_front();
                    else continue;
                
                    added = true;
                    
                    //std::cout << "for points " << path[index - 1] << "\n";
                    for (auto& pt : t) {
                        //Add all points in
                        path[index] = pt;
                        std::cout << "Adding point " << pt << "\n";
                        index++;
                    }
                    std::cout << "\n\n";
                
                    break;
                }
                if (!added) LOG_WARNING("Grid.cpp waypoint is not added for ", pos);
                
                prevPosition = pos;
            }

            path[index] = destPos;
            index++;

            std::cout << " New start --------------------\n";
            for (int i = 0; i < index; i++) {
                arr[i] = path[i];
                std::cout << arr[i] << "\n";
            }
            std::cout << " New end --------------------\n";
#else

            for (auto& i : vlist) {
                arr[index] = i;
                std::cout << arr[index] << "\n";
                index++;
            }

            arr[index] = destPos;
            std::cout << arr[index] << "\n";
            index++;
#endif


            //std::cout << "Start and end " << arr[0] << " " << arr[index - 1] << "\n";
            //std::cout << "End of A Star -----------------------------------\n";
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
            return path;
        }
    }
}
