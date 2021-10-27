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



    public static bool GetMouseDown(MouseCode button)
    {
        return GetMouseDown_Engine(button);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool GetMouseDown_Engine(MouseCode button);



    public static Vec2 GetMousePosition()
    {
        GetMousePosition_Engine(out Vec2 position);
        return position;
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool GetMousePosition_Engine(out Vec2 pos);
}
