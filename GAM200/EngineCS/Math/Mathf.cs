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

public class Mathf
{
    public const float Infinity = float.MaxValue;
    public const float Rad2Deg = 360 / (PI * 2);
    public const float PI = 3.141592653589793238462643383279502884197169399375105820974944f;

    public static float Atan2(float val1, float val2)
    {
        Atan2_Engine(out float outFloat, val1, val2);
        return outFloat;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void Atan2_Engine(out float outFloat, float val1, float val2);
}


