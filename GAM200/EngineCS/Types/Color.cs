/* Start Header**********************************************************************************/
/*
@file    Color.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    03/12/2021
\brief
This file has the function definition for Color


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


public struct Color
{
    public Color(float _r, float _g, float _b, float _a = 1f) { r = _r; g = _g; b = _b; a = _a; }

    public float r, g, b, a;

}