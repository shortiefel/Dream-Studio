/* Start Header**********************************************************************************/
/*
@file    UI.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    03/12/2021
\brief
This file has the function definition for UITexture


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class UI: IComponent
{
    //public uint entityId { get; set; }
    public UI() { }
    public UI(uint entity_id) { entityId = entity_id; }

    public Color color
    {
        // get
        // {
        //     GetFont_Text_Engine(entityId, out string text);
        //     return text;
        // }
        set { SetUI_Color_Engine(entityId, value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetUI_Color_Engine(uint entityID, Color col);

    public void ChangeTexture(string name)
    {
        ChangeTexture_UI_Engine(entityId, name);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void ChangeTexture_UI_Engine(uint entityID, string name);

}