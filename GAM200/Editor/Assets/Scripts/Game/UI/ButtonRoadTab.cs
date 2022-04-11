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
    RoadTab,
    BuildingsTab,
    None
}


public class ButtonRoadTab : MonoBehaviour
{
    Transform roadTab;
    UI roadTabUI;

    Transform drawRoadWhite;
    Transform drawRoad;
    Vector2 drawPosition;
    Vector2 drawRoadCount;

    Transform removeRoad;
    Transform removeRoadWhite;
    Vector2 removePosition;

    Transform drawERP;
    Transform drawERPWhite;
    Vector2 erpPosition;
    Vector2 drawERPCount;

    Transform drawTraffic;
    Transform drawTrafficWhite;
    Vector2 trafficPosition;
    Vector2 drawTrafficCount;

    Transform drawRemoveCar;
    Transform drawRemoveCarWhite;
    Vector2 drawRemoveCarPosition;
    Transform removeCarTransform;

    Text tooltipText;
    Transform tooltipTrans;
    Vector2 toolTipsDisplayPosition;

    Transform lineDivider1;
    Vector2 line1;

    Transform trafficIntro;
    Transform erpIntro;
    Transform maintenancefee;
    GameManager gameManager;
    //InputManager inputManager;

    Transform moneyText;
    //Transform counterText;

    GameState gameState;

    static public bool roadTabOpen;
    static public bool roadTabClose;

    float timer;

    float closeXPosition;

    float speedMultiply;

    public bool revealERPButton;
    public bool revealTrafficButton;

    //CameraMovement cameraMovement;

    CombinedUI combinedUI;
    ButtonBuildingsTab buildingsTab;

    //public bool isOn;
    public bool roadTabIsOn;
    public bool buildingsTabIsOn;

    //ButtonType bt;

    public ButtonType choosenButton = ButtonType.None;
    bool displayState = false;


    public override void Start()
    {
        combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();
        buildingsTab = GameObject.Find("DisplayBuildingsBtn").GetComponent<ButtonBuildingsTab>();
        maintenancefee = GameObject.Find("MaintenanceFee").GetComponent<Transform>();


        //Have one more script that is checking if its draw/remove/erp/traffic then when onmouseover and onclick will call the different functions that is stored here to enable or
        //disable the different effect.

        //mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

        //placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        //buttonUI = GetComponent<UI>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        closeXPosition = -96f;
      
        drawRoadWhite = GameObject.Find("DrawRoadWhite").GetComponent<Transform>();
        drawRoad = GameObject.Find("DrawRoad").GetComponent<Transform>();
        drawPosition = drawRoad.position;

        removeRoad = GameObject.Find("RemoveRoad").GetComponent<Transform>();
        removeRoadWhite = GameObject.Find("RemoveRoadWhite").GetComponent<Transform>();
        //removePosition = removeRoad.position;

        drawERP = GameObject.Find("ERPbtn").GetComponent<Transform>();
        drawERPWhite = GameObject.Find("ERPbtnWhite").GetComponent<Transform>();
        erpPosition = drawERP.position;

        drawTraffic = GameObject.Find("TrafficLight").GetComponent<Transform>();
        drawTrafficWhite = GameObject.Find("TrafficLightWhite").GetComponent<Transform>();
        trafficPosition = drawTraffic.position;

        drawRemoveCar = GameObject.Find("RemoveCar").GetComponent<Transform>();
        drawRemoveCarWhite = GameObject.Find("RemoveCarWhite").GetComponent<Transform>();
        removeCarTransform = GameObject.Find("RemoveCarCollider").GetComponent<Transform>();
        //drawRemoveCar = GameObject.Find("RemoveCar").GetComponent<Transform>();
        //drawRemoveCarWhite = GameObject.Find("RemoveCarWhite").GetComponent<Transform>();
        //drawRemoveCarPosition = drawRemoveCar.position;

        GameObject displayRoadTabGO = GameObject.Find("DisplayRoadBtn");
        roadTab = displayRoadTabGO.GetComponent<Transform>();
        roadTabUI = displayRoadTabGO.GetComponent<UI>();

        closeXPosition = -96f;

        //bt = ButtonType.RoadTab;
        drawRoadWhite.position = new Vector2(closeXPosition, drawPosition.y);
        drawRoad.position = new Vector2(closeXPosition, drawPosition.y);

        //removeRoad.position = new Vector2(closeXPosition, removePosition.y);
        //removeRoadWhite.position = new Vector2(closeXPosition, removePosition.y);

        drawERP.position = new Vector2(closeXPosition, erpPosition.y);
        drawERPWhite.position = new Vector2(closeXPosition, erpPosition.y);

        drawTraffic.position = new Vector2(closeXPosition, trafficPosition.y);
        drawTrafficWhite.position = new Vector2(closeXPosition, trafficPosition.y);

        //drawRemoveCar.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);
        //drawRemoveCarWhite.position = new Vector2(closeXPosition, drawRemoveCarPosition.y);



        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(drawERPWhite);
        Disable<Transform>(drawTrafficWhite);
        Disable<Transform>(drawRemoveCarWhite);
        Disable<Transform>(removeCarTransform);

        Disable<Transform>(drawERP);
        Disable<Transform>(drawTraffic);
        
        GameObject stringNameGo = GameObject.Find("stringname");
        tooltipText = stringNameGo.GetComponent<Text>();
        tooltipTrans = stringNameGo.GetComponent<Transform>();
        toolTipsDisplayPosition = transform.position + new Vector2(-4.0f, 7.70f);

        //lineDivider1 = GameObject.Find("Line1").GetComponent<Transform>();
        //line1 = lineDivider1.position;

        roadTabOpen = false;
        roadTabClose = false;

        timer = 0f;
        
        speedMultiply = 10f;

        //lineDivider1.position = new Vector2(closeXPosition, line1.y);


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

        roadTabIsOn = false;
        buildingsTabIsOn = false;

        

    }

    public override void OnMouseOver()
    {
        SetToolTips(true, toolTipsDisplayPosition, "Roads");
        if (Input.GetMouseButtonDown(MouseCode.Left))
            SwitchTabRoad(!displayState);
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
            roadTabOpen = true;
            choosenButton = ButtonType.Latest;

            roadTabUI.ChangeTexture("Game/UI/BuildingRoad_Click");

            //EnableAllNormalExcept();

            //Enable<Transform>(lineDivider1);

            roadTabIsOn = true;
            buildingsTabIsOn = false;
        }
        else
        {
            if(reenable)
            {
                ResetAll();
                choosenButton = ButtonType.None;
            }

            roadTabClose = true;
            

            roadTabUI.ChangeTexture("Game/UI/BuildingRoad");


            //isOn = false;
            roadTabIsOn = false;
            buildingsTabIsOn = false;
        }

        displayState = type;
    }

    private void CloseRoadTabs()
    {
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, closeXPosition, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, closeXPosition, timer), drawPosition.y);

        //removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, closeXPosition, timer), removePosition.y);
        //removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, closeXPosition, timer), removePosition.y);

        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, closeXPosition, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, closeXPosition, timer), erpPosition.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, closeXPosition, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, closeXPosition, timer), trafficPosition.y);

        //drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, closeXPosition, timer), drawRemoveCarPosition.y);
        //drawRemoveCarWhite.position = new Vector2(Mathf.Lerp(drawRemoveCarWhite.position.x, closeXPosition, timer), drawRemoveCarPosition.y);

        //lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, closeXPosition, timer), line1.y);

        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {
            timer = 0f;
            roadTabClose = false;
        }
    }

    private void OpenRoadTabs()
    {

        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, drawPosition.x, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, drawPosition.x, timer), drawPosition.y);

        //removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, removePosition.x, timer), removePosition.y);
        //removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, removePosition.x, timer), removePosition.y);
        
        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, erpPosition.x, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, erpPosition.x, timer), erpPosition.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, trafficPosition.x, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, trafficPosition.x, timer), trafficPosition.y);

        //drawRemoveCar.position = new Vector2(Mathf.Lerp(drawRemoveCar.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);
        //drawRemoveCarWhite.position = new Vector2(Mathf.Lerp(drawRemoveCarWhite.position.x, drawRemoveCarPosition.x, timer), drawRemoveCarPosition.y);

        //lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, line1.x, timer), line1.y);


        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {
            timer = 0f;
            roadTabOpen = false;
        }

    }

    public void CallFunction(ButtonType _bt)
    {
        bool _activeType = true;

        if (_bt == choosenButton) _activeType = false;
        if (_bt == ButtonType.Latest) _bt = choosenButton;

        //switch (choosenButton)
        //{
        //    case ButtonType.Draw:
        //        {

        //            break;
        //        }
        //    case ButtonType.Remove:
        //        {

        //            break;
        //        }
        //    case ButtonType.ERP:
        //        {

        //            break;
        //        }
        //    case ButtonType.TrafficLight:
        //        {

        //            break;
        //        }
        //    case ButtonType.RemoveCar:
        //        {

        //            break;
        //        }
        //}

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
                        Enable<Transform>(removeCarTransform);

                        EnableAllNormalExcept(ButtonType.RemoveCar);

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

        //if (opening)
        //    OpenTabs();
        //if (closing)
        //    CloseTabs();

        if (roadTabOpen)
        {
            //if (bt == ButtonType.RoadTab)
            {
                OpenRoadTabs();
                buildingsTab.SwitchTabBuildings(false);
            }
                
        }

        if (roadTabClose)
        {
            //if (bt == ButtonType.RoadTab)
            
            CloseRoadTabs();
            //CloseBuildingsTabs();
        }
    }

    public void SetToolTips(bool state, Vector2 position, string textToPut = "")
    {
        if (state)
        {
            Enable<Transform>(tooltipTrans);
            tooltipTrans.position = position;
            tooltipText.text = textToPut;
        }
        else 
            Disable<Transform>(tooltipTrans);
    }

    public void EnableAllNormalExcept(ButtonType bt = ButtonType.Ignore)
    {
        if (bt != ButtonType.Draw)
            Enable<Transform>(drawRoad);
        if (bt != ButtonType.Remove)
            Enable<Transform>(removeRoad);
        //Enable<Transform>(roadCount);

        if (bt != ButtonType.RemoveCar)
            Enable<Transform>(drawRemoveCar);

        if (revealERPButton)
        {
            if (bt != ButtonType.ERP)
                Enable<Transform>(drawERP);
            //Enable<Transform>(ERPCount);
        }
        if (revealTrafficButton)
        {
            if (bt != ButtonType.TrafficLight)
                Enable<Transform>(drawTraffic);
            //Enable<Transform>(trafficCount);
        }
    }

    public void DisableAllNormal()
    {
        Disable<Transform>(drawRoad);
        Disable<Transform>(removeRoad);
        Disable<Transform>(drawERP);
        Disable<Transform>(drawTraffic);
        Disable<Transform>(drawRemoveCar);

    }

    public void EnableAllWhite()
    {
        Enable<Transform>(drawRoadWhite);
        Enable<Transform>(removeRoadWhite);
        Enable<Transform>(drawRemoveCarWhite);
        Enable<Transform>(removeCarTransform);

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
        Disable<Transform>(removeCarTransform);
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

        Disable<Transform>(moneyText);
        Enable<Transform>(erpIntro);

        //closing = true; 
        //roadTabClose = true;

        Time.timeScale = 0f;

        combinedUI.CloseAllUIExcept(UIType.None);

        Disable<Transform>(GameObject.Find("stringname").GetComponent<Transform>());
    }

    public void RevealTraffic()
    {
        revealTrafficButton = true;
        //Enable<Transform>(drawTraffic);
        Disable<Transform>(maintenancefee);
        Disable<Transform>(moneyText);
        //Disable<Transform>(counterText);
        //Debug.Log("Revealing traffic ");
        Enable<Transform>(trafficIntro);

        //closing = true;
        //roadTabClose = true;

        Time.timeScale = 0f;

        combinedUI.CloseAllUIExcept(UIType.None);

        Disable<Transform>(GameObject.Find("stringname").GetComponent<Transform>());
    }

    public override void OnMouseEnter()
    {
        InputManager.allowBuilding = false;
    }
}