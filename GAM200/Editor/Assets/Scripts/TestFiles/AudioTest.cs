using System;

public class AudioTest : MonoBehaviour
{
    AudioSource audioSrc;

    Texture texture;

    Text text;

    Animation animation;

    public override void Start()
    {
        //Make sure to have the component first
        audioSrc = GetComponent<AudioSource>();

        texture = GetComponent<Texture>();

        text = GetComponent<Text>();

        animation = GetComponent<Animation>();
    }

    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.N))
        {
            Console.WriteLine("Play");
            if (audioSrc != null)
                audioSrc.Play();
        }

        else if (Input.GetKeyDown(KeyCode.J))
        {
            Console.WriteLine("Pause");
            if (audioSrc != null)
                audioSrc.Pause();
        }
        else if (Input.GetKeyDown(KeyCode.K))
        {
            Console.WriteLine("Unpause");
            if (audioSrc != null)
                audioSrc.UnPause();
        }

        if (Input.GetKeyDown(KeyCode.O))
        {
            if (texture != null)
                texture.color = new Color(1f, 1f, 1f);
        }

        if (Input.GetKeyDown(KeyCode.P))
        {
            if (text != null)
                text.color = new Color(1f, 1f, 1f);
        }

        if (Input.GetKeyDown(KeyCode.Y))
        {
            if (animation != null)
                animation.Play("Run");
        }

        if (Input.GetKeyDown(KeyCode.U))
        {
            if (animation != null)
                animation.Play("more better");
        }


    }


}