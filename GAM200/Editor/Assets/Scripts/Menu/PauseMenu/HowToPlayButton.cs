using System;
public class HowToPlayButton : MonoBehaviour
{
    //GameObject howToPlayScreen;
    //PauseMenu pauseMenu;
    //public override void Start()
    //{
    //    pauseMenu = GameObject.Find("PauseIcon").GetComponent<PauseMenu>();
    //}
    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("howtoplay selected");
        }
    }
}