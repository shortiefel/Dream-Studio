using System;
public class BackToStartMenu : MonoBehaviour
{
    UI backButtonUI;

    public override void Start()
    {
        backButtonUI = GetComponent<UI>();
    }

    public override void OnMouseEnter()
    {
        backButtonUI.color = new Color(0f, 0f, 0f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            SceneManager.LoadScene("MainMenu");
        }
    }

    public override void OnMouseExit()
    {
        backButtonUI.color = new Color(1f, 1f, 1f);
    }
}