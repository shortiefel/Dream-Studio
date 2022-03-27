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
        set { SetFont_Text_Engine(entityId, value); }
    }
   //[MethodImpl(MethodImplOptions.InternalCall)]
   //internal static extern void GetFont_Text_Engine(uint entityID, out string text);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetFont_Text_Engine(uint entityID, string text);

    public Color color
    {
        // get
        // {
        //     GetFont_Text_Engine(entityId, out string text);
        //     return text;
        // }
        set { SetFont_Color_Engine(entityId, value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetFont_Color_Engine(uint entityID, Color col);

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

}