/* Start Header**********************************************************************************/
/*
@file    Intput.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Intput


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Input
{
    public static bool GetKey(KeyCode keyCode)
    {
        return GetKey_Engine(keyCode);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool GetKey_Engine(KeyCode key);

    public static bool GetKeyDown(KeyCode keyCode)
    {
        return GetKeyDown_Engine(keyCode);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool GetKeyDown_Engine(KeyCode key);


    public static bool GetMouseButton(MouseCode button) { return GetMouse_Engine(button); }
    public static bool GetMouseButton(int button) { return GetMouse_Engine((MouseCode)button); }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool GetMouse_Engine(MouseCode button);


    public static bool GetMouseButtonDown(MouseCode button) { return GetMouseDown_Engine(button); }
    public static bool GetMouseButtonDown(int button) { return GetMouseDown_Engine((MouseCode)button); }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool GetMouseDown_Engine(MouseCode button);

    public static bool GetMouseButtonUp(MouseCode button) {  return GetMouseUp_Engine(button); }
    public static bool GetMouseButtonUp(int button) { return GetMouseUp_Engine((MouseCode)button); }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool GetMouseUp_Engine(MouseCode button);


    public static Vector2 GetMouseScroll()
    {
        GetMouseScroll_Engine(out Vector2 position);
        return position;
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetMouseScroll_Engine(out Vector2 pos);
    

    public static Vector3 GetMousePosition()
    {
        GetMousePosition_Engine(out Vector2 position);
        return new Vector3 (position.x, position.y, 1f);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetMousePosition_Engine(out Vector2 pos);
}
