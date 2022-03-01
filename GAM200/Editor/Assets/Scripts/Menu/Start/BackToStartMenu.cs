using System;
public class BackToStartMenu : MonoBehaviour
{
    UI backButtonUI;

    public override void Start()
    {
        backButtonUI = GetComponent<UI>();
        backButtonUI.color = new Color(0f, 0f, 0f);
    }

    public override void OnMouseEnter()
    {
        if (backButtonUI == null) Debug.Log("This is actually null");
        backButtonUI.color = new Color(1f, 1f, 1f);
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
        if (backButtonUI == null) Debug.Log("This is actually null");
        backButtonUI.color = new Color(0f, 0f, 0f); 
    }
}