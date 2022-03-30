/* Start Header**********************************************************************************/
/*
@file    Text.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    01/12/2021
\brief
This file has the function definition for Text


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Text : IComponent
{
    //public uint entityId { get; set; }
    public Text() { }
    public Text(uint entity_id) { entityId = entity_id; }

    public string text
    {
       // get
       // {
       //     GetFont_Text_Engine(entityId, out string text);
       //     return text;
       // }
        set { SetText_Text_Engine(entityId, value); }
    }
   //[MethodImpl(MethodImplOptions.InternalCall)]
   //internal static extern void GetFont_Text_Engine(uint entityID, out string text);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetText_Text_Engine(uint entityID, string text);

    public Color color
    {
        // get
        // {
        //     GetFont_Text_Engine(entityId, out string text);
        //     return text;
        // }
        set { SetText_Color_Engine(entityId, value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetText_Color_Engine(uint entityID, Color col);

    public float alpha
    {
        get
        {
            GetText_Alpha_Engine(entityId, out float alpha);
            return alpha;
        }
        set { SetText_Alpha_Engine(entityId, value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetText_Alpha_Engine(uint entityID, out float alpha);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetText_Alpha_Engine(uint entityID, float alpha);



    public Vector2 position
    {
        get
        {
            GetText_Position_Engine(entityId, out Vector2 result);
            return result;
        }
        set { SetText_Position_Engine(entityId, ref value); }
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetText_Position_Engine(uint entityID, out Vector2 outVec2);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetText_Position_Engine(uint entityID, ref Vector2 inVec2);

    public Vector2 scale
    {
        get
        {
            GetText_Scale_Engine(entityId, out Vector2 result);
            return result;
        }
        set { SetText_Scale_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetText_Scale_Engine(uint entityID, out Vector2 outVec2);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetText_Scale_Engine(uint entityID, ref Vector2 inVec2);

}