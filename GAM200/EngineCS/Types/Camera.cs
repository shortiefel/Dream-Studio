/* Start Header**********************************************************************************/
/*
@file    Camera.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/08/2021
\brief
This file has the function definition for Camera


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class Camera : IComponent
{
    public uint entityId { get; set; }
    public Camera() { }
    public Camera(uint entity_id) { entityId = entity_id; }
    public float height
    {
        get
        {
            GetCameraHeight_Engine(entityId, out float result);
            return result;
        }
        set { SetCameraHeight_Engine(entityId, value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetCameraHeight_Engine(uint entityID, out float pos);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetCameraHeight_Engine(uint entityID, float pos);


    public Vector3 ScreenToWorldPoint(Vector3 position)
    {
        ScreenToWorldPoint_Engine(entityId, out Vector3 outPosition, position);
        return outPosition;
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void ScreenToWorldPoint_Engine(uint entityID, out Vector3 outPosition, Vector3 inPosition);
}