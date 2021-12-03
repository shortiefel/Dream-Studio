﻿
public class QuitYes : MonoBehaviour
{
    PauseMenu pauseMenu;
    Text text;
    public override void Start()
    {
        pauseMenu = GameObject.Find("PauseIcon").GetComponent<PauseMenu>();

        text = GetComponent<Text>();
    }

    public override void OnMouseEnter()
    {
        text.color = new Color(0f, 0f, 0f);
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
        text.color = new Color(1f, 1f, 1f);
    }
}