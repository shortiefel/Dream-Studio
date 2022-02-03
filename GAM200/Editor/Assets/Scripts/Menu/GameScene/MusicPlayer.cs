using System;

public class MusicPlayer : MonoBehaviour
{
    AudioSource t1;
    AudioSource t2;

    public override void Start()
    {
      GetComponent<AudioSource>().Play();


      // t1 = GetComponent<AudioSource>();
      // t2 = GameObject.Find("Camera").GetComponent<AudioSource>();
      //
      //
      // Debug.Log("oshfddosfhoidsfjhoi");
    }

    public override void Update()
    { 
      if (Input.GetKeyDown(KeyCode.A))
        {
            //AudioSource.SetGroup_Mute(AudioGroup.Music, true);
            AudioSource.SetGroup_Volume(AudioGroup.Music, 100f);
        }
        if (Input.GetKeyDown(KeyCode.S))
        {
            //AudioSource.SetGroup_Mute(AudioGroup.Music, false);
            AudioSource.SetGroup_Volume(AudioGroup.Music, 10f);
        }
        if (Input.GetKeyDown(KeyCode.D))
        {
            //t2.mute = false;
        }

        
    }

}


