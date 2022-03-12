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

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/Grid/Grid.hpp"
#include "Engine/Header/Random/Random.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Serialize/GameSceneSerializer.hpp" //Deserialize Prefab

#include <map>

#define GET_BIN(num) (1 << (int)num)

#define SET_VALUE(type1, type2, var, value) type1.var = type2.var = value;

namespace Engine {
    namespace Game {
        std::array<Math::ivec2, 100> temporaryRoad;
        int temporarySize;

        std::list<Math::ivec2> Cell::GetAdjacent() {
            bool leftDir = (cellBinary & (1 << (int)CellDirection::Left));
            bool rightDir = (cellBinary & (1 << (int)CellDirection::Right));
            bool upDir = (cellBinary & (1 << (int)CellDirection::Up));
            bool downDir = (cellBinary & (1 << (int)CellDirection::Down));

            std::list < Math::ivec2> listPos{};
            if (leftDir) listPos.emplace_back(adjacentCell[(int)CellDirection::Left]);
            if (rightDir) listPos.emplace_back(adjacentCell[(int)CellDirection::Right]);
            if (upDir) listPos.emplace_back(adjacentCell[(int)CellDirection::Up]);
            if (downDir) listPos.emplace_back(adjacentCell[(int)CellDirection::Down]);

            return listPos;
        }

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
            backupGrid = CreateCellPtr(width, height);
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
            DeleteCellPtr(backupGrid, mapSize.x);

            grid = temGrid;
            temGrid = nullptr;

            mapSize.x = newWidth;
            mapSize.y = newHeight;

            offset.x -= xTem;
            offset.y -= yTem;

            backupGrid = CreateCellPtr(newWidth, newHeight);
            FinalizeGrid();

            //std::cout << "offset " << offset.x << " " << offset.y << "-------------------------------------\n";
            //std::cout << mapSize.x << " " << mapSize.y << "\n";
            mapSize = { newWidth, newHeight };

        }

        void Grid::DestroyGrid() {
            if (grid != nullptr)
                DeleteCellPtr(grid, mapSize.x);
            if (backupGrid != nullptr)
                DeleteCellPtr(backupGrid, mapSize.x);
            grid = nullptr;
            backupGrid = nullptr;

            mapSize = { -1, -1 };
        }

        int Grid::GetCellType(int x, int y) {

            //return static_cast<int>((grid + x + (static_cast<size_t>(y) * mapSize.x))->ct);
            return static_cast<int>((*(grid + x - offset.x) + static_cast<size_t>(y) - offset.y)->ct);
        }

        void Grid::SetCellType(int x, int y, int cellType, unsigned int entityId) {
            //std::cout << " Set cell type now \n";
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
            //if (value == CellType::SpecialStructure)
            //{
            //    specialStructure.emplace_back(Math::ivec2{ x,y });
            //}
            /*else
            {
                specialStructure.remove(Math::ivec2{ x,y });
            }*/


            //*(grid + (x - offset.x) + (static_cast<size_t>(y - offset.y) * mapSize.x)) = Cell{value, entityId };
            int xVal = x - offset.x, yVal = y - offset.y;
            *(*(grid + xVal) + yVal) = Cell{value, entityId };
            *(*(backupGrid + xVal) + yVal) = Cell{value, entityId };

            if (value == CellType::SpecialStructure)
            {
                //1 2
                //3 4
                specialStructure.emplace_back(Math::ivec2{ x,y });
                auto& currentCell = *(*(grid + xVal) + yVal);
                auto& rightCell = *(*(grid + xVal + 1) + yVal); //2
                auto& downCell = *(*(grid + xVal) + yVal + 1); //3
                auto& downRightCell = *(*(grid + xVal + 1) + yVal + 1); //4

                auto& currentCellBU = *(*(backupGrid + xVal) + yVal);
                auto& rightCellBU = *(*(backupGrid + xVal + 1) + yVal); //2
                auto& downCellBU = *(*(backupGrid + xVal) + yVal + 1); //3
                auto& downRightCellBU = *(*(backupGrid + xVal + 1) + yVal + 1); //4

#if 0
                currentCellBU.adjacentCell[(int)CellDirection::Right] = currentCell.adjacentCell[(int)CellDirection::Right] = Math::ivec2{ xVal + 1, yVal };
                currentCellBU.adjacentCell[(int)CellDirection::Down] = currentCell.adjacentCell[(int)CellDirection::Down] = Math::ivec2{ xVal, yVal + 1 };

                rightCellBU.ct = rightCell.ct = value;
                rightCellBU.entityId = rightCell.entityId = entityId;
                rightCellBU.adjacentCell[(int)CellDirection::Left] = rightCell.adjacentCell[(int)CellDirection::Left] = Math::ivec2{ xVal, yVal };
                rightCellBU.adjacentCell[(int)CellDirection::Down] = rightCell.adjacentCell[(int)CellDirection::Down] = Math::ivec2{ xVal + 1, yVal + 1 };

                downCellBU.ct = downCell.ct = value;
                downCellBU.entityId = downCell.entityId = entityId;
                downCellBU.adjacentCell[(int)CellDirection::Up] = downCell.adjacentCell[(int)CellDirection::Up] = Math::ivec2{ xVal, yVal };
                downCellBU.adjacentCell[(int)CellDirection::Right] = downCell.adjacentCell[(int)CellDirection::Right] = Math::ivec2{ xVal + 1, yVal + 1 };

                downRightCellBU.ct = downRightCell.ct = value;
                downRightCellBU.entityId = downRightCell.entityId = entityId;
                downRightCellBU.adjacentCell[(int)CellDirection::Up] = downRightCell.adjacentCell[(int)CellDirection::Up] = Math::ivec2{ xVal + 1, yVal };
                downRightCellBU.adjacentCell[(int)CellDirection::Left] = downRightCell.adjacentCell[(int)CellDirection::Left] = Math::ivec2{ xVal, yVal + 1};
#else
                //SET_VALUE(currentCellBU, currentCell, cellBinary, GET_BIN(CellDirection::Right) | GET_BIN(CellDirection::Down));
                //SET_VALUE(currentCellBU, currentCell, adjacentCell[(int)CellDirection::Right], (Math::ivec2{ xVal + 1, yVal }));
                //SET_VALUE(currentCellBU, currentCell, adjacentCell[(int)CellDirection::Down], (Math::ivec2{ xVal, yVal + 1 }));


                SET_VALUE(rightCellBU, rightCell, ct, value);
                SET_VALUE(rightCellBU, rightCell, entityId, entityId);
                //SET_VALUE(rightCellBU, rightCell, cellBinary, GET_BIN(CellDirection::Left) | GET_BIN(CellDirection::Down));
                //SET_VALUE(rightCellBU, rightCell, adjacentCell[(int)CellDirection::Left], (Math::ivec2{ xVal, yVal }));
                //SET_VALUE(rightCellBU, rightCell, adjacentCell[(int)CellDirection::Down], (Math::ivec2{ xVal + 1, yVal + 1 }));
                
                SET_VALUE(downCellBU, downCell, ct, value);
                SET_VALUE(downCellBU, downCell, entityId, entityId);
                //SET_VALUE(downCellBU, downCell, cellBinary, GET_BIN(CellDirection::Up) | GET_BIN(CellDirection::Right));
                //SET_VALUE(downCellBU, downCell, adjacentCell[(int)CellDirection::Up], (Math::ivec2{ xVal, yVal }));
                //SET_VALUE(downCellBU, downCell, adjacentCell[(int)CellDirection::Right], (Math::ivec2{ xVal + 1, yVal + 1 }));

                SET_VALUE(downRightCellBU, downRightCell, ct, value);
                SET_VALUE(downRightCellBU, downRightCell, entityId, entityId);
                //SET_VALUE(downRightCellBU, downRightCell, cellBinary, GET_BIN(CellDirection::Up) | GET_BIN(CellDirection::Left));
                //SET_VALUE(downRightCellBU, downRightCell, adjacentCell[(int)CellDirection::Up], (Math::ivec2{ xVal + 1, yVal }));
                //SET_VALUE(downRightCellBU, downRightCell, adjacentCell[(int)CellDirection::Left], (Math::ivec2{ xVal, yVal + 1 }));
#endif


            }
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

        bool Grid::GetRandomHouseStructurePoint(Math::ivec2* pos) {
            //std::cout << "House Count " << houseStructure.size() << "\n";
            int count = static_cast<int>(houseStructure.size()) - 1;
            if (count < 0) return false;

            int num;
            Random::Range(0, count, &num);
            std::list<Math::ivec2>::iterator it = houseStructure.begin();
            for (int i = 0; i < num; i++) {
                it++;
            }
            *pos = *it;

            return true;
        }

        void Grid::GetAllAdjacentCells(Math::ivec2(&arr)[4], int* count, int x, int y) {
            *count = 0;
            if (x > offset.x)
            {
                arr[*count] = Math::ivec2{ x - 1, y };
                (*count)++;
            }
            if (x < mapSize.x + offset.x - 1)
            {
                arr[*count] = Math::ivec2{ x + 1, y };
                (*count)++;
            }
            if (y > offset.y)
            {
                arr[*count] = Math::ivec2{ x, y - 1 };
                (*count)++;
            }
            if (y < mapSize.y + offset.y - 1)
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
                auto gridPTR = *(grid + temp[i].x - offset.x) +static_cast<size_t>(temp[i].y) - offset.y;
                if (IsCellWalkable(gridPTR->ct, isAgent) == true) {
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
                if (static_cast<int>((*(grid + temp[i].x - offset.x) + static_cast<size_t>(temp[i].y) - offset.y)->ct) == _type) {
                    arr[index] = temp[i];
                    index++;
                }
            }

            *count = index;
        }

        void Grid::GetAllAdjacentCellTypes(int(&arr)[4], int x, int y) {
            int none = static_cast<int>(CellType::None);
            arr[0] = none; arr[1] = none; arr[2] = none; arr[3] = none;

            if (x > offset.x) {
                //arr[0] = static_cast<int>((grid + (static_cast<size_t>(x) - 1) + (static_cast<size_t>(y) * mapSize.x))->ct);
                arr[0] = static_cast<int>((*(grid + static_cast<size_t>(x) - offset.x - 1) + static_cast<size_t>(y) - offset.y)->ct);
            }
            if (x < mapSize.x + offset.x - 1) {
                //arr[2] = static_cast<int>((grid + (static_cast<size_t>(x) + 1) + (static_cast<size_t>(y) * mapSize.x))->ct);
                arr[2] = static_cast<int>((*(grid + static_cast<size_t>(x) - offset.x + 1) + static_cast<size_t>(y) - offset.y)->ct);
            }
            if (y > offset.y) {
                //arr[3] = static_cast<int>((grid + x + ((static_cast<size_t>(y) - 1) * mapSize.x))->ct);
                arr[3] = static_cast<int>((*(grid + x - offset.x) + (static_cast<size_t>(y) - offset.y - 1))->ct);
            }
            if (y < mapSize.y + offset.y - 1) {
                //arr[1] = static_cast<int>((grid + x + ((static_cast<size_t>(y) + 1) * mapSize.x))->ct);
                arr[1] = static_cast<int>((*(grid + x - offset.x) + (static_cast<size_t>(y) - offset.y + 1))->ct);
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
            return static_cast<float>(std::abs(std::abs(endPos.x) - std::abs(point.x)) + std::abs(std::abs(endPos.y) - std::abs(point.y)));
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
            std::cout << "C++ grid print new map ----------------------------------------------------\n";
            std::vector<Math::ivec2> fv;
            std::vector<int> fg;
            std::vector<Math::ivec2> fp;
            for (int y = mapSize.y - 1; y >= 0; y--) {
                for (int x = 0; x < mapSize.x; x++) {
                    //if ((int)(((grid + (y * mapSize.x) + x))->ct) == 0) std::cout << "- ";
                    //else std::cout << (int)(((grid + (y * mapSize.x) + x))->ct) << " ";
                    if ((int)(  (*(grid + x) + y)->ct   ) == 0) std::cout << "- ";
                    else {
                        std::cout << (int)((*(grid + x) + y)->ct) << " ";
                        if (((*(grid + x) + y)->ct) == CellType::SpecialStructure) {
                            auto& tem = *(*(grid + x) + y);
                            fv.push_back({ x, y });

                            fg.push_back(tem.cellBinary);
                            
                            fp.push_back(tem.adjacentCell[(int)CellDirection::Left]);
                            fp.push_back(tem.adjacentCell[(int)CellDirection::Right]);
                            fp.push_back(tem.adjacentCell[(int)CellDirection::Up]);
                            fp.push_back(tem.adjacentCell[(int)CellDirection::Down]);
                        }
                    }
                }
                std::cout << "\n";
            }

            for (int i = 0; i < fv.size(); i++) {
                int t = 4 * i;
                std::cout << fv[i] << " with " << fg[i] << "     " << fp[t] << fp[t + 1] << fp[t + 2] << fp[t + 3] << "\n";
            }

            fv.clear(); fg.clear(); fp.clear();

            std::cout << "\n";
            std::cout << "C++ backup grid print new map ----------------------------------------------------\n";
            for (int y = mapSize.y - 1; y >= 0; y--) {
                for (int x = 0; x < mapSize.x; x++) {
                    //if ((int)(((grid + (y * mapSize.x) + x))->ct) == 0) std::cout << "- ";
                    //else std::cout << (int)(((grid + (y * mapSize.x) + x))->ct) << " ";
                    if ((int)((*(backupGrid + x) + y)->ct) == 0) std::cout << "- ";
                    //else std::cout << (int)((*(backupGrid + x) + y)->ct) << " ";
                    else {
                        std::cout << (int)((*(backupGrid + x) + y)->ct) << " ";
                        if (((*(backupGrid + x) + y)->ct) == CellType::SpecialStructure) {
                            auto& tem = *(*(backupGrid + x) + y);
                            fv.push_back({ x, y });

                            fg.push_back(tem.cellBinary);

                            fp.push_back(tem.adjacentCell[(int)CellDirection::Left]);
                            fp.push_back(tem.adjacentCell[(int)CellDirection::Right]);
                            fp.push_back(tem.adjacentCell[(int)CellDirection::Up]);
                            fp.push_back(tem.adjacentCell[(int)CellDirection::Down]);
                        }
                    }
                }
                std::cout << "\n";
            }

            for (int i = 0; i < fv.size(); i++) {
                int t = 4 * i;
                std::cout << fv[i] << " with " << fg[i] << "     " << fp[t] << fp[t + 1] << fp[t + 2] << fp[t + 3] << "\n";
            }

            std::cout << "\n";

            std::cout << "-----------------------------------------------------------------\n";
        }

        bool Grid::IsWithinGrid(Math::ivec2 pos) {
            Math::ivec2 endPoint = mapSize + offset;
            if (pos.x >= offset.x && pos.x < endPoint.x && pos.y >= offset.y && pos.y < endPoint.y)
                return true;
            return false;
        }

        //Return true if free
        bool Grid::IsPosFree(Math::ivec2 pos) {
            const Cell& cell = *(*(grid + pos.x - offset.x) + pos.y - offset.y);
            if (cell.ct == CellType::Empty || cell.ct == CellType::None) return true;
            return false;
        }

        bool Grid::IsPosRoad(Math::ivec2 pos) {
            const Cell& cell = *(*(grid + pos.x - offset.x) + pos.y - offset.y);
            return cell.ct == CellType::Road;
        }

        //Return true if position is surrounded by at least one building
        bool Grid::IsSurrounded(Math::ivec2 pos, int type) {
            CellType cellType = (CellType)type;
            int xVal = pos.x - offset.x;
            int yVal = pos.y - offset.y;
            const Cell& cellL = *(*(grid + xVal - 1) + yVal);
            if (cellL.ct == CellType::SpecialStructure || cellL.ct == CellType::Structure) return true;

            const Cell& cellR = *(*(grid + xVal + 1) + yVal);
            if (cellR.ct == CellType::SpecialStructure || cellR.ct == CellType::Structure) return true;

            const Cell& cellU = *(*(grid + xVal) + yVal + 1);
            if (cellU.ct == CellType::SpecialStructure || cellU.ct == CellType::Structure) return true;

            const Cell& cellD = *(*(grid + xVal) + yVal - 1);
            if (cellD.ct == CellType::SpecialStructure || cellD.ct == CellType::Structure) return true;

            if (cellType == CellType::SpecialStructure) {
                //C = Math::ivec2 pos (parameter)
                //() letter inside is one tile
                //(   ) ( UU) (RUU) (   ) 
                //( LU) (  U) ( RU) (RRU)
                //(  L) (  C) (  R) ( RR)
                //(   ) (  D) ( RD) (   )
                //Original checks L, R, U, D but actual tile size is 2x2 if its Special structure
                //So need to check LU, UU, RUU, RU, RRU, RR, RD
                const Cell& cellLU = *(*(grid + xVal - 1) + yVal + 1);
                if (cellLU.ct == CellType::SpecialStructure || cellLU.ct == CellType::Structure) return true;
                if (yVal + 2 < offset.y + mapSize.y) {
                    const Cell& cellUU = *(*(grid + xVal) + yVal + 2);
                    if (cellUU.ct == CellType::SpecialStructure || cellUU.ct == CellType::Structure) return true;
                    const Cell& cellRUU = *(*(grid + xVal + 1) + yVal + 2);
                    if (cellRUU.ct == CellType::SpecialStructure || cellRUU.ct == CellType::Structure) return true;
                }
                const Cell& cellRU = *(*(grid + xVal + 1) + yVal + 1);
                if (cellRU.ct == CellType::SpecialStructure || cellRU.ct == CellType::Structure) return true;
                if (xVal + 2 < offset.x + mapSize.x) {
                    const Cell& cellRRU = *(*(grid + xVal + 2) + yVal + 1);
                    if (cellRRU.ct == CellType::SpecialStructure || cellRRU.ct == CellType::Structure) return true;
                    const Cell& cellRR = *(*(grid + xVal + 2) + yVal);
                    if (cellRR.ct == CellType::SpecialStructure || cellRR.ct == CellType::Structure) return true;
                }
                const Cell& cellRD = *(*(grid + xVal + 1) + yVal - 1);
                if (cellRD.ct == CellType::SpecialStructure || cellRD.ct == CellType::Structure) return true;
            }

            return false;
        }

        bool CheckAddPoints(Math::ivec2 cellPos, Cell& cell, Math::ivec2 posToAdd) {
            //for (int p = 0; p < (int)CellDirection::End; p++) {
            //    if (cell.adjacentCell[p] == posToAdd) return false;
            //}

            if (cell.cellBinary & GET_BIN(CellDirection::Left))
                if (cell.adjacentCell[(int)CellDirection::Left] == posToAdd) return false;
            if (cell.cellBinary & GET_BIN(CellDirection::Right))
                if (cell.adjacentCell[(int)CellDirection::Right] == posToAdd) return false;
            if (cell.cellBinary & GET_BIN(CellDirection::Up))
                if (cell.adjacentCell[(int)CellDirection::Up] == posToAdd) return false;
            if (cell.cellBinary & GET_BIN(CellDirection::Down))
                if (cell.adjacentCell[(int)CellDirection::Down] == posToAdd) return false;


            //Find direction 
            if (posToAdd.x < cellPos.x) {
                cell.adjacentCell[(int)CellDirection::Left] = posToAdd;
                cell.cellBinary |= GET_BIN(CellDirection::Left);
            }

            else if (posToAdd.x > cellPos.x) { 
                cell.adjacentCell[(int)CellDirection::Right] = posToAdd;
                cell.cellBinary |= GET_BIN(CellDirection::Right);
            }

            else if (posToAdd.y < cellPos.y) { 
                cell.adjacentCell[(int)CellDirection::Down] = posToAdd; 
                cell.cellBinary |= GET_BIN(CellDirection::Down);
            }

            else if (posToAdd.y > cellPos.y) { 
                cell.adjacentCell[(int)CellDirection::Up] = posToAdd;  
                cell.cellBinary |= GET_BIN(CellDirection::Up);
            }

            return true;
        }

        void CheckRemovePoints(Cell& cell, Math::ivec2 posToRemove) {
            if (cell.adjacentCell[(int)CellDirection::Left] == posToRemove) 
                cell.cellBinary ^= GET_BIN(CellDirection::Left);

            if (cell.adjacentCell[(int)CellDirection::Right] == posToRemove) 
                cell.cellBinary ^= GET_BIN(CellDirection::Right);
 
            if (cell.adjacentCell[(int)CellDirection::Up] == posToRemove) 
                cell.cellBinary ^= GET_BIN(CellDirection::Up);

            if (cell.adjacentCell[(int)CellDirection::Down] == posToRemove) 
                cell.cellBinary ^= GET_BIN(CellDirection::Down);
            //std::cout << "Cell binary " << cell.cellBinary << "\n";
        }

        bool AllowDeletableCheck(CellType ct) {
            if (ct == CellType::Road || ct == CellType::None || ct == CellType::Empty) return true;
            return false;
        }

        std::string GetRoadType(const Cell& cell, float& angle) {
            bool leftDir = (cell.cellBinary & GET_BIN(CellDirection::Left));
            bool rightDir = (cell.cellBinary & GET_BIN(CellDirection::Right));
            bool upDir = (cell.cellBinary & GET_BIN(CellDirection::Up));
            bool downDir = (cell.cellBinary & GET_BIN(CellDirection::Down));

            int cellCount = ((int)leftDir + (int)rightDir + (int)upDir + (int)downDir);

            if (cellCount == 1) {
                if (leftDir) angle = -90.f;
                else if (rightDir) angle = 90.f;
                else if (upDir) angle = 180.f;
                else if (downDir) angle = 0.f;
                return "EndRoad";
            }

            else if (cellCount == 2) {
                if (leftDir && rightDir) angle = 90.f;
                else if (upDir && downDir) angle = 0.f;
                else {
                    //Which curve is this?
                    if (leftDir) {
                        if (upDir) angle = 180.f;
                        else if (downDir) angle = -90.f;
                    }

                    else if (rightDir) {
                        if (upDir) angle = 90.f;
                        else if (downDir) angle = 0.f;
                    }
                    return "CurveRoad";
                }
                //For the if and else if
                return "StraightRoad";
            }

            else if (cellCount == 3) {
                if (!leftDir) angle = 90.f;
                if (!rightDir) angle = -90.f;
                else if (!upDir) angle = 0.f;
                else if (!downDir) angle = 180.f;

                return "ThreeWayRoad";
            }

            else if (cellCount == 4) return "FourWayRoad";

            //LOG_WARNING("Grid.cpp GetRoadType cellCount is not recognized");
            //Empty (No Road)
            return "";
            
        }

        //Return false if no cell is replacing it = removing road tile completely
        bool UpdateCell(Cell& cell, const Math::ivec2& vec) {
            if (cell.entityId != 0) dreamECSGame->DestroyEntity(cell.entityId);
            cell.entityId = 0;
            float angle = 0.f;
            std::string type = GetRoadType(cell, angle);
            if (type.size() == 0) {
                cell.ct = CellType::Empty;
                return false;
            }
            GameSceneSerializer::DeserializePrefab(type, &(cell.entityId), Math::vec2{ (float)vec.x, (float)vec.y }, angle, 1);
            return true;
        }

        void UpdateCellWithCell(Cell& cell, Cell& oldCell, const Math::ivec2& vec) {
            if (cell.entityId != 0) dreamECSGame->DestroyEntity(cell.entityId);
            cell.entityId = 0;
            float angle = 0.f;
            std::string type = GetRoadType(oldCell, angle);
            if (type.size() == 0) return;
            GameSceneSerializer::DeserializePrefab(type, &(oldCell.entityId), Math::vec2{ (float)vec.x, (float)vec.y }, angle, 1);
        }

        int Grid::SetRoads(Math::ivec2 posArr[MAX_LINE], int size) {
            //Add roads
            //All position in posArr will be added (excluding duplicates), this will be used to spawn the prefab
            std::map<Math::ivec2, bool> instantiatePos;
            int noOfRoadToAdd = 0;
            temporarySize = size;
            for (int i = 0; i < size; i++) {
                temporaryRoad[i] = posArr[i];

                Cell& cellC = *(*(grid + posArr[i].x - offset.x) + posArr[i].y - offset.y);
                Cell& cellB = i != 0         ? *(*(grid + posArr[i - 1].x - offset.x) + posArr[i - 1].y - offset.y) : cellC;
                Cell& cellF = i != size - 1  ? *(*(grid + posArr[i + 1].x - offset.x) + posArr[i + 1].y - offset.y) : cellC;

                if (cellC.ct == CellType::Structure || cellC.ct == CellType::SpecialStructure) {
                    //house/destination already has connected point
                    if (cellC.cellBinary != 0) continue;

                    if (cellC.ct == CellType::SpecialStructure) {
                        int xVal = posArr[i].x - offset.x;
                        int yVal = posArr[i].y - offset.y;
                        //Check a 2x2 box around current point for the other parts of the special structure
                        Cell& cellL = *(*(grid + xVal - 1) + yVal);
                        //Do Note that in the first if and else, we do not know whether it is on top or below
                        //If L = cellL, S = special structure, C = cellC, - = ignore
                        //SS
                        //LC //L is part of the special structure
                        if (cellL.ct == CellType::SpecialStructure) {
                            if (cellL.cellBinary != 0) continue;
                            //U = cellU
                            //SU
                            //LC //U is part of the special structure
                            Cell& cellU = *(*(grid + xVal) + yVal + 1);
                            if (cellU.ct == CellType::SpecialStructure) {
                                if (cellU.cellBinary != 0) continue;
                    
                                //Check Up Left
                                Cell& cellUL = *(*(grid + xVal - 1) + yVal + 1);
                                if (cellUL.cellBinary != 0) continue;
                            }
                            //-U
                            //LC //U is not part of the special structure
                            //SS
                            else {
                                Cell& cellD = *(*(grid + xVal) + yVal - 1);
                                if (cellD.cellBinary != 0) continue;
                                //Check Down Left
                                Cell& cellDL = *(*(grid + xVal - 1) + yVal - 1);
                                if (cellDL.cellBinary != 0) continue;
                            }
                        }
                        //If L = cellL, S = special structure and C = cellC
                        //-SS
                        //LCS //L is not part of the special structure
                        else {
                            Cell& cellR = *(*(grid + xVal + 1) + yVal);
                            if (cellR.cellBinary != 0) continue;
                            //U = cellU
                            //-US
                            //LCS   //U is part of the special structure
                            Cell& cellU = *(*(grid + xVal) + yVal + 1);
                            if (cellU.ct == CellType::SpecialStructure) {
                                if (cellU.cellBinary != 0) continue;
                                //Check Up Right
                                Cell& cellUR = *(*(grid + xVal + 1) + yVal + 1);
                                if (cellUR.cellBinary != 0) continue;
                            }
                            //-U-
                            //LCS   //U is not part of the special structure
                            //-SS
                            else {
                                Cell& cellD = *(*(grid + xVal) + yVal - 1);
                                if (cellD.cellBinary != 0) continue;
                                //Check Down Right
                                Cell& cellDR = *(*(grid + xVal + 1) + yVal - 1);
                                if (cellDR.cellBinary != 0) continue;
                            }
                        }
                    }
                    //Since points doesnt add house/destination as adjacentCell
                    //It has to be done here when the house/destination choose which point it wants to be connected to
                    //the lines are noted with a (*Done here*)
                        
                    //Always choose the position before house/destination to be the connected point
                    if (i != 0) {
                        //cellC.adjacentCell[cellC.cellCount] = posArr[i - 1];
                        CheckAddPoints(posArr[i], cellC, posArr[i - 1]);
                        bool changes = CheckAddPoints(posArr[i - 1], cellB, posArr[i]); //*Done here*
                        instantiatePos[posArr[i - 1]] |= changes;
                    }
                    //But if house/destination is first, choose the point after
                    else {
                        //cellC.adjacentCell[cellC.cellCount] = posArr[i + 1];
                        CheckAddPoints(posArr[i], cellC, posArr[i + 1]);
                        bool changes = CheckAddPoints(posArr[i + 1], cellF, posArr[i]); //*Done here*
                        instantiatePos[posArr[i + 1]] |= changes;
                    }


                    //Skip the other checks and add point
                    continue; 
                }

                if (cellC.ct == CellType::Empty || cellC.ct == CellType::None) 
                    ++noOfRoadToAdd;
                //Only add points if it is CellType (None, Empty, Road) 
                //CellType (Structure and SpecialStructure) are stopped above
                cellC.ct = CellType::Road;
                bool changes = false;
                if (i != 0        && AllowDeletableCheck(cellB.ct)) changes |= CheckAddPoints(posArr[i], cellC, posArr[i - 1]);
                if (i != size - 1 && AllowDeletableCheck(cellF.ct)) changes |= CheckAddPoints(posArr[i], cellC, posArr[i + 1]);

                instantiatePos[posArr[i]] |= changes;
            }

            for (auto& [vec, changes] : instantiatePos) {
                Cell& cell = *(*(grid + vec.x - offset.x) + vec.y - offset.y);
                //Destroy the previous entity
                if (changes) {
                    //temporaryRoad[temporarySize] = vec;
                    //temporarySize++;

                    UpdateCell(cell, vec);
                }
            }

            return noOfRoadToAdd;
        }

        int Grid::UnsetRoads(Math::ivec2 pos) {
            if (!IsWithinGrid(pos)) return false;
            
            Cell& cell = *(*(grid + pos.x - offset.x) + pos.y - offset.y);

            if (cell.entityId == EMPTY_ENTITY || cell.ct != CellType::Road) return 0;
            dreamECSGame->DestroyEntity(cell.entityId);
            cell.entityId = EMPTY_ENTITY;
            
            int roadRemoved = 1;
            bool leftDir = (cell.cellBinary & GET_BIN(CellDirection::Left));
            bool rightDir = (cell.cellBinary & GET_BIN(CellDirection::Right));
            bool upDir = (cell.cellBinary & GET_BIN(CellDirection::Up));
            bool downDir = (cell.cellBinary & GET_BIN(CellDirection::Down));

            cell.ct = CellType::Empty;
            cell.cellBinary = 0;

            Math::ivec2 removePos{};
            if (leftDir) {
                removePos = cell.adjacentCell[(int)CellDirection::Left];
                Cell& cellT = *(*(grid + removePos.x - offset.x) + removePos.y - offset.y);
                cellT.cellBinary ^= GET_BIN(CellDirection::Right);
                //cellT.adjacentCell[(int)CellDirection::Right] = removePos; //Prevent the previous position from being the same and not adding
                if (cellT.ct == CellType::Road)
                    //UpdateCell(cellT, removePos);
                    if (!UpdateCell(cellT, removePos)) ++roadRemoved;
            }

            if (rightDir) {
                removePos = cell.adjacentCell[(int)CellDirection::Right];
                Cell& cellT = *(*(grid + removePos.x - offset.x) + removePos.y - offset.y);
                cellT.cellBinary ^= GET_BIN(CellDirection::Left);
                if (cellT.ct == CellType::Road)
                    //UpdateCell(cellT, removePos);
                    if (!UpdateCell(cellT, removePos)) ++roadRemoved;
            }

            if (upDir) {
                removePos = cell.adjacentCell[(int)CellDirection::Up];
                Cell& cellT = *(*(grid + removePos.x - offset.x) + removePos.y - offset.y);
                cellT.cellBinary ^= GET_BIN(CellDirection::Down);
                if (cellT.ct == CellType::Road)
                    //UpdateCell(cellT, removePos);
                    if (!UpdateCell(cellT, removePos)) ++roadRemoved;
            }

            if (downDir) {
                removePos = cell.adjacentCell[(int)CellDirection::Down];
                Cell& cellT = *(*(grid + removePos.x - offset.x) + removePos.y - offset.y);
                cellT.cellBinary ^= GET_BIN(CellDirection::Up);
                if (cellT.ct == CellType::Road)
                    //UpdateCell(cellT, removePos);
                    if (!UpdateCell(cellT, removePos)) ++roadRemoved;
            }

            FinalizeGrid();

            return roadRemoved;
        }

        void Grid::RevertGrid() {
#if 0
            for (int i = 0; i < temporarySize; i++) {
                Cell& cell = *(*(grid + temporaryRoad[i].x) + temporaryRoad[i].y);
                if (i != 0) CheckRemovePoints(cell, temporaryRoad[i - 1]);
                if (i != temporarySize - 1) CheckRemovePoints(cell, temporaryRoad[i + 1]);
                
                //std::cout << "Current cell " << cell.cellBinary << "\n";
                //if (cell.entityId != 0) dreamECSGame->DestroyEntity(cell.entityId);
            } 
            //std::cout << "\n";
            for (int i = 0; i < temporarySize; i++) {
                Cell& cell = *(*(grid + temporaryRoad[i].x) + temporaryRoad[i].y);
                if (!AllowDeletableCheck(cell.ct)) continue;
                if (cell.cellBinary == 0) cell.ct = CellType::Empty;
                UpdateCell(cell, temporaryRoad[i]);
            }

            temporarySize = 0;
#else
            for (int y = mapSize.y - 1; y >= 0; y--) {
                for (int x = 0; x < mapSize.x; x++) {
                    Cell& cell = *(*(grid + x) + y);
                    Cell& oldCell = *(*(backupGrid + x) + y);
                    if (cell.ct == CellType::Road) 
                        UpdateCellWithCell(cell, oldCell, Math::ivec2(x, y));
                    cell = oldCell;
                }
            }
#endif
        }

        void Grid::FinalizeGrid() {
            temporarySize = 0;

            //std::cout << "Finalize called -------------------------------------------------------\n";
            for (int y = mapSize.y - 1; y >= 0; y--) {
                for (int x = 0; x < mapSize.x; x++) {
                    *(*(backupGrid + x) + y) = *(*(grid + x) + y);
                }
            }
        }

        void Grid::AStarSearch(Math::vec2(&arr)[MAX_WAYPOINTS], int* count, Math::ivec2 housePos, Math::ivec2 destPos, int* roadCount) {
            std::list<Math::ivec2> vlist = AStarSearchInternal(housePos, destPos, roadCount);
            //vlist.reverse();
            
            int index = *count = 0;
            if (vlist.size() == 0) return;

            ////Remove the housePos and destPos
            //vlist.pop_front();
            //vlist.pop_back();

            //std::cout << "\n " << vlist.size() << " Starting of A Star(C++)---------------------------------- - \n";

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

            Math::ivec2 prevPosition = housePos;
            Math::ivec2 nextPosition{};
            while(vlist.size() > 0) {
                Math::ivec2 pos = vlist.front();
                auto& entId = (*(grid + pos.x - offset.x) + pos.y - offset.y)->entityId;

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
                    if (t.size() == 0) return; //If road was deleted while points are added
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
                        //std::cout << "Adding point " << pt << "\n";
                        index++;
                    }
                    //std::cout << "\n\n";
                
                    break;
                }
                if (!added) LOG_WARNING("Grid.cpp waypoint is not added for ", pos);
                
                prevPosition = pos;
            }

            path[index] = destPos;
            index++;

            //std::cout << " New start --------------------\n";
            for (int i = 0; i < index; i++) {
                arr[i] = path[i];
                //std::cout << arr[i] << "\n";
            }
            //std::cout << " New end --------------------\n";
#else

            for (auto& i : vlist) {
                arr[index] = i;
                index++;
            }

            arr[index] = destPos;
            index++;
#endif


            //std::cout << "Start and end " << arr[0] << " " << arr[index - 1] << "\n";
            //std::cout << "End of A Star -----------------------------------\n";
            *count = index;
        }

        std::list<Math::ivec2> Grid::AStarSearchInternal(Math::ivec2 startPosition, Math::ivec2& endPosition, int* roadCount) {
            *roadCount = 0;
            Math::ivec2 endRight = endPosition + Math::ivec2{ 1,0 };
            Math::ivec2 endUp = endPosition + Math::ivec2{ 0,1 };
            Math::ivec2 endUpRight = endPosition + Math::ivec2{ 1,1 };

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
                Cell& cell = *(*(backupGrid + current.x - offset.x) + current.y - offset.y);
                if (cell.ct == CellType::SpecialStructure && 
                    (current == endPosition || current == endRight || current == endUp || current == endUpRight)) {
                    path = GeneratePath(parentsDictionary, current);
                    path.reverse();

                    //Remove the housePos and destPos
                    path.pop_front();
                    path.pop_back();

                    if (current == endRight) endPosition = endRight;
                    else if (current == endUp) endPosition = endUp;
                    else if (current == endUpRight) endPosition = endUpRight;
                    *roadCount = (int)path.size();

                    return path;
                }

                //std::list<Math::ivec2> temp = GetAdjacentCells(current, isAgent);
                std::list<Math::ivec2> temp = cell.GetAdjacent();
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
