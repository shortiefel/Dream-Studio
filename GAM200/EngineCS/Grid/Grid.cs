﻿/* Start Header**********************************************************************************/
/*
@file    Grid.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    06/11/2021
\brief
This file has the function definition for Grid


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Collections.Generic;
using System.Runtime.CompilerServices; //For internal calls
using System;
public enum CellType
{
    Empty = 0,
    Road,
    Structure,
    SpecialStructure,
    None
}

public class Grid
{
    private CellType[,] _grid;
    private int _width;
    //public int Width { get { return _width; } }
    private int _height;
    private int _xOffset;
    private int _yOffset;
    //public int Height { get { return _height; } }

    private List<Point> _roadList = new List<Point>();
    private List<Point> _houseStructure = new List<Point>();
    private List<Point> _specialStructure = new List<Point>();

    public Grid(int width, int height)
    {
        _width = width;
        _height = height;
        _xOffset = 0;
        _yOffset = 0;
        _grid = new CellType[width, height];
        CreateGrid_Engine(width, height);
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void CreateGrid_Engine(int width, int height);

    //Size of grid is expanded by 2 (Default) times
    public void Expand(int xMul = 2, int yMul = 2)
    {
        Resize(_width * xMul, _height * yMul);
    }

    private void Resize(int newWidth, int newHeight)
    {
        _xOffset = (newWidth - _width) / 2;
        _yOffset = (newHeight - _height) / 2;
        CellType[,] temGrid = new CellType[newWidth, newHeight];

        for (int y = 0; y < _height; y++)
        {
            for (int x = 0; x < _width; x++)
            {
                temGrid[x, y] = _grid[x, y];
            }
        }

        _grid = temGrid;
        _width = newWidth;
        _height = newHeight;
        ResizeGrid_Engine(newWidth, newHeight);
    }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void ResizeGrid_Engine(int newWidth, int newHeight);

    public Vector2Int GetStartPoint()
    {
        return new Vector2Int(-_xOffset, -_yOffset);
    }

    public void PrintGridOut()
    {
        /*for (int y = 0; y < _height; y++)
            
        {
            for (int x = 0; x < _width; x++)
            {
                if ((int)_grid[x, y] == 0) Debug.Log("  ");
                else Debug.Log((int)_grid[x, y] + " ");
            }
            Debug.Log("\n");
        }

        PrintGridOut_Engine();*/
        Console.WriteLine("-----------------------------------------");
        Console.WriteLine(-_xOffset + " " + -_yOffset);
        Console.WriteLine(_width + " " + _height);
        Console.WriteLine("-----------------------------------------");

    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void PrintGridOut_Engine();

    public Vector2Int GetGridSize()
    {
        return new Vector2Int(_width, _height);
    }

    // Adding index operator to our Grid class so that we can use grid[][] to access specific cell from our grid. 
    public CellType this[int i, int j]
    {
        get
        {
            
            //Console.WriteLine(GetCellType_Engine(i, j) + " and " + (int)_grid[i, j]);
            //return (CellType)GetCellType_Engine(i, j);
            return _grid[i + _xOffset, j + _yOffset];
        }
        set
        {
            if (value == CellType.Road)
            {
                _roadList.Add(new Point(i, j));
            }
            /*else
            {
                _roadList.Remove(new Point(i, j));
            }*/
            if (value == CellType.Structure)
            {
                _houseStructure.Add(new Point(i, j));
            }
            /*else
            {
                _houseStructure.Remove(new Point(i, j));
            }*/
            if (value == CellType.SpecialStructure)
            {
                _specialStructure.Add(new Point(i, j));
            }
            /*else
            {
                _specialStructure.Remove(new Point(i, j));
            }*/
            
            _grid[i + _xOffset, j + _yOffset] = value;
            //SetCellType_Engine(i, j, (int)value);
        }
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern int GetCellType_Engine(int x, int y);
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void SetCellType_Engine(int x, int y, int cellType);

    public static bool IsCellWakable(CellType cellType, bool aiAgent = false)
    {
        if (aiAgent)
        {
            return cellType == CellType.Road;
        }
        return cellType == CellType.Empty || cellType == CellType.Road;
    }

    public Point GetRandomRoadPoint()
    {
        //GetRandomRoadPoint_Engine(out Point point);
        /*return point;*/

        int count = _roadList.Count - 1;
        if (count < 0) return null;

        int n = Random.Range(0, count);
        return _roadList[n];
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool GetRandomRoadPoint_Engine(out Point point);

    public Point GetRandomSpecialStructurePoint()
    {
        //GetRandomSpecialStructurePoint_Engine(out Point point);
        /*return point;*/

        int count = _specialStructure.Count - 1;
        if (count < 0) return null;
 
        int n = Random.Range(0, count);
        return _specialStructure[n];
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern bool GetRandomSpecialStructurePoint_Engine(out Point point);

    public List<Point> GetAdjacentCells(Point cell, bool isAgent)
    {
        return GetWakableAdjacentCells((int)cell.X, (int)cell.Y, isAgent);
    }

    public float GetCostOfEnteringCell(Point cell)
    {
        return 1;
    }

    public List<Point> GetAllAdjacentCells(int x, int y)
    {
        List<Point> adjacentCells = new List<Point>();
        if (x > -_xOffset)
        {
            adjacentCells.Add(new Point(x - 1, y));
        }
        if (x < _width - 1)
        {
            adjacentCells.Add(new Point(x + 1, y));
        }
        if (y > -_yOffset)
        {
            adjacentCells.Add(new Point(x, y - 1));
        }
        if (y < _height - 1)
        {
            adjacentCells.Add(new Point(x, y + 1));
        }
        //Console.WriteLine("GetAllAdjacentCells: ----------------------------");
        //---------------------------------------------------------------------------------WORKING----------------------------------------------------------------------------------
       /* Vector2Int[] pos = new Vector2Int[4];
        //GetAllAdjacentCells_Engine(pos, out int count, x, y);
        List<Point> adjacentCellsTest = new List<Point>();
        for (int i = 0; i < count; i++)
        {
            adjacentCellsTest.Add(new Point(pos[i]));
            //Console.WriteLine(adjacentCellsTest[i]);
        }*/

        /*Console.WriteLine("Old GetAllAdjacentCells ");

        for (int i = 0; i < count; i++)
        {
            Console.WriteLine(adjacentCells[i]);
        }
        Console.WriteLine("----------------------------");*/
        return adjacentCells;
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void GetAllAdjacentCells_Engine(Vector2Int[] pos, out int count, int x, int y);

    public List<Point> GetWakableAdjacentCells(int x, int y, bool isAgent)
    {
        List<Point> adjacentCells = GetAllAdjacentCells(x, y);
        Console.WriteLine("Start part: " + x + " " + y);
        for (int i = adjacentCells.Count - 1; i >= 0; i--)
        {
            //if (IsCellWakable(GetCellType(adjacentCells[i].X, adjacentCells[i].Y), isAgent) == false)
            Console.WriteLine("Error part: " + _width + " " + _height);
            Console.WriteLine("Error part: " + (adjacentCells[i].X + _xOffset) + " " + (adjacentCells[i].Y + _yOffset));
            if (IsCellWakable(_grid[adjacentCells[i].X + _xOffset, adjacentCells[i].Y + _yOffset], isAgent) == false)
            {
                adjacentCells.RemoveAt(i);
            }
        }
        //Console.WriteLine("walkableadjacentCells: ----------------------------");
        //---------------------------------------------------------------------------------WORKING----------------------------------------------------------------------------------
        /*Vector2Int[] pos = new Vector2Int[4];
        GetWalkableAdjacentCells_Engine(pos, out int count, x, y, isAgent);
        List<Point> adjacentCellsTest = new List<Point>();
        for (int i = 0; i < count; i++)
        {
            adjacentCellsTest.Add(new Point(pos[i]));
            //Console.WriteLine(adjacentCellsTest[i]);
        }*/

        /*Console.WriteLine("Old walkableadjacentCells ");

        for (int i = 0; i < count; i++)
        {
            Console.WriteLine(adjacentCells[i]);
        }
        Console.WriteLine("----------------------------");*/
        return adjacentCells;
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void GetWalkableAdjacentCells_Engine(Vector2Int[] pos, out int count, int x, int y, bool isAgent);

    public List<Point> GetAdjacentCellsOfType(int x, int y, CellType type)
    {
        List<Point> adjacentCells = GetAllAdjacentCells(x, y);
        for (int i = adjacentCells.Count - 1; i >= 0; i--)
        {
            if (_grid[adjacentCells[i].X + _xOffset, adjacentCells[i].Y + _yOffset] != type)
            {
                adjacentCells.RemoveAt(i);
            }
        }
        //Console.WriteLine("adjacentCells: ----------------------------");
        //---------------------------------------------------------------------------------WORKING----------------------------------------------------------------------------------
        /*Vector2Int[] pos = new Vector2Int[4];
        GetAdjacentCellsOfType_Engine(pos, out int count, x, y, (int)type);
        List<Point> adjacentCellsTest = new List<Point>();
        for (int i = 0; i < count; i++)
        {
            adjacentCellsTest.Add(new Point(pos[i]));
            //Console.WriteLine(adjacentCellsTest[i]);
        }*/

        /*Console.WriteLine("Old adjacentCells ");

        for (int i = 0; i < count; i++)
        {
            Console.WriteLine(adjacentCells[i]);
        }
        Console.WriteLine("----------------------------");*/
        return adjacentCells;
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void GetAdjacentCellsOfType_Engine(Vector2Int[] pos, out int count, int x, int y, int type);


    /// <summary>
    /// Returns array [Left neighbour, Top neighbour, Right neighbour, Down neighbour]
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <returns></returns>
    public CellType[] GetAllAdjacentCellTypes(int x, int y)
    {
        CellType[] neighbours = { CellType.None, CellType.None, CellType.None, CellType.None };
        if (x > 0)
        {
            neighbours[0] = _grid[x - 1 + _xOffset, y + _yOffset];
        }
        if (x < _width - 1)
        {

            neighbours[2] = _grid[x + 1 + _xOffset, y + _yOffset];
        }
        if (y > 0)
        {
            neighbours[3] = _grid[x + _xOffset, y - 1 + _yOffset];
        }
        if (y < _height - 1)
        {
            neighbours[1] = _grid[x + _xOffset, y + 1 + _yOffset];
        }

        //Console.WriteLine("Neighbour: ----------------------------");
        //---------------------------------------------------------------------------------WORKING----------------------------------------------------------------------------------
        /*int[] pos = new int[4];
        GetAllAdjacentCellTypes_Engine(pos, x, y);
        CellType[] neighboursTest = { CellType.None, CellType.None, CellType.None, CellType.None };
        for (int i = 0; i < 4; i++)
        {
            neighboursTest[i] = (CellType)(pos[i]);
            //Console.WriteLine((int)neighboursTest[i] + " " + pos[i]);
        }*/

        /*Console.WriteLine("Old Neighbour ");

        for (int i = 0; i < 4; i++)
        {
            Console.WriteLine((int)neighbours[i]);
        }
        Console.WriteLine("----------------------------");*/
        return neighbours;
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void GetAllAdjacentCellTypes_Engine(int[] pos, int x, int y);

    public List<Point> GetAllHouses()
    {
        return _houseStructure;
    }

    public List<Point> GetAllSpecialStructure()
    {
        return _specialStructure;
    }

    public Point GetRandomHouseStructurePoint()
    {
        if (_houseStructure.Count == 0)
        {
            return null;
        }
        return _houseStructure[Random.Range(0, _houseStructure.Count)];
    }
}