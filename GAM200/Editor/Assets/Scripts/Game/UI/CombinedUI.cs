
public enum UIType
{
    Pause = 0,
    Time,
    Store,
    Road, //Bottom left button that build road and stuff
    None
}
public class CombinedUI : MonoBehaviour
{
 
    PauseMenu pauseMenu;
    TimeSystem timeSystem;
    //ButtonStore buttonStore;
    public ButtonRoadTab roadTab;
    public ButtonBuildingsTab buildingsTab;

    Transform pauseIcon;
    Transform timerButton;
    Transform roadTabTransform;
    Transform buildingsTabTransform;
    Transform displayTabTransform;
    //Transform removeRoad;
    //Transform removeRoadWhite;
    //Transform drawRemoveCar;
    //Transform drawRemoveCarWhite;

    Transform moneyText;
    Transform coinSymbol;
    Transform dayClock;
    Transform dayTimer;
    Transform maintenancefee;
    Transform maintenanceIcon;
    Transform ampm;
    Transform listOfCostText;
    UI listOfCostDestUI;

    bool isRoadTabOpen;
    bool isBuildingsTabOpen;
    //bool isClockOpen;

    GameManager gameManager;
    GameState gameState;

    Text tooltipText;
    Transform tooltipTrans;
    
    static public ButtonType choosenButton = ButtonType.None;
    static public bool allowKeyButton = true;

    public override void Start()
    {
        pauseMenu = GameObject.Find("PauseIcon").GetComponent<PauseMenu>();
        timeSystem = GameObject.Find("TimerIcon").GetComponent<TimeSystem>();
        roadTab = GameObject.Find("DisplayRoadBtn").GetComponent<ButtonRoadTab>();
        buildingsTab = GameObject.Find("DisplayBuildingsBtn").GetComponent<ButtonBuildingsTab>();

        pauseIcon = GameObject.Find("PauseIcon").GetComponent<Transform>();
        timerButton = GameObject.Find("TimerIcon").GetComponent<Transform>();
        roadTabTransform = GameObject.Find("DisplayRoadBtn").GetComponent<Transform>();
        buildingsTabTransform = GameObject.Find("DisplayBuildingsBtn").GetComponent<Transform>();
        displayTabTransform = GameObject.Find("DisplayTab").GetComponent<Transform>();


        moneyText = GameObject.Find("MoneyText").GetComponent<Transform>();
        coinSymbol = GameObject.Find("CoinBag").GetComponent<Transform>();
        dayClock = GameObject.Find("DayClock").GetComponent<Transform>();
        dayTimer = GameObject.Find("Clock").GetComponent<Transform>();
        ampm = GameObject.Find("AMPM").GetComponent<Transform>();
        maintenancefee = GameObject.Find("MaintenanceFee").GetComponent<Transform>();
        maintenanceIcon = GameObject.Find("MaintenanceIcon").GetComponent<Transform>();

        //removeRoad = GameObject.Find("RemoveRoad").GetComponent<Transform>();
        //removeRoadWhite = GameObject.Find("RemoveRoadWhite").GetComponent<Transform>();
        //drawRemoveCar = GameObject.Find("RemoveCar").GetComponent<Transform>();
        //drawRemoveCarWhite = GameObject.Find("RemoveCarWhite").GetComponent<Transform>();

        listOfCostText = GameObject.Find("ListOfCostText").GetComponent<Transform>();
        listOfCostDestUI = GameObject.Find("ListOfCostDest").GetComponent<UI>();

        isRoadTabOpen = false;
        isBuildingsTabOpen = false;
        //isClockOpen = false;

        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        GameObject stringNameGo = GameObject.Find("stringname");
        tooltipText = stringNameGo.GetComponent<Text>();
        tooltipTrans = stringNameGo.GetComponent<Transform>();

    }

    public void CloseAllUIExcept(UIType uitype)
    {
        if (roadTab.roadTabIsOn) isRoadTabOpen = true;
        else isRoadTabOpen = false;
        if (buildingsTab.buildingsTabIsOn) isBuildingsTabOpen = true;
        else isBuildingsTabOpen = false;

        //if (timeSystem.isOn) isClockOpen = true;
        //else isClockOpen = false;

        switch (uitype)
        {
            case UIType.Pause:
                {
                    SceneManager.drawNonUI = false;

                    //timeSystem.SwitchTabTimer(false, false);
                    timeSystem.FullClose();
                    //buttonStore.SwitchTabStore(false, false);
                    roadTab.SwitchTabRoad(false, false);
                    buildingsTab.SwitchTabBuildings(false, false);

                    Disable<Transform>(timerButton);
                    Disable<Transform>(roadTabTransform);
                    Disable<Transform>(buildingsTabTransform);
                    Disable<Transform>(displayTabTransform);

                    Disable<Transform>(moneyText);
                    Disable<Transform>(coinSymbol);
                    Disable<Transform>(dayClock);

                    Disable<Transform>(maintenancefee);
                    Disable<Transform>(maintenanceIcon);

                    Disable<Transform>(listOfCostText);

                    Disable<Transform>(tooltipTrans);

                    listOfCostDestUI.alpha = 0f;

                    allowKeyButton = false;
                    break;             
                }
            //case UIType.Time:
            //    {
            //        pauseMenu.SwitchTabPause(false, false);
            //        buttonStore.SwitchTabStore(false, false);
            //        buttonRoad.SwitchTabRoad(false, false);
            //
            //        Disable<Transform>(pauseIcon);
            //        Disable<Transform>(storeButton);
            //        Disable<Transform>(displayArrow);
            //        break;
            //    }
            //case UIType.Store:
            //    {
            //        SceneManager.drawNonUI = false;
            //
            //        pauseMenu.SwitchTabPause(false, false);
            //        timeSystem.SwitchTabTimer(false, false);
            //        roadTab.SwitchTabRoad(false, false);
            //        buildingsTab.SwitchTabBuildings(false, false);
            //
            //        Disable<Transform>(pauseIcon);
            //        Disable<Transform>(timerButton);
            //        Disable<Transform>(roadTabTransform);
            //        Disable<Transform>(buildingsTabTransform);
            //        break;
            //    }
            //case UIType.Road:
            //    {
            //        SceneManager.drawNonUI = false;
            //
            //
            //        pauseMenu.SwitchTabPause(false, false);
            //        timeSystem.SwitchTabTimer(false, false);
            //        //buttonStore.SwitchTabStore(false, false);
            //        //roadTab.SwitchTabRoad(false, true);
            //        //buildingsTab.SwitchTabBuildings(false, true);
            //
            //        Disable<Transform>(pauseIcon);
            //        Disable<Transform>(timerButton);
            //        //Disable<Transform>(roadTabTransform);
            //        //Disable<Transform>(buildingsTabTransform);
            //        Disable<Transform>(dayClock);
            //        Disable<Transform>(dayTimer);
            //        Disable<Transform>(ampm);
            //        Disable<Transform>(maintenancefee);
            //        Disable<Transform>(maintenanceIcon);
            //
            //        Disable<Transform>(listOfCostText);
            //        listOfCostDestUI.alpha = 0f;
            //        break;
            //    }
            case UIType.None:
                {
                    SceneManager.drawNonUI = false;

                    if (pauseMenu != null)
                        pauseMenu.SwitchTabPause(false, false);
                    //timeSystem.SwitchTabTimer(false, false);
                    timeSystem.FullClose();
                    //buttonStore.SwitchTabStore(false, false);
                    roadTab.SwitchTabRoad(false, false);
                    buildingsTab.SwitchTabBuildings(false, false);

                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(timerButton);
                    Disable<Transform>(roadTabTransform);
                    Disable<Transform>(buildingsTabTransform);
                    Disable<Transform>(displayTabTransform);
                    Disable<Transform>(dayClock);
                    Disable<Transform>(dayTimer);
                    Disable<Transform>(ampm);
                    Disable<Transform>(maintenancefee);
                    Disable<Transform>(maintenanceIcon);

                    Disable<Transform>(roadTab.removeRoad);
                    Disable<Transform>(roadTab.removeRoadWhite);
                    Disable<Transform>(roadTab.drawRemoveCar);
                    Disable<Transform>(roadTab.drawRemoveCarWhite);

                    Disable<Transform>(listOfCostText);
                    listOfCostDestUI.alpha = 0f;

                    allowKeyButton = true;
                    break;
                }
        }
    }

    public void EnableAllMasterButton()
    {
        SceneManager.drawNonUI = true;

        Enable<Transform>(pauseIcon);
        Enable<Transform>(timerButton);

        if (isRoadTabOpen)
        {
            roadTab.SwitchTabRoad(true, false);
            BRCallFunction(ButtonType.Latest);
        }
        if (isBuildingsTabOpen)
        {
            buildingsTab.SwitchTabBuildings(true, false);
            BRCallFunction(ButtonType.Latest);
        }

        allowKeyButton = true;

        //if (isClockOpen)
        {
            //timeSystem.SwitchTabTimer(true);
            timeSystem.FullOpen();
        }
            //Enable<Transform>(displayArrow);
        Enable<Transform>(roadTabTransform);
        Enable<Transform>(buildingsTabTransform);
        Enable<Transform>(displayTabTransform);
        Enable<Transform>(moneyText);
        Enable<Transform>(coinSymbol);
        Enable<Transform>(dayClock);
        Enable<Transform>(dayTimer);
        Enable<Transform>(ampm);
        Enable<Transform>(maintenancefee);
        Enable<Transform>(maintenanceIcon);

        Enable<Transform>(roadTab.removeRoad);
        Enable<Transform>(roadTab.drawRemoveCar);

        Enable<Transform>(listOfCostText);
        listOfCostDestUI.alpha = 1f;
    }


    public void BRCallFunction(ButtonType _bt)
    {
        bool _activeType = true;
        if (_bt == choosenButton) _activeType = false;
        if (_bt == ButtonType.Latest) _bt = choosenButton;
        
        switch (choosenButton)
        {
            case ButtonType.Draw:
                {
                    Enable<Transform>(roadTab.drawRoad);
                    Disable<Transform>(roadTab.drawRoadWhite);
                    break;
                }
            
            case ButtonType.ERP:
                {
                    Enable<Transform>(roadTab.drawERP);
                    Disable<Transform>(roadTab.drawERPWhite);
                    break;
                }
            case ButtonType.TrafficLight:
                {
                    Enable<Transform>(roadTab.drawTraffic);
                    Disable<Transform>(roadTab.drawTrafficWhite);
                    break;
                }
            case ButtonType.Remove:
                {
                    Enable<Transform>(roadTab.removeRoad);
                    Disable<Transform>(roadTab.removeRoadWhite);
                    break;
                }
            case ButtonType.RemoveCar:
                {
                    Enable<Transform>(roadTab.drawRemoveCar);
                    Disable<Transform>(roadTab.drawRemoveCarWhite);
                    break;
                }

            case ButtonType.PlaceHospital:
                {
                    buildingsTab.placeHospitalUI.ChangeTexture("Game/UI/Hospital");
                    break;
                }
            case ButtonType.PlaceOffice:
                {
                    buildingsTab.placeOfficeUI.ChangeTexture("Game/UI/Office");
                    break;
                }
            case ButtonType.PlacePark:
                {
                    buildingsTab.placeParkUI.ChangeTexture("Game/UI/Park");
                    break;
                }
            case ButtonType.PlaceMall:
                {
                    buildingsTab.placeMallUI.ChangeTexture("Game/UI/ShoppingMall");
                    break;
                }
            case ButtonType.PlacePoliceStation:
                {
                    buildingsTab.placePoliceStationUI.ChangeTexture("Game/UI/PoliceStation");
                    break;
                }
            case ButtonType.Latest:
                {
                    buildingsTab.ResetAllTextures();
                    break;
                }
        }

        //Debug.Log("Calling " + _bt + " " + _activeType);
        //DisableAll();

        if (_activeType)
        {
            //if (Input.GetMouseButtonDown(MouseCode.Left))
            //    cameraMovement.SetZoom(ZoomType.In);

            switch (_bt)
            {
                case ButtonType.Draw:
                    {
                        gameManager.RoadPlacementHandler();

                        Disable<Transform>(roadTab.drawRoad);
                        Enable<Transform>(roadTab.drawRoadWhite);

                        GameManager.smallHoverText.text = "Cost: -20";
                        Enable<Transform>(GameManager.smallHoverBox);
                        break;
                    }
                case ButtonType.Remove:
                    {
                        gameManager.RemoveStructureHandler();

                        Disable<Transform>(roadTab.removeRoad);
                        Enable<Transform>(roadTab.removeRoadWhite);

                        Enable<Transform>(GameManager.smallHoverBox);
                        Disable<Transform>(GameManager.bigHoverBox);
                        break;
                    }
                case ButtonType.ERP:
                    {
                        gameManager.ERPHandler();

                        Disable<Transform>(roadTab.drawERP);
                        Enable<Transform>(roadTab.drawERPWhite);

                        Enable<Transform>(GameManager.smallHoverBox);
                        Disable<Transform>(GameManager.bigHoverBox);
                        break;
                    }
                case ButtonType.TrafficLight:
                    {
                        gameManager.TrafficLightHandler();

                        Disable<Transform>(roadTab.drawTraffic);
                        Enable<Transform>(roadTab.drawTrafficWhite);

                        Enable<Transform>(GameManager.smallHoverBox);
                        Disable<Transform>(GameManager.bigHoverBox);
                        break;
                    }
                case ButtonType.RemoveCar:
                    {
                        gameManager.RemoveCarHandler();

                        Disable<Transform>(roadTab.drawRemoveCar);
                        Enable<Transform>(roadTab.drawRemoveCarWhite);

                        GameManager.smallHoverText.text = "Cost: -20";
                        Enable<Transform>(GameManager.smallHoverBox);
                        Disable<Transform>(GameManager.bigHoverBox);
                        break;
                    }

                case ButtonType.PlaceHospital:
                    {
                        gameManager.PlaceDestHospitalHandler();
                        buildingsTab.placeHospitalUI.ChangeTexture("Game/UI/Hospital_Click");

                        Enable<Transform>(GameManager.bigHoverBox);
                        Disable<Transform>(GameManager.smallHoverBox);
                        break;
                    }
                case ButtonType.PlaceOffice:
                    {
                        gameManager.PlaceDestOfficeHandler();
                        buildingsTab.placeOfficeUI.ChangeTexture("Game/UI/Office_Click");

                        Enable<Transform>(GameManager.bigHoverBox);
                        Disable<Transform>(GameManager.smallHoverBox);
                        break;
                    }
                case ButtonType.PlacePark:
                    {
                        gameManager.PlaceDestParkHandler();
                        buildingsTab.placeParkUI.ChangeTexture("Game/UI/Park_Click");

                        Enable<Transform>(GameManager.bigHoverBox);
                        Disable<Transform>(GameManager.smallHoverBox);
                        break;
                    }
                case ButtonType.PlaceMall:
                    {
                        gameManager.PlaceDestMallHandler();
                        buildingsTab.placeMallUI.ChangeTexture("Game/UI/ShoppingMall_Click");

                        Enable<Transform>(GameManager.bigHoverBox);
                        Disable<Transform>(GameManager.smallHoverBox);
                        break;
                    }
                case ButtonType.PlacePoliceStation:
                    {
                        gameManager.PlaceDestPoliceStationHandler();
                        buildingsTab.placePoliceStationUI.ChangeTexture("Game/UI/PoliceStation_Click");

                        Enable<Transform>(GameManager.bigHoverBox);
                        Disable<Transform>(GameManager.smallHoverBox);
                        break;
                    }
            }
            choosenButton = _bt;
            SceneManager.SetDrawMode(true);
        }
        else
        {
            gameManager.ClearInputActions();

            SceneManager.SetDrawMode(false);
            Disable<Transform>(GameManager.bigHoverBox);
            Disable<Transform>(GameManager.smallHoverBox);

            choosenButton = ButtonType.None;
        }

    }

    public void SetToolTips(bool state, Vector2 position, string textToPut = "")
    {
        if (state)
        {
            Enable<Transform>(tooltipTrans);
            tooltipTrans.position = position;
            tooltipText.text = textToPut;
            if (gameState.GetNight())
                tooltipText.color = new Color(1f, 1f, 1f);
            else
                tooltipText.color = new Color(0f, 0f, 0f);

        }
        else Disable<Transform>(tooltipTrans);
    }

    public override void Update()
    {
        if (allowKeyButton)
        {

            if (Input.GetKeyDown(KeyCode.T1))
            {
                buildingsTab.SwitchTabBuildings(true, false);
                BRCallFunction(ButtonType.PlaceHospital);
            }
            if (Input.GetKeyDown(KeyCode.T2))
            {
                buildingsTab.SwitchTabBuildings(true, false);
                BRCallFunction(ButtonType.PlaceOffice);
            }
            if (Input.GetKeyDown(KeyCode.T3))
            {
                buildingsTab.SwitchTabBuildings(true, false);
                BRCallFunction(ButtonType.PlacePark);
            }
            if (Input.GetKeyDown(KeyCode.T4))
            {
                buildingsTab.SwitchTabBuildings(true, false);
                BRCallFunction(ButtonType.PlaceMall);
            }
            if (Input.GetKeyDown(KeyCode.T5))
            {
                buildingsTab.SwitchTabBuildings(true, false);
                BRCallFunction(ButtonType.PlacePoliceStation);
            }


            if (Input.GetKeyDown(KeyCode.Q))
            {
                //roadTab.SwitchTabRoad(true, false);
                BRCallFunction(ButtonType.Remove);
            }

            if (Input.GetKeyDown(KeyCode.E))
            {
                //roadTab.SwitchTabRoad(true, false);
                BRCallFunction(ButtonType.RemoveCar);
            }

            if (Input.GetKeyDown(KeyCode.R))
            {
                roadTab.SwitchTabRoad(true, false);
                BRCallFunction(ButtonType.Draw);
            }
            if (roadTab.revealTrafficButton)
            {
                if (Input.GetKeyDown(KeyCode.T))
                {
                    roadTab.SwitchTabRoad(true, false);
                    BRCallFunction(ButtonType.TrafficLight);
                }
            }
            if (roadTab.revealERPButton)
            {
                if (Input.GetKeyDown(KeyCode.Y))
                {
                    roadTab.SwitchTabRoad(true, false);
                    BRCallFunction(ButtonType.ERP);
                }
            }
        }
    }
}
