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
    Ignore,
    Latest, //Used to reopen the last buttontype
    None

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

    Transform drawRemoveCar;
    Transform drawRemoveCarWhite;
    Vector2 drawRemoveCarPosition;

    Transform displayArrow;
    UI displayArrowUI;

    Transform placeHospital;
    Transform placeOffice;
    Transform placePark;
    Transform placeMall;
    Transform placePoliceStation;

    UI placeHospitalUI;
    UI placeOfficeUI;
    UI placeParkUI;
    UI placeMallUI;
    UI placePoliceStationUI;

    Vector2 placeHospitalPos;
    Vector2 placeOfficePos;
    Vector2 placeParkPos;
    Vector2 placeMallPos;
    Vector2 placePoliceStationPos;

    Text tooltipText;
    Transform tooltipTrans;
    Vector2 toolTipsDisplayPosition;

    Transform lineDivider1;
    Vector2 line1;

    GameManager gameManager;

    Transform moneyText;

 
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

  

    public override void Start()
    {
        mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();


        /*********************************** DRAWING ************************************/
        drawRoadWhite = GameObject.Find("DrawRoadWhite").GetComponent<Transform>();
        drawRoad = GameObject.Find("DrawRoad").GetComponent<Transform>();
        roadCount = GameObject.Find("currRoadDisplay").GetComponent<Transform>();
        drawPosition = drawRoad.position;
        drawRoadCount = roadCount.position;

        removeRoad = GameObject.Find("RemoveRoad").GetComponent<Transform>();
        removeRoadWhite = GameObject.Find("RemoveRoadWhite").GetComponent<Transform>();
        removePosition = removeRoad.position;

        drawRemoveCar = GameObject.Find("RemoveCar").GetComponent<Transform>();
        drawRemoveCarWhite = GameObject.Find("RemoveCarWhite").GetComponent<Transform>();

        GameObject displayGO = GameObject.Find("Displaybtn");
        displayArrow = displayGO.GetComponent<Transform>();
        displayArrowUI = displayGO.GetComponent<UI>();


        GameObject hopitalGO = GameObject.Find("PlaceHospital");
        placeHospital = hopitalGO.GetComponent<Transform>();
        placeHospitalUI = hopitalGO.GetComponent<UI>();

        GameObject officeGO = GameObject.Find("PlaceOffice");
        placeOffice = officeGO.GetComponent<Transform>();
        placeOfficeUI = officeGO.GetComponent<UI>();

        GameObject parkGO = GameObject.Find("PlacePark");
        placePark = parkGO.GetComponent<Transform>();
        placeParkUI = parkGO.GetComponent<UI>();

        GameObject mallGO = GameObject.Find("PlaceMall");
        placeMall = mallGO.GetComponent<Transform>();
        placeMallUI = mallGO.GetComponent<UI>();

        GameObject psGO = GameObject.Find("PlacePoliceStation");
        placePoliceStation = psGO.GetComponent<Transform>();
        placePoliceStationUI = psGO.GetComponent<UI>();

        placeHospitalPos = placeHospital.position;
        placeOfficePos = placeOffice.position;
        placeParkPos = placePark.position;
        placeMallPos = placeMall.position;
        placePoliceStationPos = placePoliceStation.position;

        lineDivider1 = GameObject.Find("Line1").GetComponent<Transform>();
        line1 = lineDivider1.position;


        GameObject stringNameGo = GameObject.Find("stringname");
        tooltipText = stringNameGo.GetComponent<Text>();
        tooltipTrans = stringNameGo.GetComponent<Transform>();
        toolTipsDisplayPosition = transform.position + new Vector2(-2.40f, 7.70f);


        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(drawRemoveCarWhite);
        Disable<Transform>(trafficCount);


        opening = false;
        closing = false;
        timer = 0f;
        closeXPosition = -96f;
        speedMultiply = 5f;

        /*********************************** Position ************************************/


        drawRoadWhite.position = new Vector2(closeXPosition, drawPosition.y);
        drawRoad.position = new Vector2(closeXPosition, drawPosition.y);
        roadCount.position = new Vector2(closeXPosition, drawPosition.y);

        removeRoad.position = new Vector2(closeXPosition, removePosition.y);
        removeRoadWhite.position = new Vector2(closeXPosition, removePosition.y);

        drawRemoveCar.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);

        placeHospital.position = new Vector2(closeXPosition, placeHospitalPos.y);
        placeOffice.position = new Vector2(closeXPosition, placeOfficePos.y);
        placePark.position = new Vector2(closeXPosition, placeParkPos.y);
        placeMall.position = new Vector2(closeXPosition, placeMallPos.y);
        placePoliceStation.position = new Vector2(closeXPosition, placePoliceStationPos.y);

        lineDivider1.position = new Vector2(closeXPosition, line1.y);


        /*********************************** Game Objects ************************************/
        GameObject go3 = GameObject.Find("MoneyText");
        if (go3 != null)
            moneyText = go3.GetComponent<Transform>();



    }

    private void OpenTab()
    {
        //Debug.Log("im lerpiong");

        /***************************** positions **************************************************/
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, drawPosition.x, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, drawPosition.x, timer), drawPosition.y);
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, drawRoadCount.x, timer), drawRoadCount.y);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, removePosition.x, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, removePosition.x, timer), removePosition.y);

        drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(Mathf.Lerp(drawRemoveCarWhite.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);

        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, placeHospitalPos.x, timer), placeHospitalPos.y);
        placeOffice.position = new Vector2(Mathf.Lerp(placeOffice.position.x, placeOfficePos.x, timer), placeOfficePos.y);
        placePark.position = new Vector2(Mathf.Lerp(placePark.position.x, placeParkPos.x, timer), placeParkPos.y);
        placeMall.position = new Vector2(Mathf.Lerp(placeMall.position.x, placeMallPos.x, timer), placeMallPos.y);
        placePoliceStation.position = new Vector2(Mathf.Lerp(placePoliceStation.position.x, placePoliceStationPos.x, timer), placePoliceStationPos.y);

        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, line1.x, timer), line1.y);

        /***************************** Timer **************************************************/
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

        /***************************** positions **************************************************/
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, closeXPosition, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, closeXPosition, timer), drawPosition.y);
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, closeXPosition, timer), drawRoadCount.y);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, closeXPosition, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, closeXPosition, timer), removePosition.y);

        drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, closeXPosition, timer), drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(Mathf.Lerp(drawRemoveCarWhite.position.x, closeXPosition, timer), drawRemoveCarPosition.y);


        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, closeXPosition, timer), placeHospitalPos.y);
        placeOffice.position = new Vector2(Mathf.Lerp(placeOffice.position.x, closeXPosition, timer), placeOfficePos.y);
        placePark.position = new Vector2(Mathf.Lerp(placePark.position.x, closeXPosition, timer), placeParkPos.y);
        placeMall.position = new Vector2(Mathf.Lerp(placeMall.position.x, closeXPosition, timer), placeMallPos.y);
        placePoliceStation.position = new Vector2(Mathf.Lerp(placePoliceStation.position.x, closeXPosition, timer), placePoliceStationPos.y);


        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, closeXPosition, timer), line1.y);

        /***************************** Timer **************************************************/
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
        if (_tbt == TutButtonType.Latest) _tbt = choosenButton;

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
            case TutButtonType.PlaceOffice:
                {
                    placeOfficeUI.ChangeTexture("Game/UI/ERP");
                    break;
                }
            case TutButtonType.PlacePark:
                {
                    placeParkUI.ChangeTexture("Game/UI/ERP");
                    break;
                }
            case TutButtonType.PlaceMall:
                {
                    placeMallUI.ChangeTexture("Game/UI/ERP");
                    break;
                }
            case TutButtonType.PlacePoliceStation:
                {
                    placePoliceStationUI.ChangeTexture("Game/UI/ERP");
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
                        Enable<Transform>(drawRoadWhite);

                        EnableAllNormalExcept(TutButtonType.Draw);

                        break;
                    }
                case TutButtonType.Remove:
                    {
                        gameManager.RemoveRoadHandler();
                        Enable<Transform>(removeRoadWhite);

                        EnableAllNormalExcept(TutButtonType.Remove);
                        break;
                    }
                case TutButtonType.RemoveCar:
                    {
                        gameManager.RemoveCarHandler();

                        Enable<Transform>(drawRemoveCarWhite);

                        EnableAllNormalExcept(TutButtonType.RemoveCar);

                        break;
                    }

                case TutButtonType.PlaceHospital:
                    {
                        gameManager.PlaceDestHospitalHandler();
                        placeHospitalUI.ChangeTexture("Game/UI/Arrow_L");

                        EnableAllNormalExcept();
                        break;
                    }
                case TutButtonType.PlaceOffice:
                    {
                        gameManager.PlaceDestOfficeHandler();
                        placeOfficeUI.ChangeTexture("Game/UI/Arrow_L");

                        EnableAllNormalExcept();
                        break;
                    }
                case TutButtonType.PlacePark:
                    {
                        gameManager.PlaceDestParkHandler();

                        placeParkUI.ChangeTexture("Game/UI/Arrow_L");

                        EnableAllNormalExcept();
                        break;
                    }
                case TutButtonType.PlaceMall:
                    {
                        gameManager.PlaceDestMallHandler();
                        placeMallUI.ChangeTexture("Game/UI/Arrow_L");

                        EnableAllNormalExcept();
                        break;
                    }
                case TutButtonType.PlacePoliceStation:
                    {
                        gameManager.PlaceDestPoliceStationHandler();
                        placePoliceStationUI.ChangeTexture("Game/UI/Arrow_L");

                        EnableAllNormalExcept();
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

            EnableAllNormalExcept();

            _tbt = TutButtonType.None;
        }


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

            EnableAllNormalExcept();

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

        /****Shortcut keys in game***/
        if (Input.GetKeyDown(KeyCode.H)) CallFunctionTut(TutButtonType.PlaceHospital);
        if (Input.GetKeyDown(KeyCode.M)) CallFunctionTut(TutButtonType.PlaceMall);
        if (Input.GetKeyDown(KeyCode.P)) CallFunctionTut(TutButtonType.PlacePark);
        if (Input.GetKeyDown(KeyCode.O)) CallFunctionTut(TutButtonType.PlaceOffice);
        if (Input.GetKeyDown(KeyCode.S)) CallFunctionTut(TutButtonType.PlacePoliceStation);

    }


    public void EnableAllWhite()
    {
        Enable<Transform>(drawRoadWhite);
        Enable<Transform>(removeRoadWhite);
        Enable<Transform>(drawRemoveCarWhite);
    }

    public void DisableAllWhite()
    {
        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(drawRemoveCarWhite);
    }


    public void ResetAll()
    {
        EnableAllNormalExcept();
        DisableAllWhite();

        gameManager.ClearInputActions();

        SceneManager.SetDrawMode(false);
        //gameState.SetDrawMode(false);
        //activeType = false;
    }

    public void DisableAllNormal()
    {
        Disable<Transform>(drawRoad);
        Disable<Transform>(removeRoad);
        Disable<Transform>(drawRemoveCar);
        Disable<Transform>(roadCount);
        Disable<Transform>(trafficCount);
    }

    public void DisableAll()
    {
        DisableAllNormal();
        DisableAllWhite();

        gameManager.ClearInputActions();

        SceneManager.SetDrawMode(false);
        //gameState.SetDrawMode(false);
        //activeType = false;
    }

    public void EnableAllNormalExcept(TutButtonType tbt = TutButtonType.Ignore)
    {
        if (tbt != TutButtonType.Draw)
            Enable<Transform>(drawRoad);
        if (tbt != TutButtonType.Remove)
            Enable<Transform>(removeRoad);
        Enable<Transform>(roadCount);

        if (tbt != TutButtonType.RemoveCar)
            Enable<Transform>(drawRemoveCar);

      
    }

}