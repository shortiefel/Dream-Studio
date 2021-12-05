using System;
public class ButtonRoad : MonoBehaviour
{
    UI buttonUI;
    bool result;

    GameManager gameManager;

    public override void Start()
    {
        buttonUI = GetComponent<UI>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();

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
                gameManager.RoadPlacementHandler();
            else
                gameManager.RemoveRoadHandler();
        }
    }

    public override void OnMouseExit()
    {
        buttonUI.color = new Color(1f, 1f, 1f);
    }
}