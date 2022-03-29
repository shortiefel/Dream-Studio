using System;
public class IntroScene : MonoBehaviour
{
    Texture logos;
    private int counter;
    private bool fading;
    private float fadespeed;
    public override void Start()
    {
        logos = GameObject.Find("Logos").GetComponent<Texture>();
        Console.WriteLine("Enter Intro Start");
        logos.alpha = 1.0f;
        fadespeed = 0.003f;
        fading = false;
        counter = 0;
    }
    public override void Update()
    {
        if(fading == false)
        {
            logos.alpha -= fadespeed;
        }
        else
        {
            logos.alpha += fadespeed;
        }
        if(logos.alpha >= 1.0f)
        {
            fading = false;
        }
        Console.WriteLine("Logo Alpha = " + logos.alpha.ToString());
        if(logos.alpha <= 0.0f)
        {
            if(counter == 0)
            {
                logos.ChangeTexture("Logo//Adobe");
            }
            if(counter == 1)
            {
                logos.ChangeTexture("Logo//FMod");
            }
            if(counter == 2)
            {
                logos.ChangeTexture("Logo//Mono");
            }
            if (counter == 3)
            {
                logos.ChangeTexture("Logo//OpenGL");
            }
            if (counter == 4)
            {
                logos.ChangeTexture("Logo//Dream_Studio_Logo");
            }
            counter++;
            fading = true;
        }
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Intro Skip");
            SceneManager.LoadScene("MainMenu");
        }
    }
}