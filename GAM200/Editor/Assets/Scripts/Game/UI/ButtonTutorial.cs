using System;

public enum TutButtonType
{
    Display = 1,
    Draw,
    Remove
    
}

public class ButtonTutorial : MonoBehaviour
{
    Transform drawRoadWhite;
    Transform drawRoad;
    Transform roadCount;
    Vector2 drawPosition;
    Vector2 drawRoadCount;

    Transform removeRoad;
    Transform removeRoadWhite;
    Transform trafficCount;
    Vector2 removePosition;

    Transform displayArrow;
    Transform displayArrowWhite;

    GameManager gameManager;

    Transform moneyText;
    Transform counterText;

    GameState gameState;

    private Camera mainCamera;

    public bool opening;
    public bool closing;
    float timer;

    float closeXPosition;

    float speedMultiply;

    ButtonTutorial buttonTutSys;

    public override void Start()
    {
        mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
        //buttonTutSys = GameObject.Find("Displaybtn").GetComponent<ButtonTutorial>();

        drawRoadWhite = GameObject.Find("DrawRoadWhite").GetComponent<Transform>();
        drawRoad = GameObject.Find("DrawRoad").GetComponent<Transform>();
        roadCount = GameObject.Find("currRoadDisplay").GetComponent<Transform>();
        drawPosition = drawRoad.position;
        drawRoadCount = roadCount.position;

        removeRoad = GameObject.Find("RemoveRoad").GetComponent<Transform>();
        removeRoadWhite = GameObject.Find("RemoveRoadWhite").GetComponent<Transform>();
        removePosition = removeRoad.position;

        displayArrow = GameObject.Find("Displaybtn").GetComponent<Transform>();
        displayArrowWhite = GameObject.Find("DisplaybtnWhite").GetComponent<Transform>();


        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(displayArrowWhite);


        opening = false;
        closing = false;
        timer = 0f;
        closeXPosition = -96f;
        speedMultiply = 5f;

        drawRoadWhite.position = new Vector2(closeXPosition, drawPosition.y);
        drawRoad.position = new Vector2(closeXPosition, drawPosition.y);
        roadCount.position = new Vector2(closeXPosition, drawPosition.y);

        removeRoad.position = new Vector2(closeXPosition, removePosition.y);
        removeRoadWhite.position = new Vector2(closeXPosition, removePosition.y);

        GameObject go3 = GameObject.Find("MoneyText");
        if (go3 != null)
            moneyText = go3.GetComponent<Transform>();

        GameObject go4 = GameObject.Find("CounterText");
        if (go4 != null)
            counterText = go4.GetComponent<Transform>();

    }

    private void OpenTab()
    {
        //Debug.Log("im lerpiong");
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x , drawPosition.x, timer), drawPosition.y);
        Debug.Log(drawPosition.x );

        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, drawPosition.x, timer), drawPosition.y);
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, drawRoadCount.x, timer), drawRoadCount.y + 2.0f);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, removePosition.x, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, removePosition.x, timer), removePosition.y);


        timer += speedMultiply * Time.deltaTime;
        if (timer > 0.8f)
        {
            //Disable<Transform>(displayArrow);
            //Enable<Transform>(displayArrowWhite);

            timer = 0f;
            opening = false;
        }

    }

    private void CloseTab()
    {
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, closeXPosition, timer), drawPosition.y);

        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, closeXPosition, timer), drawPosition.y);
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, closeXPosition, timer), drawRoadCount.y + 2.0f);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, closeXPosition, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, closeXPosition, timer), removePosition.y);

        timer += speedMultiply * Time.deltaTime;
        if (timer > 0.8f)
        {
            //Disable<Transform>(displayArrowWhite);
            //Enable<Transform>(displayArrow);

            timer = 0f;
            closing = false;
        }
    }

   

    public void CallFunctionTut(TutButtonType _tbt, bool _activeType)
    {
        //Debug.Log("Calling " + _bt + " " + _activeType);
        DisableAll();

        if (_activeType)
        {
            switch (_tbt)
            {
                case TutButtonType.Draw:
                    {
                        gameManager.RoadPlacementHandler();
                        Enable<Transform>(drawRoadWhite);

                        EnableAllNormal();

                        Disable<Transform>(drawRoad);
                        break;
                    }
                case TutButtonType.Remove:
                    {
                        gameManager.RemoveRoadHandler();
                        Enable<Transform>(removeRoadWhite);

                        EnableAllNormal();

                        Disable<Transform>(removeRoad);
                        break;
                    }

            }

            SceneManager.SetDrawMode(true);
            gameState.SetDrawMode(true);

        }
        else
        {
            SceneManager.SetDrawMode(false);
            gameState.SetDrawMode(false);

            EnableAllNormal();
        }
    }

    public void SwitchTabTut(bool type)
    {
        Debug.Log("im here");
        if (type)
        {
            Debug.Log("opening");
            opening = true;

            Disable<Transform>(displayArrow);
            Enable<Transform>(displayArrowWhite);


            EnableAllNormal();
        }
        else
        {
            Debug.Log("closing");
            ResetAll();

            closing = true;

            Disable<Transform>(displayArrowWhite);
            Enable<Transform>(displayArrow);
        }
    }



    public override void Update()
    {
        if (opening)
            OpenTab();
        if (closing)
            CloseTab();
    }

    public void EnableAllNormal()
    {
        Enable<Transform>(drawRoad);
        Enable<Transform>(removeRoad);
        Enable<Transform>(roadCount);
    }

    public void DisableAllNormal()
    {
        Disable<Transform>(drawRoad);
        Disable<Transform>(removeRoad);
        Enable<Transform>(roadCount);
        Enable<Transform>(trafficCount);
    }

    public void EnableAllWhite()
    {
        Enable<Transform>(drawRoadWhite);
        Enable<Transform>(removeRoadWhite);
    }

    public void DisableAllWhite()
    {
        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
    }

    public void ResetAll()
    {
        EnableAllNormal();
        DisableAllWhite();


        gameManager.ClearInputActions();

        SceneManager.SetDrawMode(false);
        gameState.SetDrawMode(false);
        //activeType = false;
    }

    public void DisableAll()
    {
        DisableAllNormal();
        DisableAllWhite();

        gameManager.ClearInputActions();

        SceneManager.SetDrawMode(false);
        gameState.SetDrawMode(false);
        //activeType = false;
    }

}