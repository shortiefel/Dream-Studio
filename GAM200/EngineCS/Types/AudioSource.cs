/* Start Header**********************************************************************************/
/*
@file    AudioSource.cs
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    03/12/2021
\brief
This file has the function definition for AudioSource


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

using System.Runtime.CompilerServices; //For internal calls

public class AudioSource : IComponent
{
    public uint entityId { get; set; }
    public AudioSource() { }
    public AudioSource(uint entity_id) { entityId = entity_id; }


    public void Play()
    {
        //SetAudioSource_Play_Engine(entityId);
    }
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void SetAudioSource_Play_Engine(uint entityID);

    public void Pause()
    {
        //SetAudioSource_Pause_Engine(entityId);
    }
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void SetAudioSource_Pause_Engine(uint entityID);

    public void UnPause()
    {
        //SetAudioSource_UnPause_Engine(entityId);
    }
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void SetAudioSource_UnPause_Engine(uint entityID);

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetAudioSource_Engine(uint entityID);
}