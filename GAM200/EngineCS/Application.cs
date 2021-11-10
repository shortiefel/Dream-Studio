﻿/* Start Header**********************************************************************************/
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
        Debug.Log("Quit does nothing yet");
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void Quit_Engine();
}
