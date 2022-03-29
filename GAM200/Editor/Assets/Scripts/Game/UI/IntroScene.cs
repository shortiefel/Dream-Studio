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
        fadespeed = 0.002f;
        fading = false;
        counter = 0;
    }
    public override void OnMouseEnter()
    {
        
    }
    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Intro Skip");
            //Time.timeScale = 1;
            SceneManager.LoadScene("MainMenu");
        }
    }
    public override void OnMouseExit()
    {
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
                logos.ChangeTexture("DeleteRoad");
            }
            if(counter == 1)
            {
                logos.ChangeTexture("EndRoad");
            }
            counter++;
            fading = true;
        }        
    }
}