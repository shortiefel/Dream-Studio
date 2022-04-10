using System;
public class IntroScene : MonoBehaviour
{
    Texture logos;
    Transform logosT;
    private int counter;
    private bool fading;
    private float fadespeed;
    Vector2 vAdobe,vOpenGL,vMono,vFmod,vDreamStudio,test;
    public override void Start()
    {
        logos = GameObject.Find("Logos").GetComponent<Texture>();
        logosT = GameObject.Find("Logos").GetComponent<Transform>();
        Console.WriteLine("Enter Intro Start");
        test.x = 0f;
        test.y = 0f;
        logos.alpha = 1.0f;
        fadespeed = 0.002f;
        fading = false;
        counter = 0;
        vAdobe.x = 5.0f;
        vAdobe.y = 5.0f;
        vOpenGL.x = 4.807453632354736f;
        vOpenGL.y = 2.0f;
        vMono.x = 4.5f;
        vMono.y = 3.0f;
        vFmod.x = 3.7035884857177736f;
        vFmod.y = 2.0f;
        vDreamStudio.x = 3.0f;
        vDreamStudio.y = 3.0f;
    }
    public override void Update()
    {
        if (fading == false)
        {
            logos.alpha -= fadespeed;
            if (counter == 5 && logos.alpha <= 0.0f)
            {
                transform.scale = test;
                SceneManager.LoadScene("MainMenu");
            }
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
                transform.scale = vAdobe;
            }
            if(counter == 1)
            {
                logos.ChangeTexture("Logo//FMod");
                transform.scale = vFmod;
            }
            if(counter == 2)
            {
                logos.ChangeTexture("Logo//Mono");
                transform.scale = vMono;
            }
            if (counter == 3)
            {
                logos.ChangeTexture("Logo//OpenGL");
                transform.scale = vOpenGL;
            }
            if (counter == 4)
            {
                logos.ChangeTexture("Logo//DreamStudio_Logo");
                transform.scale = vDreamStudio;
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