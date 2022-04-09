using System;

public enum TutButtonType
{
    Draw = 0,
    Remove,
    ERP,
    TrafficLight,
    RemoveCar,
    PlaceHospital,
    PlaceOffice,
    PlacePark,
    PlaceMall,
    PlacePoliceStation,
    Display,
    Ignore,
    Latest, //Used to reopen the last buttontype
    RoadTab,
    BuildingsTab,
    None

}

public class ButtonTutorial : MonoBehaviour
{
    Transform roadTab;
    UI roadTabUI;
    Transform buildingsTab;
    UI buildingsTabUI;

    Transform drawRoadWhite;
    Transform drawRoad;
    Transform roadCount;
    Vector2 drawPosition;
    Vector2 drawRoadCount;

    Transform removeRoad;
    Transform removeRoadWhite;
    Transform trafficCount;
    Vector2 removePosition;

    Transform drawERP;
    Transform drawERPWhite;
    Transform ERPCount;
    Vector2 erpPosition;
    Vector2 drawERPCount;

    Transform drawTraffic;
    Transform drawTrafficWhite;
    Vector2 trafficPosition;
    Vector2 drawTrafficCount;

    Transform drawRemoveCar;
    Transform drawRemoveCarWhite;
    Vector2 drawRemoveCarPosition;

    //Transform displayArrow;
    //UI displayArrowUI;

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

    Transform dayClockText;

    GameManager gameManager;

    Transform moneyText;

 
    private Camera mainCamera;

    static public bool roadTabOpen;
    static public bool roadTabClose;
    static public bool buildingsTabOpen;
    static public bool buildingsTabClose;

    public bool roadTabIsOn;
    public bool buildingsTabIsOn;

    float timer;

    float closeXPosition;

    float speedMultiply;

    // ButtonTutorial buttonTutSys;

    TutButtonType tbt;
    TutButtonType choosenButton = TutButtonType.None;

    public bool isOn;
    bool displayState = false;

    CombinedUI combinedUI;



    public override void Start()
    {

        combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();
        mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();

        dayClockText = GameObject.Find("DayClock").GetComponent<Transform>();

        /*********************************** DRAWING ************************************/
        if (entityId == GameObject.Find("DisplayRoadBtn").GetComponent<Transform>().entityId)
        {
            drawRoadWhite = GameObject.Find("DrawRoadWhite").GetComponent<Transform>();
            drawRoad = GameObject.Find("DrawRoad").GetComponent<Transform>();
            drawPosition = drawRoad.position;

            removeRoad = GameObject.Find("RemoveRoad").GetComponent<Transform>();
            removeRoadWhite = GameObject.Find("RemoveRoadWhite").GetComponent<Transform>();
            removePosition = removeRoad.position;

            drawERP = GameObject.Find("ERPbtn").GetComponent<Transform>();
            drawERPWhite = GameObject.Find("ERPbtnWhite").GetComponent<Transform>();
            erpPosition = drawERP.position;

            drawTraffic = GameObject.Find("TrafficLight").GetComponent<Transform>();
            drawTrafficWhite = GameObject.Find("TrafficLightWhite").GetComponent<Transform>();
            trafficPosition = drawTraffic.position;

            drawRemoveCar = GameObject.Find("RemoveCar").GetComponent<Transform>();
            drawRemoveCarWhite = GameObject.Find("RemoveCarWhite").GetComponent<Transform>();
            //drawRemoveCar = GameObject.Find("RemoveCar").GetComponent<Transform>();
            //drawRemoveCarWhite = GameObject.Find("RemoveCarWhite").GetComponent<Transform>();
            drawRemoveCarPosition = drawRemoveCar.position;

            GameObject displayRoadTabGO = GameObject.Find("DisplayRoadBtn");
            roadTab = displayRoadTabGO.GetComponent<Transform>();
            roadTabUI = displayRoadTabGO.GetComponent<UI>();


            tbt = TutButtonType.RoadTab;
            drawRoadWhite.position = new Vector2(closeXPosition, drawPosition.y);
            drawRoad.position = new Vector2(closeXPosition, drawPosition.y);

            removeRoad.position = new Vector2(closeXPosition, removePosition.y);
            removeRoadWhite.position = new Vector2(closeXPosition, removePosition.y);

            drawERP.position = new Vector2(closeXPosition, erpPosition.y);
            drawERPWhite.position = new Vector2(closeXPosition, erpPosition.y);

            drawTraffic.position = new Vector2(closeXPosition, trafficPosition.y);
            drawTrafficWhite.position = new Vector2(closeXPosition, trafficPosition.y);

            drawRemoveCar.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);
            drawRemoveCarWhite.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);



            Disable<Transform>(drawRoadWhite);
            Disable<Transform>(removeRoadWhite);
            Disable<Transform>(drawERPWhite);
            Disable<Transform>(drawTrafficWhite);
            Disable<Transform>(drawRemoveCarWhite);

            Disable<Transform>(drawERP);
            Disable<Transform>(drawTraffic);
        }

        else if (entityId == GameObject.Find("DisplayBuildingsBtn").GetComponent<Transform>().entityId)
        {
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

            GameObject displayBuildingsTabGO = GameObject.Find("DisplayBuildingsBtn");
            buildingsTab = displayBuildingsTabGO.GetComponent<Transform>();
            buildingsTabUI = displayBuildingsTabGO.GetComponent<UI>();

            placeHospitalPos = placeHospital.position;
            placeOfficePos = placeOffice.position;
            placeParkPos = placePark.position;
            placeMallPos = placeMall.position;
            placePoliceStationPos = placePoliceStation.position;


            tbt = TutButtonType.BuildingsTab;
            placeHospital.position = new Vector2(closeXPosition, placeHospitalPos.y);
            placeOffice.position = new Vector2(closeXPosition, placeOfficePos.y);
            placePark.position = new Vector2(closeXPosition, placeParkPos.y);
            placeMall.position = new Vector2(closeXPosition, placeMallPos.y);
            placePoliceStation.position = new Vector2(closeXPosition, placePoliceStationPos.y);
        }

        lineDivider1 = GameObject.Find("Line1").GetComponent<Transform>();
        line1 = lineDivider1.position;


        GameObject stringNameGo = GameObject.Find("stringname");
        tooltipText = stringNameGo.GetComponent<Text>();
        tooltipTrans = stringNameGo.GetComponent<Transform>();
        toolTipsDisplayPosition = transform.position + new Vector2(-2.40f, 7.70f);

        Disable<Transform>(dayClockText);

        roadTabOpen = false;
        roadTabClose = false;
        buildingsTabOpen = false;
        buildingsTabClose = false;

        roadTabIsOn = false;
        buildingsTabIsOn = false;

        timer = 0f;
        closeXPosition = -96f;
        speedMultiply = 5f;

        /*********************************** Game Objects ************************************/
        GameObject go3 = GameObject.Find("MoneyText");
        if (go3 != null)
            moneyText = go3.GetComponent<Transform>();



    }

    private void CloseRoadTabs()
    {
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, closeXPosition, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, closeXPosition, timer), drawPosition.y);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, closeXPosition, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, closeXPosition, timer), removePosition.y);

        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, closeXPosition, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, closeXPosition, timer), erpPosition.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, closeXPosition, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, closeXPosition, timer), trafficPosition.y);

        drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, closeXPosition, timer), drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(Mathf.Lerp(drawRemoveCarWhite.position.x, closeXPosition, timer), drawRemoveCarPosition.y);

        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, closeXPosition, timer), line1.y);



        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {


            timer = 0f;
            roadTabClose = false;
        }
    }

    private void CloseBuildingsTabs()
    {

        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, closeXPosition, timer), placeHospitalPos.y);
        placeOffice.position = new Vector2(Mathf.Lerp(placeOffice.position.x, closeXPosition, timer), placeOfficePos.y);
        placePark.position = new Vector2(Mathf.Lerp(placePark.position.x, closeXPosition, timer), placeParkPos.y);
        placeMall.position = new Vector2(Mathf.Lerp(placeMall.position.x, closeXPosition, timer), placeMallPos.y);
        placePoliceStation.position = new Vector2(Mathf.Lerp(placePoliceStation.position.x, closeXPosition, timer), placePoliceStationPos.y);

        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {
            timer = 0f;
            buildingsTabClose = false;
        }
    }

    private void OpenRoadTabs()
    {

        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, drawPosition.x, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, drawPosition.x, timer), drawPosition.y);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, removePosition.x, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, removePosition.x, timer), removePosition.y);

        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, erpPosition.x, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, erpPosition.x, timer), erpPosition.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, trafficPosition.x, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, trafficPosition.x, timer), trafficPosition.y);

        drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(Mathf.Lerp(drawRemoveCarWhite.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);

        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, line1.x, timer), line1.y);


        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {


            timer = 0f;
            roadTabOpen = false;
        }

    }

    private void OpenBuildingsTabs()
    {
        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, placeHospitalPos.x, timer), placeHospitalPos.y);
        placeOffice.position = new Vector2(Mathf.Lerp(placeOffice.position.x, placeOfficePos.x, timer), placeOfficePos.y);
        placePark.position = new Vector2(Mathf.Lerp(placePark.position.x, placeParkPos.x, timer), placeParkPos.y);
        placeMall.position = new Vector2(Mathf.Lerp(placeMall.position.x, placeMallPos.x, timer), placeMallPos.y);
        placePoliceStation.position = new Vector2(Mathf.Lerp(placePoliceStation.position.x, placePoliceStationPos.x, timer), placePoliceStationPos.y);

        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {


            timer = 0f;
            buildingsTabOpen = false;
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
                    placeHospitalUI.ChangeTexture("Game/UI/Hospital");
                    break;
                }
            case TutButtonType.PlaceOffice:
                {
                    placeOfficeUI.ChangeTexture("Game/UI/Office");
                    break;
                }
            case TutButtonType.PlacePark:
                {
                    placeParkUI.ChangeTexture("Game/UI/Park");
                    break;
                }
            case TutButtonType.PlaceMall:
                {
                    placeMallUI.ChangeTexture("Game/UI/ShoppingMall");
                    break;
                }
            case TutButtonType.PlacePoliceStation:
                {
                    placePoliceStationUI.ChangeTexture("Game/UI/PoliceStation");
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
                        gameManager.RemoveStructureHandler();
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
                        placeHospitalUI.ChangeTexture("Game/UI/Hospital_Click");

                        EnableAllNormalExcept();
                        break;
                    }
                case TutButtonType.PlaceOffice:
                    {
                        gameManager.PlaceDestOfficeHandler();
                        placeOfficeUI.ChangeTexture("Game/UI/Office_Click");

                        EnableAllNormalExcept();
                        break;
                    }
                case TutButtonType.PlacePark:
                    {
                        gameManager.PlaceDestParkHandler();

                        placeParkUI.ChangeTexture("Game/UI/Park_Click");

                        EnableAllNormalExcept();
                        break;
                    }
                case TutButtonType.PlaceMall:
                    {
                        gameManager.PlaceDestMallHandler();
                        placeMallUI.ChangeTexture("Game/UI/ShoppingMall_Click");

                        EnableAllNormalExcept();
                        break;
                    }
                case TutButtonType.PlacePoliceStation:
                    {
                        gameManager.PlaceDestPoliceStationHandler();
                        placePoliceStationUI.ChangeTexture("Game/UI/PoliceStation_Click");

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
        switch (tbt)
        {
            case TutButtonType.RoadTab:
                {
                    SetToolTips(true, toolTipsDisplayPosition, "Display Road Buttons");
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                        SwitchTabRoad(!displayState);
                    break;
                }
            case TutButtonType.BuildingsTab:
                {
                    SetToolTips(true, toolTipsDisplayPosition, "Display Buildings Buttons");
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                        SwitchTabBuildings(!displayState);
                    break;
                }
            default:
                break;
        }
    }

    public override void OnMouseExit()
    {
        SetToolTips(false, Vector2.zero);
    }

    public void SwitchTabRoad(bool type, bool reenable = true)
    {
        if (type)
        {
            roadTabOpen = true;

            roadTabUI.ChangeTexture("Game/UI/Arrow_L");

            EnableAllNormalExcept();

            Enable<Transform>(lineDivider1);

            roadTabIsOn = true;
            buildingsTabIsOn = false;
        }
        else
        {
            ResetAll();


            roadTabClose = true;
            buildingsTabClose = true;

            roadTabUI.ChangeTexture("Game/UI/Arrow_R");

            roadTabIsOn = false;
            buildingsTabIsOn = false;
        }

        displayState = type;
    }
    public void SwitchTabBuildings(bool type, bool reenable = true)
    {
        if (type)
        {

            roadTabOpen = false;
            buildingsTabOpen = true;

            buildingsTabUI.ChangeTexture("Game/UI/Arrow_L");
            EnableAllNormalExcept();

            roadTabIsOn = false;
            buildingsTabIsOn = true;
        }
        else
        {
            ResetAll();
 
            roadTabClose = true;
            buildingsTabClose = true;

            buildingsTabUI.ChangeTexture("Game/UI/Arrow_R");
          
            roadTabIsOn = false;
            buildingsTabIsOn = false;
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

    public override void FixedUpdate()
    {

        //if (opening)
        //    OpenTabs();
        //if (closing)
        //    CloseTabs();

        if (roadTabOpen)
        {
            if (tbt == TutButtonType.RoadTab)
                OpenRoadTabs();
            else
                CloseBuildingsTabs();
        }

        if (roadTabClose)
        {
            if (tbt == TutButtonType.RoadTab)
                CloseRoadTabs();
            //CloseBuildingsTabs();
        }

        if (buildingsTabOpen)
        {
            if (tbt == TutButtonType.BuildingsTab)
                OpenBuildingsTabs();
            else
                CloseRoadTabs();
        }

        if (buildingsTabClose)
        {
            if (tbt == TutButtonType.BuildingsTab)
                CloseBuildingsTabs();
            //CloseRoadTabs();
        }

        /****Shortcut keys in game***/
        if (Input.GetKeyDown(KeyCode.T1)) CallFunctionTut(TutButtonType.PlaceHospital);
        if (Input.GetKeyDown(KeyCode.T2)) CallFunctionTut(TutButtonType.PlaceMall);
        if (Input.GetKeyDown(KeyCode.T3)) CallFunctionTut(TutButtonType.PlacePark);
        if (Input.GetKeyDown(KeyCode.T4)) CallFunctionTut(TutButtonType.PlaceOffice);
        if (Input.GetKeyDown(KeyCode.T5)) CallFunctionTut(TutButtonType.PlacePoliceStation);
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
        Disable<Transform>(dayClockText);
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
        Disable<Transform>(dayClockText);
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

    public override void OnMouseEnter()
    {
        InputManager.allowBuilding = false;
    }

}