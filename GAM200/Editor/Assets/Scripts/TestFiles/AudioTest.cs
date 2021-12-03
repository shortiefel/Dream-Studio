using System;

public class AudioTest : MonoBehaviour
{
    AudioSource audioSrc;

    Texture texture;

    Text text;

    public override void Start()
    {
        //Make sure to have the component first
        audioSrc = GetComponent<AudioSource>();

        texture = GetComponent<Texture>();

        text = GetComponent<Text>();
    }

    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.N))
        {
            Console.WriteLine("Play");
            audioSrc.Play();
        }

        else if (Input.GetKeyDown(KeyCode.J))
        {
            Console.WriteLine("Pause");
            audioSrc.Pause();
        }
        else if (Input.GetKeyDown(KeyCode.K))
        {
            Console.WriteLine("Unpause");
            audioSrc.UnPause();
        }

        if (Input.GetKeyDown(KeyCode.O))
        {
            texture.color = new Color(1f, 1f, 1f);
        }

        if (Input.GetKeyDown(KeyCode.P))
        {
            text.color = new Color(1f, 1f, 1f);
        }

        
    }


}