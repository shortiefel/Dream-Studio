using System;

public class CreditsButton : MonoBehaviour
{
    public override void Start()
    {
        Console.WriteLine("going into credit scene");
    }

    public override void Update()
    {

    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Credit selected");
            SceneManager.LoadScene("Credits");
        }
    }
}