/* Start Header**********************************************************************************/
/*
@file    Application.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    07/11/2021
\brief
This file has the function definition for Application


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Application
{
    public static void Quit()
    {
        Quit_Engine();
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void Quit_Engine();

    public static void SetPause(bool state)
    {
        SetPause_Engine(state);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetPause_Engine(bool state);
}

