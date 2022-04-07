using System;

public class MusicPlayer : MonoBehaviour
{
 
    public override void Start()
    {
      GetComponent<AudioSource>().Play();
    }
}


