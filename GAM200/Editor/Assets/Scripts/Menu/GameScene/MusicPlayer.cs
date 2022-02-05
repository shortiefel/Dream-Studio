using System;

public class MusicPlayer : MonoBehaviour
{
    AudioSource t1;
    AudioSource t2;

    public override void Start()
    {
      GetComponent<AudioSource>().Play();

    }

    

}


