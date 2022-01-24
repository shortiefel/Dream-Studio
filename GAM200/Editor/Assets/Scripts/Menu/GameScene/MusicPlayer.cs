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
    }

    public override void Update()
    { 
      if (Input.GetKeyDown(KeyCode.A))
        {
            t1.mute = true;
        }
        if (Input.GetKeyDown(KeyCode.S))
        {
            t2.mute = true;
        }
        if (Input.GetKeyDown(KeyCode.D))
        {
            t2.mute = false;
        }
    }

}


