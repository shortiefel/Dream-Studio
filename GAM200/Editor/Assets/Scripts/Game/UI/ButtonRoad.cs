using System;
public class ButtonRoad : MonoBehaviour
{
    UI buttonUI;
    bool result;
    public override void Start()
    {
        buttonUI = GetComponent<UI>();

        if (transform.entityId == GameObject.Find("DrawRoad").GetComponent<Transform>().entityId)
        {
            result = true;

        }
        else
        {
            result = false;
        }

    }

    public override void OnMouseEnter()
    {
        buttonUI.color = new Color(1f, 0f, 0f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            //SceneManager.LoadScene("MainMenu");
            if (result)
                Debug.Log("Change to draw");
            else
                Debug.Log("Change to delete");
        }
    }

    public override void OnMouseExit()
    {
        buttonUI.color = new Color(1f, 1f, 1f);
    }
}