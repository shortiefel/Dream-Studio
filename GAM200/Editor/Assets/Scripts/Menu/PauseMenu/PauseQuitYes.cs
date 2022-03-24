﻿
public class PauseQuitYes : MonoBehaviour
{
    PauseMenu pauseMenu;
    //Text text;
    UI texture;
    public override void Start()
    {
        pauseMenu = GameObject.Find("PauseIcon").GetComponent<PauseMenu>();

       // text = GetComponent<Text>();
        texture = GameObject.Find("QuitYesBtn").GetComponent<UI>();
        texture.color = new Color(1f, 1f, 1f);
    }

    public override void OnMouseEnter()
    {
        //text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            pauseMenu.QuitYesAction();
        }
    }

    public override void OnMouseExit()
    {
        //text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(1f, 1f, 1f);
    }
}