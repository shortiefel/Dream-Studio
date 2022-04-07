using System;

//The U behind means its being used = button is white
public enum ButtonType
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
    None
}


public class ButtonRoad : MonoBehaviour
{
    //PlacementManager placementManager;

    //UI buttonUI;
    //bool buttonType;
    //bool activeType;
    //bool drawRoadMode;
    //bool deleteRoadMode;
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

    Transform displayArrow;
    UI displayArrowUI;
    //Transform displayArrowWhite;

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

    //Transform placeHospitalWhite;
    //Transform placeOfficeWhite;
    //Transform placeParkWhite;
    //Transform placeMallWhite;
    //Transform placePoliceStationWhite;

    Text tooltipText;
    Transform tooltipTrans;
    Vector2 toolTipsDisplayPosition;

    Transform lineDivider1;
    Vector2 line1;

    Transform trafficIntro;
    Transform erpIntro;

    GameManager gameManager;
    //InputManager inputManager;

    Transform moneyText;
    //Transform counterText;

    GameState gameState;

    //private Camera mainCamera;

    public bool opening;
    public bool closing;
    float timer;

    float closeXPosition;

    float speedMultiply;

    public bool revealERPButton;
    public bool revealTrafficButton;

    //CameraMovement cameraMovement;

    CombinedUI combinedUI;

    public bool isOn;

    ButtonType choosenButton = ButtonType.None;
    bool displayState = false;
    

    public override void Start()
    {
        combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();

        //Have one more script that is checking if its draw/remove/erp/traffic then when onmouseover and onclick will call the different functions that is stored here to enable or
        //disable the different effect.

        //mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

        //placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        //buttonUI = GetComponent<UI>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        drawRoadWhite = GameObject.Find("DrawRoadWhite").GetComponent<Transform>();
        drawRoad = GameObject.Find("DrawRoad").GetComponent<Transform>();
        roadCount = GameObject.Find("currRoadDisplay").GetComponent<Transform>();
        drawPosition = drawRoad.position;
        drawRoadCount = roadCount.position;

        removeRoad = GameObject.Find("RemoveRoad").GetComponent<Transform>();
        removeRoadWhite = GameObject.Find("RemoveRoadWhite").GetComponent<Transform>();
        removePosition = removeRoad.position;

        drawERP = GameObject.Find("ERPbtn").GetComponent<Transform>();
        drawERPWhite = GameObject.Find("ERPbtnWhite").GetComponent<Transform>();
        ERPCount = GameObject.Find("currERPDisplay").GetComponent<Transform>();
        erpPosition = drawERP.position;
        drawERPCount = ERPCount.position;

        drawTraffic = GameObject.Find("TrafficLight").GetComponent<Transform>();
        drawTrafficWhite = GameObject.Find("TrafficLightWhite").GetComponent<Transform>();
        trafficCount = GameObject.Find("currTrafficDisplay").GetComponent<Transform>();
        trafficPosition = drawTraffic.position;
        drawTrafficCount = trafficCount.position;

        drawRemoveCar = GameObject.Find("RemoveCar").GetComponent<Transform>();
        drawRemoveCarWhite = GameObject.Find("RemoveCarWhite").GetComponent<Transform>();
        //drawRemoveCar = GameObject.Find("RemoveCar").GetComponent<Transform>();
        //drawRemoveCarWhite = GameObject.Find("RemoveCarWhite").GetComponent<Transform>();
        drawRemoveCarPosition = drawRemoveCar.position;

        GameObject displayGO = GameObject.Find("Displaybtn");
        displayArrow = displayGO.GetComponent<Transform>();
        displayArrowUI = displayGO.GetComponent<UI>();
        //displayArrowWhite = GameObject.Find("DisplaybtnWhite").GetComponent<Transform>();

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

        //placeHospitalWhite = GameObject.Find("PlaceHospitalWhite").GetComponent<Transform>();
        //placeOfficeWhite = GameObject.Find("PlaceOfficeWhite").GetComponent<Transform>();
        //placeParkWhite = GameObject.Find("PlaceParkWhite").GetComponent<Transform>();
        //placeMallWhite = GameObject.Find("PlaceMallWhite").GetComponent<Transform>();
        //placePoliceStationWhite = GameObject.Find("PlacePoliceStationWhite").GetComponent<Transform>();

        GameObject stringNameGo = GameObject.Find("stringname");
        tooltipText = stringNameGo.GetComponent<Text>();
        tooltipTrans = stringNameGo.GetComponent<Transform>();
        toolTipsDisplayPosition = transform.position + new Vector2(-2.40f, 7.70f);

        lineDivider1 = GameObject.Find("Line1").GetComponent<Transform>();
        line1 = lineDivider1.position;



        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(drawERPWhite);
        Disable<Transform>(drawTrafficWhite);
        Disable<Transform>(drawRemoveCarWhite);
        Disable<Transform>(roadCount);
        Disable<Transform>(ERPCount);
        Disable<Transform>(trafficCount);

        Disable<Transform>(drawERP);
        Disable<Transform>(drawTraffic);

        //Disable<Transform>(displayArrowWhite);

        //Disable<Transform>(placeHospitalWhite);
        //Disable<Transform>(placeOfficeWhite);
        //Disable<Transform>(placeParkWhite);
        //Disable<Transform>(placeMallWhite);
        //Disable<Transform>(placePoliceStationWhite);


        opening = false;
        closing = false;
        timer = 0f;
        closeXPosition = -96f;
        speedMultiply = 10f;

        drawRoadWhite.position = new Vector2(closeXPosition, drawPosition.y);
        drawRoad.position = new Vector2(closeXPosition, drawPosition.y);
        roadCount.position = new Vector2(closeXPosition, drawPosition.y);

        removeRoad.position = new Vector2(closeXPosition, removePosition.y);
        removeRoadWhite.position = new Vector2(closeXPosition, removePosition.y);

        drawERP.position = new Vector2(closeXPosition, erpPosition.y);
        drawERPWhite.position = new Vector2(closeXPosition, erpPosition.y);
        ERPCount.position = new Vector2(closeXPosition, drawPosition.y);

        drawTraffic.position = new Vector2(closeXPosition, trafficPosition.y);
        drawTrafficWhite.position = new Vector2(closeXPosition, trafficPosition.y);
        trafficCount.position = new Vector2(closeXPosition, drawPosition.y);

        drawRemoveCar.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);

        placeHospital.position = new Vector2(closeXPosition, placeHospitalPos.y);
        placeOffice.position = new Vector2(closeXPosition, placeOfficePos.y);
        placePark.position = new Vector2(closeXPosition, placeParkPos.y);
        placeMall.position = new Vector2(closeXPosition, placeMallPos.y);
        placePoliceStation.position = new Vector2(closeXPosition, placePoliceStationPos.y);

        lineDivider1.position = new Vector2(closeXPosition, line1.y);


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

        isOn = false;
        //GameObject go4 = GameObject.Find("CounterText");
        //if (go4 != null)
        //    counterText = go4.GetComponent<Transform>();


        //cameraMovement = GameObject.Find("Camera").GetComponent<CameraMovement>();

        //drawRoadMode = false;
        //deleteRoadMode = false;

        //activeType = false;
        //
        //if (transform.entityId == GameObject.Find("DrawRoad").GetComponent<Transform>().entityId || 
        //    transform.entityId == GameObject.Find("DrawRoadWhite").GetComponent<Transform>().entityId)
        //{
        //    buttonType = true;
        //
        //}
        //else if (transform.entityId == GameObject.Find("RemoveRoad").GetComponent<Transform>().entityId ||
        //    transform.entityId == GameObject.Find("RemoveRoadWhite").GetComponent<Transform>().entityId)
        //{
        //    buttonType = false;
        //}
        //else if (transform.entityId == GameObject.Find("ERPbtn").GetComponent<Transform>().entityId ||
        //    transform.entityId == GameObject.Find("ERPbtnWhite").GetComponent<Transform>().entityId)
        //{
        //    buttonType = true;
        //
        //}
        //else if (transform.entityId == GameObject.Find("TrafficLight").GetComponent<Transform>().entityId ||
        //  transform.entityId == GameObject.Find("TrafficLightWhite").GetComponent<Transform>().entityId)
        //{
        //    buttonType = true;
        //
        //}
    }

    public override void OnMouseOver()
    {
        SetToolTips(true, toolTipsDisplayPosition, "Display buttons");

        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            SwitchTabRoad(!displayState);
        }
    }

    public override void OnMouseExit()
    {
        SetToolTips(false, Vector2.zero);
    }

    //_activeType = false means u r clicking the white version
    public void SwitchTabRoad(bool type, bool reenable = true)
    {
        if (type)
        {
            opening = true;

            //Disable<Transform>(displayArrow);
            //Enable<Transform>(displayArrowWhite);
            displayArrowUI.ChangeTexture("Game/UI/Arrow_L");

            EnableAllNormalExcept();

            Enable<Transform>(lineDivider1);

            isOn = true;
        }
        else
        {
            ResetAll();

            closing = true;

            //Disable<Transform>(displayArrowWhite);
            //if (reenable)
            //    Enable<Transform>(displayArrow);

            displayArrowUI.ChangeTexture("Game/UI/Arrow_R");
            //if (reenable)
            //{
            //    Debug.Log("Enaalsaksd");
            //    Enable<Transform>(displayArrow);
            //}
            //else
            //{
            //    Debug.Log("Disabling 3231323132131333333333333");
            //    Disable<Transform>(displayArrow);
            //}

            //cameraMovement.SetZoom(ZoomType.Out);
            isOn = false;
        }

        displayState = type;
    }
    private void CloseTabs()
    {
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, closeXPosition, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, closeXPosition, timer), drawPosition.y);
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, closeXPosition, timer), drawRoadCount.y);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, closeXPosition, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, closeXPosition, timer), removePosition.y);

        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, closeXPosition, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, closeXPosition, timer), erpPosition.y);
        ERPCount.position = new Vector2(Mathf.Lerp(ERPCount.position.x, closeXPosition, timer), drawERPCount.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, closeXPosition, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, closeXPosition, timer), trafficPosition.y);
        trafficCount.position = new Vector2(Mathf.Lerp(trafficCount.position.x, closeXPosition, timer), drawTrafficCount.y );

        drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, closeXPosition, timer), drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(Mathf.Lerp(drawRemoveCarWhite.position.x, closeXPosition, timer), drawRemoveCarPosition.y);


        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, closeXPosition, timer), placeHospitalPos.y);
        placeOffice.position = new Vector2(Mathf.Lerp(placeOffice.position.x, closeXPosition, timer), placeOfficePos.y);
        placePark.position = new Vector2(Mathf.Lerp(placePark.position.x, closeXPosition, timer), placeParkPos.y);
        placeMall.position = new Vector2(Mathf.Lerp(placeMall.position.x, closeXPosition, timer), placeMallPos.y);
        placePoliceStation.position = new Vector2(Mathf.Lerp(placePoliceStation.position.x, closeXPosition, timer), placePoliceStationPos.y);


        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, closeXPosition, timer), line1.y);



        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {


            timer = 0f;
            closing = false;
        }
    }

    private void OpenTabs()
    {

        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, drawPosition.x, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, drawPosition.x, timer), drawPosition.y);
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, drawRoadCount.x, timer), drawRoadCount.y);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, removePosition.x, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, removePosition.x, timer), removePosition.y);

        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, erpPosition.x, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, erpPosition.x, timer), erpPosition.y);
        ERPCount.position = new Vector2(Mathf.Lerp(ERPCount.position.x, drawERPCount.x, timer), drawERPCount.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, trafficPosition.x, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, trafficPosition.x, timer), trafficPosition.y);
        trafficCount.position = new Vector2(Mathf.Lerp(trafficCount.position.x, drawTrafficCount.x, timer), drawTrafficCount.y);

        drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);
        drawRemoveCarWhite.position = new Vector2(Mathf.Lerp(drawRemoveCarWhite.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);

        placeHospital.position = new Vector2(Mathf.Lerp(placeHospital.position.x, placeHospitalPos.x, timer), placeHospitalPos.y);
        placeOffice.position = new Vector2(Mathf.Lerp(placeOffice.position.x, placeOfficePos.x, timer), placeOfficePos.y);
        placePark.position = new Vector2(Mathf.Lerp(placePark.position.x, placeParkPos.x, timer), placeParkPos.y);
        placeMall.position = new Vector2(Mathf.Lerp(placeMall.position.x, placeMallPos.x, timer), placeMallPos.y);
        placePoliceStation.position = new Vector2(Mathf.Lerp(placePoliceStation.position.x, placePoliceStationPos.x, timer), placePoliceStationPos.y);

        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, line1.x, timer), line1.y);


        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {


            timer = 0f;
            opening = false;
        }

    }
    public void CallFunction(ButtonType _bt)
    {
        bool _activeType = true;

        if (_bt == choosenButton) _activeType = false;
        if (_bt == ButtonType.Latest) _bt = choosenButton;

        switch (choosenButton)
        {
            case ButtonType.Draw:
                {

                    break;
                }
            case ButtonType.Remove:
                {

                    break;
                }
            case ButtonType.ERP:
                {

                    break;
                }
            case ButtonType.TrafficLight:
                {

                    break;
                }
            case ButtonType.RemoveCar:
                {

                    break;
                }

            case ButtonType.PlaceHospital:
                {
                    placeHospitalUI.ChangeTexture("Game/UI/Hospital");
                    break;
                }
            case ButtonType.PlaceOffice:
                {
                    placeOfficeUI.ChangeTexture("Game/UI/Office");
                    break;
                }
            case ButtonType.PlacePark:
                {
                    placeParkUI.ChangeTexture("Game/UI/Park");
                    break;
                }
            case ButtonType.PlaceMall:
                {
                    placeMallUI.ChangeTexture("Game/UI/ShoppingMall");
                    break;
                }
            case ButtonType.PlacePoliceStation:
                {
                    placePoliceStationUI.ChangeTexture("Game/UI/PoliceStation");
                    break;
                }
        }

        //Debug.Log("Calling " + _bt + " " + _activeType);
        DisableAll();

        if (_activeType)
        {
            //if (Input.GetMouseButtonDown(MouseCode.Left))
            //    cameraMovement.SetZoom(ZoomType.In);

            switch (_bt)
            {
                case ButtonType.Draw:
                    {
                        gameManager.RoadPlacementHandler();
                        Enable<Transform>(drawRoadWhite);

                        EnableAllNormalExcept(ButtonType.Draw);

                        break;
                    }
                case ButtonType.Remove:
                    {
                        gameManager.RemoveStructureHandler();
                        Enable<Transform>(removeRoadWhite);

                        EnableAllNormalExcept(ButtonType.Remove);

                        //Disable<Transform>(removeRoad);
                        break;
                    }
                case ButtonType.ERP:
                    {
                        gameManager.ERPHandler();
                        Enable<Transform>(drawERPWhite);

                        EnableAllNormalExcept(ButtonType.ERP);

                        //Disable<Transform>(drawERP);
                        break;
                    }
                case ButtonType.TrafficLight:
                    {
                        gameManager.TrafficLightHandler();
                        Enable<Transform>(drawTrafficWhite);

                        EnableAllNormalExcept(ButtonType.TrafficLight);

                        //Disable<Transform>(drawTraffic);
                        break;
                    }
                case ButtonType.RemoveCar:
                    {
                        gameManager.RemoveCarHandler();
                        
                        Enable<Transform>(drawRemoveCarWhite);

                        EnableAllNormalExcept(ButtonType.RemoveCar);

                        break;
                    }

                case ButtonType.PlaceHospital:
                    {
                        gameManager.PlaceDestHospitalHandler();
                        placeHospitalUI.ChangeTexture("Game/UI/Hospital_Click");

                        EnableAllNormalExcept();
                        break;
                    }
                case ButtonType.PlaceOffice:
                    {
                        gameManager.PlaceDestOfficeHandler();
                        placeOfficeUI.ChangeTexture("Game/UI/Office_Click");

                        EnableAllNormalExcept();
                        break;
                    }
                case ButtonType.PlacePark:
                    {
                        gameManager.PlaceDestParkHandler();
                        
                        placeParkUI.ChangeTexture("Game/UI/Park_Click");

                        EnableAllNormalExcept();
                        break;
                    }
                case ButtonType.PlaceMall:
                    {
                        gameManager.PlaceDestMallHandler();
                        placeMallUI.ChangeTexture("Game/UI/ShoppingMall_Click");

                        EnableAllNormalExcept();
                        break;
                    }
                case ButtonType.PlacePoliceStation:
                    {
                        gameManager.PlaceDestPoliceStationHandler();
                        placePoliceStationUI.ChangeTexture("Game/UI/PoliceStation_Click");

                        EnableAllNormalExcept();
                        break;
                    }
            }
            
            SceneManager.SetDrawMode(true);
            //gameState.SetDrawMode(true);
            //cameraMovement.drawMode = true;
        }
        else
        {

            SceneManager.SetDrawMode(false);
            //gameState.SetDrawMode(false);

            EnableAllNormalExcept();

            _bt = ButtonType.None;
        }

        
        choosenButton = _bt;
    }


    public override void FixedUpdate()
    {
 
        if (opening)
            OpenTabs();
        if (closing)
            CloseTabs();

        /****Shortcut keys in game***/
        if (Input.GetKeyDown(KeyCode.H)) CallFunction(ButtonType.PlaceHospital);
        if (Input.GetKeyDown(KeyCode.M)) CallFunction(ButtonType.PlaceMall);
        if (Input.GetKeyDown(KeyCode.P)) CallFunction(ButtonType.PlacePark);
        if (Input.GetKeyDown(KeyCode.O)) CallFunction(ButtonType.PlaceOffice);
        if (Input.GetKeyDown(KeyCode.S)) CallFunction(ButtonType.PlacePoliceStation);
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

    public void EnableAllNormalExcept(ButtonType bt = ButtonType.Ignore)
    {
        if (bt != ButtonType.Draw)
            Enable<Transform>(drawRoad);
        if (bt != ButtonType.Remove)
            Enable<Transform>(removeRoad);
        Enable<Transform>(roadCount);

        if (bt != ButtonType.RemoveCar)
            Enable<Transform>(drawRemoveCar);

        if (revealERPButton)
        {
            if (bt != ButtonType.ERP)
                Enable<Transform>(drawERP);
            Enable<Transform>(ERPCount);
        }
        if (revealTrafficButton)
        {
            if (bt != ButtonType.TrafficLight)
                Enable<Transform>(drawTraffic);
            Enable<Transform>(trafficCount);
        }
    }

    public void DisableAllNormal()
    {
        Disable<Transform>(drawRoad);
        Disable<Transform>(removeRoad);
        Disable<Transform>(drawERP);
        Disable<Transform>(drawTraffic);
        Disable<Transform>(drawRemoveCar);
        Disable<Transform>(roadCount);
        Disable<Transform>(ERPCount);
        Disable<Transform>(trafficCount);
    }

    public void EnableAllWhite()
    {
        Enable<Transform>(drawRoadWhite);
        Enable<Transform>(removeRoadWhite);
        Enable<Transform>(drawRemoveCarWhite);

        if (revealERPButton)
        {
            Enable<Transform>(drawERPWhite);
        }
        if (revealTrafficButton)
        {
            Enable<Transform>(drawTrafficWhite);
        }
    }

    public void DisableAllWhite()
    {
        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(drawERPWhite);
        Disable<Transform>(drawTrafficWhite);
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

    public void DisableAll()
    {
        DisableAllNormal();
        DisableAllWhite();

        gameManager.ClearInputActions();

        SceneManager.SetDrawMode(false);
        //gameState.SetDrawMode(false);
        //activeType = false;
    }

    public void RevealERP()
    {
        revealERPButton = true;
        //Enable<Transform>(drawERP);

        Disable<Transform>(moneyText);
        //Disable<Transform>(counterText);
        Disable<Transform>(roadCount);
        Disable<Transform>(trafficCount);

        Enable<Transform>(erpIntro);

        closing = true;

        Time.timeScale = 0f;


        combinedUI.CloseAllUIExcept(UIType.None);

        Disable<Transform>(GameObject.Find("stringname").GetComponent<Transform>());
    }

    public void RevealTraffic()
    {
        revealTrafficButton = true;
        //Enable<Transform>(drawTraffic);

        Disable<Transform>(moneyText);
        //Disable<Transform>(counterText);
        Disable<Transform>(roadCount);
        //Debug.Log("Revealing traffic ");
        Enable<Transform>(trafficIntro);

        closing = true;

        Time.timeScale = 0f;

        combinedUI.CloseAllUIExcept(UIType.None);

        Disable<Transform>(GameObject.Find("stringname").GetComponent<Transform>());
    }

}