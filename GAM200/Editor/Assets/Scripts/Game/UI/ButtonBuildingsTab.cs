using System;

//The U behind means its being used = button is white

public class ButtonBuildingsTab : MonoBehaviour
{

    UI buildingDisplayTab;
    Vector2 displayTabPos;
    Transform buildingTab;

    Transform buildingsTab;
    UI buildingsTabUI;

    Transform placeHospital;
    Transform placeOffice;
    Transform placePark;
    Transform placeMall;
    Transform placePoliceStation;

    public UI placeHospitalUI;
    public UI placeOfficeUI;
    public UI placeParkUI;
    public UI placeMallUI;
    public UI placePoliceStationUI;

    Vector2 placeHospitalPos;
    Vector2 placeOfficePos;
    Vector2 placeParkPos;
    Vector2 placeMallPos;
    Vector2 placePoliceStationPos;

    //Transform placeHospitalWhite;
    //Transform placeOfficeWhite;
    //Transform placeParkWhite;
    //Transform placeMallWhite;
    //Transform placePoliceStationWhite;

    //Text tooltipText;
    //Transform tooltipTrans;
    Vector2 toolTipsDisplayPosition;

    Transform trafficIntro;
    Transform erpIntro;

    GameManager gameManager;
    //InputManager inputManager;

    Transform moneyText;
    //Transform counterText;

    //GameState gameState;

    //private Camera mainCamera;

    private bool buildingsTabOpen;
    private bool buildingsTabClose;

    float timer;

    float closeXPosition;
    float tabXPosition;
    float closetabXPosition;


    float speedMultiply;

    public bool revealERPButton;
    public bool revealTrafficButton;

    //CameraMovement cameraMovement;

    CombinedUI combinedUI;
    ButtonRoadTab roadTab;

    //public bool isOn;
    public bool roadTabIsOn;
    public bool buildingsTabIsOn;

    //static public ButtonType choosenButton = ButtonType.None;
    bool displayState = true;



    public override void Start()
    {
        combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();
        roadTab = GameObject.Find("DisplayRoadBtn").GetComponent<ButtonRoadTab>();

        GameObject displaytabGO = GameObject.Find("DisplayBuildings");
        buildingTab = displaytabGO.GetComponent<Transform>();
        buildingDisplayTab = displaytabGO.GetComponent<UI>();

        displayTabPos = buildingTab.position;
        tabXPosition = -22.10f;
        closetabXPosition = -150f;

        buildingTab.position = new Vector2(closetabXPosition, displayTabPos.y);

        //Have one more script that is checking if its draw/remove/erp/traffic then when onmouseover and onclick will call the different functions that is stored here to enable or
        //disable the different effect.

        //mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

        //placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        //buttonUI = GetComponent<UI>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();
        //gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        //else if (entityId == GameObject.Find("DisplayBuildingsBtn").GetComponent<Transform>().entityId)
        //{
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

        closeXPosition = -96f;


        placeHospital.position = new Vector2(closeXPosition, placeHospitalPos.y);
        placeOffice.position = new Vector2(closeXPosition, placeOfficePos.y);
        placePark.position = new Vector2(closeXPosition, placeParkPos.y);
        placeMall.position = new Vector2(closeXPosition, placeMallPos.y);
        placePoliceStation.position = new Vector2(closeXPosition, placePoliceStationPos.y);
        //}


        //GameObject stringNameGo = GameObject.Find("stringname");
        //tooltipText = stringNameGo.GetComponent<Text>();
        //tooltipTrans = stringNameGo.GetComponent<Transform>();
        toolTipsDisplayPosition = transform.position + new Vector2(-6.8f, 7.70f);


        //Disable<Transform>(displayArrowWhite);

        //Disable<Transform>(placeHospitalWhite);
        //Disable<Transform>(placeOfficeWhite);
        //Disable<Transform>(placeParkWhite);
        //Disable<Transform>(placeMallWhite);
        //Disable<Transform>(placePoliceStationWhite);

        buildingsTabOpen = true;
        buildingsTabClose = false;

        timer = 0f;
        closeXPosition = -96f;
        speedMultiply = 10f;


        revealERPButton = false;
        revealTrafficButton = false;


        GameObject go = GameObject.Find("TrafficIntro");
        if (go != null)
            trafficIntro = go.GetComponent<Transform>();

        GameObject go2 = GameObject.Find("ERPIntro");
        if (go2 != null)
            erpIntro = go2.GetComponent<Transform>();

        if (trafficIntro != null)
            Disable<Transform>(trafficIntro);
        if (erpIntro != null)
            Disable<Transform>(erpIntro);

        GameObject go3 = GameObject.Find("MoneyText");
        if (go3 != null)
            moneyText = go3.GetComponent<Transform>();

        //isOn = false;
        //roadTabIsOn = false;
        //buildingsTabIsOn = true;
        
    }

    public override void OnMouseEnter()
    {
        InputManager.allowBuilding = false;
    }
    public override void OnMouseOver()
    {

        combinedUI.SetToolTips(true, toolTipsDisplayPosition, "Buildings");
        if (Input.GetMouseButtonDown(MouseCode.Left))
            SwitchTabBuildings(!displayState);
    }

    public override void OnMouseExit()
    {
        InputManager.allowBuilding = true;
        combinedUI.SetToolTips(false, Vector2.zero);
    }

    //_activeType = false means u r clicking the white version

    public void SwitchTabBuildings(bool type, bool reenable = true)
    {
        if (type)
        {
            //switch (CombinedUI.choosenButton)
            //{
            //    case ButtonType.PlaceHospital:
            //    case ButtonType.PlaceOffice:
            //    case ButtonType.PlacePark:
            //    case ButtonType.PlaceMall:
            //    case ButtonType.PlacePoliceStation:
            //        CombinedUI.choosenButton = ButtonType.None;
            //        break;
            //}

            buildingsTabOpen = true;
            //choosenButton = ButtonType.Latest;

            buildingsTabUI.ChangeTexture("Game/UI/Buildings_Click");
            //EnableAllNormalExcept();

            roadTabIsOn = false;
            buildingsTabIsOn = true;
        }
        else
        {
            
            

            if (reenable)
            {
                
                ResetAllTextures();

                switch (CombinedUI.choosenButton)
                {
                    case ButtonType.PlaceHospital:
                    case ButtonType.PlaceOffice:
                    case ButtonType.PlacePark:
                    case ButtonType.PlaceMall:
                    case ButtonType.PlacePoliceStation:
                        gameManager.ClearInputActions();
                        //Disable<Transform>(GameManager.bigHoverBox);
                        SceneManager.SetDrawMode(false);
                        CombinedUI.choosenButton = ButtonType.None;
                        break;
                }
            }

            buildingsTabClose = true;

            buildingsTabUI.ChangeTexture("Game/UI/Buildings");
            Disable<Transform>(GameManager.bigHoverBox);

            roadTabIsOn = false;
            buildingsTabIsOn = false;
        }
        displayState = type;
    }


    private void CloseBuildingsTabs()
    {
        buildingTab.position = new Vector2(Mathf.Lerp(buildingTab.position.x, closetabXPosition, timer), displayTabPos.y);
        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, closeXPosition, timer), placeHospitalPos.y);
        placeOffice.position = new Vector2(Mathf.Lerp(placeOffice.position.x, closeXPosition, timer), placeOfficePos.y);
        placePark.position = new Vector2(Mathf.Lerp(placePark.position.x, closeXPosition, timer), placeParkPos.y);
        placeMall.position = new Vector2(Mathf.Lerp(placeMall.position.x, closeXPosition, timer), placeMallPos.y);
        placePoliceStation.position = new Vector2(Mathf.Lerp(placePoliceStation.position.x, closeXPosition, timer), placePoliceStationPos.y);

        timer += speedMultiply * Time.unscaledDeltaTime;
        if (timer >= 1f)
        {
            timer = 0f;
            buildingsTabClose = false;
        }
    }

    private void OpenBuildingsTabs()
    {
        buildingTab.position = new Vector2(Mathf.Lerp(buildingTab.position.x, tabXPosition, timer), displayTabPos.y);
        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, placeHospitalPos.x, timer), placeHospitalPos.y);
        placeOffice.position = new Vector2(Mathf.Lerp(placeOffice.position.x, placeOfficePos.x, timer), placeOfficePos.y);
        placePark.position = new Vector2(Mathf.Lerp(placePark.position.x, placeParkPos.x, timer), placeParkPos.y);
        placeMall.position = new Vector2(Mathf.Lerp(placeMall.position.x, placeMallPos.x, timer), placeMallPos.y);
        placePoliceStation.position = new Vector2(Mathf.Lerp(placePoliceStation.position.x, placePoliceStationPos.x, timer), placePoliceStationPos.y);

        timer += speedMultiply * Time.unscaledDeltaTime;
        if (timer >= 1f)
        {
            timer = 0f;
            buildingsTabOpen = false;
        }

    }
    


    public override void Update()
    {
        if (buildingsTabOpen)
        {
            //if (bt == ButtonType.BuildingsTab)
            {
                OpenBuildingsTabs();
                roadTab.SwitchTabRoad(false, true);
            }
        }
        if (buildingsTabClose)
        {
            //if (bt == ButtonType.BuildingsTab)
            CloseBuildingsTabs();
            //CloseRoadTabs();
        }
    }

    //public override void Update()
    //{
    //    if (buildingsTabIsOn)
    //    {
    //        /****Shortcut keys in game***/
    //        if (Input.GetKeyDown(KeyCode.T1)) CallFunction(ButtonType.PlaceHospital);
    //        if (Input.GetKeyDown(KeyCode.T2)) CallFunction(ButtonType.PlaceOffice);
    //        if (Input.GetKeyDown(KeyCode.T3)) CallFunction(ButtonType.PlacePark);
    //        if (Input.GetKeyDown(KeyCode.T4)) CallFunction(ButtonType.PlaceMall);
    //        if (Input.GetKeyDown(KeyCode.T5)) CallFunction(ButtonType.PlacePoliceStation);
    //    }
    //}

    //public void SetToolTips(bool state, Vector2 position, string textToPut = "")
    //{
    //    if (state)
    //    {
    //        Enable<Transform>(tooltipTrans);
    //        tooltipTrans.position = position;
    //        tooltipText.text = textToPut;
    //        if(gameState.GetNight())
    //            tooltipText.color = new Color(1f, 1f, 1f);
    //        else
    //            tooltipText.color = new Color(0f, 0f, 0f);
    //
    //    }
    //    else Disable<Transform>(tooltipTrans);
    //}

    public void ResetAllTextures()
    {
        placeHospitalUI.ChangeTexture("Game/UI/Hospital");
        placeOfficeUI.ChangeTexture("Game/UI/Office");
        placeParkUI.ChangeTexture("Game/UI/Park");
        placeMallUI.ChangeTexture("Game/UI/ShoppingMall");
        placePoliceStationUI.ChangeTexture("Game/UI/PoliceStation");
    }

    //public void ResetAll()
    //{
    //    gameManager.ClearInputActions();
    //    ResetAllTextures();
    //    Test.choosenButton = ButtonType.None;
    //    SceneManager.SetDrawMode(false);
    //}
    //
    //public void DisableAll()
    //{
    //    gameManager.ClearInputActions();
    //
    //    //Disable<Transform>(placeHospital);
    //    //Disable<Transform>(placeOffice);
    //    //Disable<Transform>(placePark);
    //    //Disable<Transform>(placeMall);
    //    //Disable<Transform>(placePoliceStation);
    //
    //    SceneManager.SetDrawMode(false);
    //    //gameState.SetDrawMode(false);
    //    //activeType = false;
    //}

    //public void RevealERP()
    //{
    //    revealERPButton = true;

    //    Disable<Transform>(moneyText);
    //    Enable<Transform>(erpIntro);

    //    buildingsTabClose = true;

    //    Time.timeScale = 0f;

    //    combinedUI.CloseAllUIExcept(UIType.None);

    //    Disable<Transform>(GameObject.Find("stringname").GetComponent<Transform>());
    //}

    //public void RevealTraffic()
    //{
    //    revealTrafficButton = true;
    //    //Enable<Transform>(drawTraffic);

    //    Disable<Transform>(moneyText);
    //    //Disable<Transform>(counterText);
    //    //Debug.Log("Revealing traffic ");
    //    Enable<Transform>(trafficIntro);

    //    buildingsTabClose = true;

    //    Time.timeScale = 0f;

    //    combinedUI.CloseAllUIExcept(UIType.None);

    //    Disable<Transform>(GameObject.Find("stringname").GetComponent<Transform>());
    //}

    

}