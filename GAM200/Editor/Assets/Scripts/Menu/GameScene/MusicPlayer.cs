using System;

public class MusicPlayer : MonoBehaviour
{
    AudioSource t1;
    AudioSource t2;

    public override void Start()
    {
       GetComponent<AudioSource>().Play();
        t1 = GetComponent<AudioSource>();
        t2 = GameObject.Find("Camera").GetComponent<AudioSource>();
    

        Debug.Log("oshfddosfhoidsfjhoi");
    }

    public override void Update()
    { 
      if (Input.GetKeyDown(KeyCode.A))
        {
            AudioSource.SetGroup_Mute(AudioGroup.Music, true);
        }
        if (Input.GetKeyDown(KeyCode.S))
        {
            AudioSource.SetGroup_Mute(AudioGroup.Music, false);
        }
        if (Input.GetKeyDown(KeyCode.D))
        {
            t2.mute = false;
        }

        
    }

}


