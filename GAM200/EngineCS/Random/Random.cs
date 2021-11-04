/* Start Header**********************************************************************************/
/*
@file    Random.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Random


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Random
{
    public static int Range(int num1, int num2)
    {
        Random_Range_Engine(num1, num2, out int answer);
        return answer;
    }
    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    internal static extern void Random_Range_Engine(int num1, int num2, out int answer);
}
