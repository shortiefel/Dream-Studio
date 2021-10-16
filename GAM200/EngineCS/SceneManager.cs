﻿/* Start Header**********************************************************************************/
/*
@file    SceneManager.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for SceneManager


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class SceneManager
{
    public static void LoadScene(string sceneName)
    {
        LoadScene_Engine(sceneName);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void LoadScene_Engine(string sceneName);
}
