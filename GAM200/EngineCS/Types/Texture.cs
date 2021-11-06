/* Start Header**********************************************************************************/
/*
@file    Texture.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Texture


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Texture : IComponent
{
    public uint entityId { get; set; }
    public Texture() { }
    public Texture(uint entity_id) { entityId = entity_id; }

    public void ChangeTexture(string name)
    {
        ChangeTexture_Engine(entityId, name);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void ChangeTexture_Engine(uint entityID, string name);
}