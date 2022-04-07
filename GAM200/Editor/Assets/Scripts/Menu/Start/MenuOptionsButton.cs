using System;

public class MenuOptionsButton : MonoBehaviour
{

    UI MenuOptionsBtn;

    public override void Start()
    {
        MenuOptionsBtn = GetComponent<UI>();
        MenuOptionsBtn.color = new Color(1f, 1f, 1f);

    }

    public override void OnMouseEnter()
    {
        if (MenuOptionsBtn == null) Debug.Log("This is actually null");
        MenuOptionsBtn.color = new Color(1f, 1f, 1f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
           
            SceneManager.LoadScene("Options");
        }
    }

    public override void OnMouseExit()
    {
        if (MenuOptionsBtn == null) Debug.Log("This is actually null");
        MenuOptionsBtn.color = new Color(1f, 1f, 1f);
    }
}