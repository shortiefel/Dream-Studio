/* Start Header**********************************************************************************/
/*
@file    Mathf.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Mathf


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls
using System;
public class Mathf
{
    public const float Infinity = float.MaxValue;
    public const float Rad2Deg = 360 / (PI * 2);
    public const float PI = 3.141592653589793238462643383279502884197169399375105820974944f;

    public static float Atan2(float yVal, float xVal)
    {
        Atan2_Engine(out float outFloat, xVal, yVal);
        return outFloat;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void Atan2_Engine(out float outFloat, float xVal, float yVal);


    public static bool Approximately(float num1, float num2)
    {
        Approximately_Engine(num1, num2, out bool result);
        return result;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void Approximately_Engine(float num1, float num2, out bool result);

    public static float Lerp(float num1, float num2, float t)
    {
        float result = num1;
        Lerp_Engine(out result, num2, t);
        return result;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void Lerp_Engine(out float num1, float num2, float t);

    //public static float Abs(float t)
    //{
    //    if (t < 0f) return -t;
    //    return t;
    //}

    public static float ShortestAngle(float target, float comparedTo)
    {
        float diff1 = System.Math.Abs(comparedTo - target);
        float diff2;
        float newTarget;
        if (target < comparedTo)
        {
            newTarget = target + 360;
            diff2 = System.Math.Abs(comparedTo - newTarget);
           
            if (diff1 < diff2) return target;
            else return newTarget;
        }

        newTarget = target - 360;
        diff2 = System.Math.Abs(comparedTo - newTarget);
       
        if (diff1 < diff2) return target;
        return newTarget;
    }
}


