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

public enum AudioGroup
{
    Master = 0,
    SFX,
    Music
}

public class AudioSource : IComponent
{
    //public uint entityId { get; set; }
    public AudioSource() { }
    public AudioSource(uint entity_id) { entityId = entity_id; }

    

    enum AudioType
    {
        Play = 0,
        Pause,
        Unpause
    }

    public void Play()
    {
        //SetAudioSource_Play_Engine(entityId);
        SetSound_State_Engine(entityId, (int)AudioType.Play);
    }
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void SetAudioSource_Play_Engine(uint entityID);

    public void Pause()
    {
        //SetAudioSource_Pause_Engine(entityId);
        SetSound_State_Engine(entityId, (int)AudioType.Pause);
    }
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void SetAudioSource_Pause_Engine(uint entityID);

    public void UnPause()
    {
        //SetAudioSource_UnPause_Engine(entityId);
        SetSound_State_Engine(entityId, (int)AudioType.Unpause);
    }
    //[MethodImpl(MethodImplOptions.InternalCall)]
    //internal static extern void SetAudioSource_UnPause_Engine(uint entityID);

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetSound_State_Engine(uint entityID, int audioType);

    public float volume
    {
        get
        {
            GetSound_Volume_Engine(entityId, out float vol);
            return vol;
        }
        set { SetSound_Volume_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetSound_Volume_Engine(uint entityID, out float _vol);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetSound_Volume_Engine(uint entityID, ref float _vol);

    public bool mute
    {
        get
        {
            GetSound_Mute_Engine(entityId, out bool _mute);
            return _mute;
        }
        set { SetSound_Mute_Engine(entityId, ref value); }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetSound_Mute_Engine(uint entityID, out bool _mute);
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetSound_Mute_Engine(uint entityID, ref bool _mute);

    static public void SetGroup_Mute(AudioGroup ag, bool state)
    {
        SetSoundGroup_Mute_Engine((int)ag, state);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetSoundGroup_Mute_Engine(int audioGroup, bool _state);
    static public bool GetGroup_Mute(AudioGroup ag)
    {
        return GetSoundGroup_Mute_Engine((int)ag);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool GetSoundGroup_Mute_Engine(int audioGroup);

    static public void SetGroup_Volume(AudioGroup ag, float vol)
    {
        SetSoundGroup_Volume_Engine((int)ag, vol);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void SetSoundGroup_Volume_Engine(int audioGroup, float vol);

    static public float GetGroup_Volume(AudioGroup ag)
    {
        return GetSoundGroup_Volume_Engine((int)ag);
    }


    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern float GetSoundGroup_Volume_Engine(int audioGroup);

}
