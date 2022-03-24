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
    //public uint entityId { get; set; }
    public Texture() { }
    public Texture(uint entity_id) { entityId = entity_id; }

    public void ChangeTexture(string name)
    {
        ChangeTexture_Engine(entityId, name);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void ChangeTexture_Engine(uint entityID, string name);

    public Color color
    {
        // get
        // {
        //     GetTexture_Color_Engine(entityId, out string text);
        //     return text;
        // }
        set { SetTexture_Color_Engine(entityId, value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTexture_Color_Engine(uint entityID, Color col);

    public float alpha
    {
        get
        {
            GetTexture_Alpha_Engine(entityId, out float alpha);
            return alpha;
        }
        set { SetTexture_Alpha_Engine(entityId, value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetTexture_Alpha_Engine(uint entityID, out float alpha);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetTexture_Alpha_Engine(uint entityID, float alpha);

    public string RetrieveTexture()
    {
        RetrieveTexture_Engine(entityId, out string name);
        return name;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void RetrieveTexture_Engine(uint entityID, out string name);

}