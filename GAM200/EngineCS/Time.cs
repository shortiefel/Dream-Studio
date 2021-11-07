/* Start Header**********************************************************************************/
/*
@file    Time.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Time


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Time
{
    public static float deltaTime
    {
        get
        {
            GetDeltaTime_Engine(out float result);
            return result;
        }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetDeltaTime_Engine(out float outFloat);

    public static float timeScale
    {
        set
        {
            SetTimeScale_Engine(value);
        }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTimeScale_Engine(float timeScale);
}

public class WaitForSeconds
{
    public WaitForSeconds(float timer)
    {
        Debug.Log("Not done waitforsecond");
        WaitForSeconds_Engine(timer);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void WaitForSeconds_Engine(float timer);
}
