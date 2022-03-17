using System;
public class GoToMenu : MonoBehaviour
{
  

    public override void Start()
    {
    }

    public override void Update()
    {
        if(Input.GetMouseButtonDown(MouseCode.Left))
        {
            SceneManager.LoadScene("MainMenu");
        }
    }

    //public override void OnMouseEnter()
    //{
    //    text.color = new Color(0f, 0f, 0f);
    //    texture.color = new Color(1f, 1f, 1f);
    //}

    //public override void OnMouseOver()
    //{
    //    if (Input.GetMouseButtonDown(MouseCode.Left))
    //    {
    //        Console.WriteLine("menu");
    //        SceneManager.LoadScene("MainMenu");
    //    }
    //}

    //public override void OnMouseExit()
    //{
    //    text.color = new Color(1f, 1f, 1f);
    //    texture.color = new Color(0f, 0f, 0f);
    //}
}
