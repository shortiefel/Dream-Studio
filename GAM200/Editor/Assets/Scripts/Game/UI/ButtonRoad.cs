using System;
public class ButtonRoad : MonoBehaviour
{
    UI buttonUI;
    bool result;
    bool drawRoadMode;
    bool deleteRoadMode;
    Transform drawRoadWhite;
    Transform drawRoad;

    Transform removeRoad;
    Transform removeRoadWhite;

    GameManager gameManager;
    InputManager inputManager;

    GameState gameState;

    public override void Start()
    {
        buttonUI = GetComponent<UI>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        drawRoadWhite = GameObject.Find("DrawRoadWhite").GetComponent<Transform>();
        drawRoad = GameObject.Find("DrawRoad").GetComponent<Transform>();
        removeRoad = GameObject.Find("RemoveRoad").GetComponent<Transform>();
        removeRoadWhite = GameObject.Find("RemoveRoadWhite").GetComponent<Transform>();

        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);

        drawRoadMode = false;
        deleteRoadMode = false;

        if (transform.entityId == GameObject.Find("DrawRoad").GetComponent<Transform>().entityId || 
            transform.entityId == GameObject.Find("DrawRoadWhite").GetComponent<Transform>().entityId)
        {
            result = true;

        }
        else if (transform.entityId == GameObject.Find("RemoveRoad").GetComponent<Transform>().entityId ||
            transform.entityId == GameObject.Find("RemoveRoadWhite").GetComponent<Transform>().entityId)
        {
            result = false;
        }

    }

    //public override void OnMouseEnter()
    //{
    //    buttonUI.color = new Color(1f, 0f, 0f);
    //}

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            //SceneManager.LoadScene("MainMenu");
            if (result)
            {
                if (drawRoadMode == false)
                {
                    Disable<Transform>(drawRoad);
                    Enable<Transform>(drawRoadWhite);
                    drawRoadMode = true;
                    Disable<Transform>(removeRoadWhite);
                    Enable<Transform>(removeRoad);
                    gameManager.RoadPlacementHandler();
                    SwitchMode();
                }
                else if (drawRoadMode == true)
                {
                    Enable<Transform>(drawRoad);
                    Disable<Transform>(drawRoadWhite);
                    drawRoadMode = false;
                    Disable<Transform>(removeRoadWhite);
                    Enable<Transform>(removeRoad);
                    gameManager.ClearInputActions();
                    SwitchMode();
                }

            }

            else
            {
                if (deleteRoadMode == false)
                {
                    Disable<Transform>(removeRoad);
                    Enable<Transform>(removeRoadWhite);
                    gameManager.RemoveRoadHandler();
                    deleteRoadMode = true;
                    Enable<Transform>(drawRoad);
                    Disable<Transform>(drawRoadWhite);
                    SwitchMode();
                }
                else if (deleteRoadMode == true)
                {
                    Enable<Transform>(drawRoad);
                    Disable<Transform>(drawRoadWhite);
                    deleteRoadMode = false;
                    Disable<Transform>(removeRoadWhite);
                    Enable<Transform>(removeRoad);
                    gameManager.ClearInputActions();
                    SwitchMode();
                }

            }

        }
    }

    //public override void OnMouseExit()
    //{
    //    buttonUI.color = new Color(1f, 1f, 1f);
    //}

    public void SwitchMode()
    {

        if (gameState.GetDrawMode())
        {
            SceneManager.SetDrawMode(false);

            //drawModeBool = false;
            gameState.SetDrawMode(false);
        }
        else
        {
            SceneManager.SetDrawMode(true);

            //drawModeBool = true;
            gameState.SetDrawMode(true);
        }
    }
}