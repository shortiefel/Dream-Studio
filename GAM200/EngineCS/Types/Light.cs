/* Start Header**********************************************************************************/
/*
@file    Light.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    24/03/2022
\brief
This file has the function definition for Light


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Light : IComponent
{
    public Light() { }
    public Light(uint entity_id) { entityId = entity_id; }

    
}
