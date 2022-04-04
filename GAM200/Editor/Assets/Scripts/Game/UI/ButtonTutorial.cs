using System;

public enum TutButtonType
{
    Display = 1,
    Draw,
    Remove,
    RemoveCar,
    PlaceHospital,
    PlaceOffice,
    PlacePark,
    PlaceMall,
    PlacePoliceStation,
    None

}

public class ButtonTutorial : MonoBehaviour
{
    //Transform drawRoadWhite;
    Transform drawRoad;
    Transform roadCount;
   // Transform drawRoadGlow;

    Vector2 drawPosition;
    Vector2 drawRoadCount;

    Transform removeRoad;
    Vector2 removePosition;

    Transform displayArrow;
    UI displayArrowUI;


    Transform drawRemoveCar;
    Transform drawRemoveCarWhite;
    Vector2 drawRemoveCarPosition;

    Transform placeHospital;
    UI placeHospitalUI;
    Vector2 placeHospitalPos;

    GameManager gameManager;

    Transform moneyText;

    Transform lineDivider1;
    Vector2 line1;

    private Camera mainCamera;

    public bool opening;
    public bool closing;
    float timer;

    float closeXPosition;

    float speedMultiply;

    ButtonTutorial buttonTutSys;

    TutButtonType choosenButton = TutButtonType.None;

    public bool isOn;
    bool displayState = false;

    Text tooltipText;
    Transform tooltipTrans;
    Vector2 toolTipsDisplayPosition;

    public override void Start()
    {
        mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();


        /*********************************** DRAWING ************************************/
        drawRoad = GameObject.Find("DrawRoad").GetComponent<Transform>();
        roadCount = GameObject.Find("currRoadDisplay").GetComponent<Transform>();
        drawPosition = drawRoad.position;
        drawRoadCount = roadCount.position;

        removeRoad = GameObject.Find("RemoveRoad").GetComponent<Transform>();
        removePosition = removeRoad.position;

        drawRemoveCar = GameObject.Find("RemoveCar").GetComponent<Transform>();
        drawRemoveCarWhite = GameObject.Find("RemoveCarWhite").GetComponent<Transform>();
        drawRemoveCarPosition = drawRemoveCar.position;

        GameObject displayGO = GameObject.Find("Displaybtn");
        displayArrow = displayGO.GetComponent<Transform>();
        displayArrowUI = displayGO.GetComponent<UI>();
       

        GameObject hopitalGO = GameObject.Find("PlaceHospital");
        placeHospital = hopitalGO.GetComponent<Transform>();
        placeHospitalUI = hopitalGO.GetComponent<UI>();

        placeHospitalPos = placeHospital.position;

        lineDivider1 = GameObject.Find("Line1").GetComponent<Transform>();
        line1 = lineDivider1.position;


        GameObject stringNameGo = GameObject.Find("stringname");
        tooltipText = stringNameGo.GetComponent<Text>();
        tooltipTrans = stringNameGo.GetComponent<Transform>();
        toolTipsDisplayPosition = transform.position + new Vector2(-2.40f, 7.70f);


        Disable<Transform>(drawRoad);
        Disable<Transform>(removeRoad);


        opening = false;
        closing = false;
        timer = 0f;
        closeXPosition = -96f;
        speedMultiply = 5f;

        /*********************************** Position ************************************/


        drawRoad.position = new Vector2(closeXPosition, drawPosition.y);
        roadCount.position = new Vector2(closeXPosition, drawPosition.y);
        removeRoad.position = new Vector2(closeXPosition, removePosition.y);
        drawRemoveCar.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);


        /*********************************** Game Objects ************************************/
        GameObject go3 = GameObject.Find("MoneyText");
        if (go3 != null)
            moneyText = go3.GetComponent<Transform>();

   

    }

    private void OpenTab()
    {
        //Debug.Log("im lerpiong");
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, drawPosition.x, timer), drawPosition.y);
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, drawRoadCount.x, timer), drawRoadCount.y);
        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, removePosition.x, timer), removePosition.y);
        drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(Mathf.Lerp(drawRemoveCarWhite.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);
        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, placeHospitalPos.x, timer), placeHospitalPos.y);


        timer += speedMultiply * Time.deltaTime;
        if (timer >= 1f)
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
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, closeXPosition, timer), drawRoadCount.y);
        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, closeXPosition, timer), removePosition.y);
        drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, closeXPosition, timer), drawRemoveCarPosition.y);
        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, closeXPosition, timer), placeHospitalPos.y);

        timer += speedMultiply * Time.deltaTime;
        if (timer >= 1f)
        {

            timer = 0f;
            closing = false;
        }
    }

   

    public void CallFunctionTut(TutButtonType _tbt)
    {
        //Debug.Log("Calling " + _bt + " " + _activeType);
        bool _activeType = true;

        if (_tbt == choosenButton) _activeType = false;

        switch (choosenButton)
        {
            case TutButtonType.Draw:
                {

                    break;
                }
            case TutButtonType.Remove:
                {

                    break;
                }
            case TutButtonType.RemoveCar:
                {

                    break;
                }

            case TutButtonType.PlaceHospital:
                {
                    placeHospitalUI.ChangeTexture("Game/UI/ERP");
                    break;
                }
        }

        DisableAll();

        if (_activeType)
        {
            switch (_tbt)
            {
                case TutButtonType.Draw:
                    {
                        gameManager.RoadPlacementHandler();
                        //Enable<Transform>(drawRoadWhite);

                        EnableAllNormal();

                        Disable<Transform>(drawRoad);
                        break;
                    }
                case TutButtonType.Remove:
                    {
                        gameManager.RemoveRoadHandler();
                        //Enable<Transform>(removeRoadWhite);

                        EnableAllNormal();

                        Disable<Transform>(removeRoad);
                        break;
                    }

            }

            SceneManager.SetDrawMode(true);
            //gameState.SetDrawMode(true);

        }
        else
        {
            SceneManager.SetDrawMode(false);
            //gameState.SetDrawMode(false);

            EnableAllNormal();
        }

        if (_tbt == choosenButton) _tbt = TutButtonType.None;
        choosenButton = _tbt;
    }

    public override void OnMouseOver()
    {
        SetToolTips(true, toolTipsDisplayPosition, "Display buttons");

        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            SwitchTabTut(!displayState);
        }
    }

    public override void OnMouseExit()
    {
        SetToolTips(false, Vector2.zero);
    }

    public void SwitchTabTut(bool type)
    {
        Debug.Log("im here");
        if (type)
        {
            Debug.Log("opening");
            opening = true;

            displayArrowUI.ChangeTexture("Game/UI/Arrow_L");
            //Enable<Transform>(displayArrowWhite);
            Enable<Transform>(lineDivider1);

            EnableAllNormal();

            isOn = true;
        }
        else
        {
            Debug.Log("closing");
            ResetAll();

            closing = true;


            //Disable<Transform>(displayArrowWhite);
            displayArrowUI.ChangeTexture("Game/UI/Arrow_R");
            isOn = false;
        }

        displayState = type;
    }

    public void SetToolTips(bool state, Vector2 position, string textToPut = "")
    {
        if (state)
        {
            Enable<Transform>(tooltipTrans);
            tooltipTrans.position = position;
            tooltipText.text = textToPut;
        }
        else Disable<Transform>(tooltipTrans);


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
       // Enable<Transform>(trafficCount);
    }

 
    public void ResetAll()
    {
        EnableAllNormal();
 
        gameManager.ClearInputActions();

        SceneManager.SetDrawMode(false);
        //gameState.SetDrawMode(false);
        //activeType = false;
    }

    public void DisableAll()
    {
        DisableAllNormal();

        gameManager.ClearInputActions();

        SceneManager.SetDrawMode(false);
       // gameState.SetDrawMode(false);
        //activeType = false;
    }

}