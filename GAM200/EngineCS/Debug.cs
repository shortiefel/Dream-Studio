/* Start Header**********************************************************************************/
/*
@file    Debug.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Debug


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Debug
{
    public static void Log<T>(T message)
    {
        ConsoleWrite_Engine(message.ToString());
    }
    public static void Log(string message)
    {
        ConsoleWrite_Engine(message);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void ConsoleWrite_Engine(string message);
}

