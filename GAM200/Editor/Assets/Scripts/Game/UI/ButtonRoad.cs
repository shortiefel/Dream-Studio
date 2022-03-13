using System;

//The U behind means its being used = button is white
public enum ButtonType
{
    Draw = 0,
    Remove,
    ERP,
    TrafficLight,
    Display,
    Ignore
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

    Transform displayArrow;
    Transform displayArrowWhite;

    Transform lineDivider1;
    Vector2 line1;

    Transform trafficIntro;
    Transform erpIntro;

    GameManager gameManager;
    //InputManager inputManager;

    Transform moneyText;
    //Transform counterText;

    GameState gameState;

    private Camera mainCamera;

    public bool opening;
    public bool closing;
    float timer;

    float closeXPosition;

    float speedMultiply;

    public bool revealERPButton;
    public bool revealTrafficButton;

    CameraMovement cameraMovement;

    CombinedUI combinedUI;

    public override void Start()
    {
        combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();

        //Have one more script that is checking if its draw/remove/erp/traffic then when onmouseover and onclick will call the different functions that is stored here to enable or
        //disable the different effect.

        mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

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

        displayArrow = GameObject.Find("Displaybtn").GetComponent<Transform>();
        displayArrowWhite = GameObject.Find("DisplaybtnWhite").GetComponent<Transform>();

        lineDivider1 = GameObject.Find("Line1").GetComponent<Transform>();
        line1 = lineDivider1.position;



        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(drawERPWhite);
        Disable<Transform>(drawTrafficWhite);
        Disable<Transform>(roadCount);
        Disable<Transform>(ERPCount);
        Disable<Transform>(trafficCount);

        Disable<Transform>(drawERP);
        Disable<Transform>(drawTraffic);

        Disable<Transform>(displayArrowWhite);

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

        //GameObject go4 = GameObject.Find("CounterText");
        //if (go4 != null)
        //    counterText = go4.GetComponent<Transform>();


        cameraMovement = GameObject.Find("Camera").GetComponent<CameraMovement>();

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

    //_activeType = false means u r clicking the white version
    public void SwitchTabRoad(bool type, bool reenable = true)
    {
        if (type)
        {
            opening = true;

            Disable<Transform>(displayArrow);
            Enable<Transform>(displayArrowWhite);


            EnableAllNormalExcept();

            Enable<Transform>(lineDivider1);
        }
        else
        {
            ResetAll();

            closing = true;

            Disable<Transform>(displayArrowWhite);
            if (reenable)
                Enable<Transform>(displayArrow);

            cameraMovement.SetZoom(ZoomType.Out);
        }
    }
    private void CloseTabs()
    {
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, closeXPosition, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, closeXPosition, timer), drawPosition.y);
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, closeXPosition, timer), drawRoadCount.y + 2.0f);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, closeXPosition, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, closeXPosition, timer), removePosition.y);

        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, closeXPosition, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, closeXPosition, timer), erpPosition.y);
        ERPCount.position = new Vector2(Mathf.Lerp(ERPCount.position.x, closeXPosition, timer), drawERPCount.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, closeXPosition, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, closeXPosition, timer), trafficPosition.y);
        trafficCount.position = new Vector2(Mathf.Lerp(trafficCount.position.x, closeXPosition, timer), drawTrafficCount.y );

        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, closeXPosition, timer), line1.y);



        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {
            //Disable<Transform>(displayArrowWhite);
            //Enable<Transform>(displayArrow);

            timer = 0f;
            closing = false;
        }
    }

    private void OpenTabs()
    {

        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, drawPosition.x, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, drawPosition.x, timer), drawPosition.y);
        roadCount.position = new Vector2(Mathf.Lerp(roadCount.position.x, drawRoadCount.x, timer), drawRoadCount.y + 2.0f);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, removePosition.x, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, removePosition.x, timer), removePosition.y);

        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, erpPosition.x, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, erpPosition.x, timer), erpPosition.y);
        ERPCount.position = new Vector2(Mathf.Lerp(ERPCount.position.x, drawERPCount.x, timer), drawERPCount.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, trafficPosition.x, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, trafficPosition.x, timer), trafficPosition.y);
        trafficCount.position = new Vector2(Mathf.Lerp(trafficCount.position.x, drawTrafficCount.x, timer), drawTrafficCount.y);

        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, line1.x, timer), line1.y);


        timer += speedMultiply * Time.fixedDeltaTime;
        if (timer >= 1f)
        {
            //Disable<Transform>(displayArrow);
            //Enable<Transform>(displayArrowWhite);

            timer = 0f;
            opening = false;
        }

    }
    public void CallFunction(ButtonType _bt, bool _activeType)
    {
        
        //Debug.Log("Calling " + _bt + " " + _activeType);
        DisableAll();

        if (_activeType)
        {
            if (Input.GetMouseButtonDown(MouseCode.Left))
                cameraMovement.SetZoom(ZoomType.In);

            switch (_bt)
            {
                case ButtonType.Draw:
                    {
                        gameManager.RoadPlacementHandler();
                        Enable<Transform>(drawRoadWhite);

                        EnableAllNormalExcept(ButtonType.Draw);
                        //Disable<Transform>(drawRoad);


                        //Enable<Transform>(removeRoad);
                        //Enable<Transform>(roadCount);
                        //
                        //if (revealERPButton)
                        //{
                        //    Enable<Transform>(drawERP);
                        //    Enable<Transform>(ERPCount);
                        //}
                        //if (revealTrafficButton)
                        //{
                        //    Enable<Transform>(drawTraffic);
                        //    Enable<Transform>(trafficCount);
                        //}

                        
                        break;
                    }
                case ButtonType.Remove:
                    {
                        gameManager.RemoveRoadHandler();
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
            }

            SceneManager.SetDrawMode(true);
            gameState.SetDrawMode(true);
            cameraMovement.drawMode = true;
        }
        else
        {
            cameraMovement.SetZoom(ZoomType.Out);

            SceneManager.SetDrawMode(false);
            gameState.SetDrawMode(false);

            EnableAllNormalExcept();
        }
    }

    //public override void OnMouseEnter()
    //{
    //    buttonUI.color = new Color(1f, 0f, 0f);
    //}

    public override void FixedUpdate()
    {
        //if (Input.GetMouseButtonDown(MouseCode.Left))
        //{
        //    Vector3 mousePos = mainCamera.ScreenToWorldPoint(Input.GetMousePosition());
        //    Vector2 startPos = placementManager.placementGrid.GetStartPoint();
        //    Vector2 endPos = placementManager.placementGrid.GetGridSize() + startPos;
        //    if (mousePos.x < startPos.x - 0.5 || mousePos.x > endPos.x - 0.5 ||
        //        mousePos.y < startPos.y - 0.5 || mousePos.y > endPos.y - 0.5)
        //    {
        //        ResetAll();
        //    }
        //}
        if (opening)
            OpenTabs();
        if (closing)
            CloseTabs();
    }

    public void EnableAllNormalExcept(ButtonType bt = ButtonType.Ignore)
    {
        if (bt != ButtonType.Draw)
            Enable<Transform>(drawRoad);
        if (bt != ButtonType.Remove)
            Enable<Transform>(removeRoad);
        Enable<Transform>(roadCount);

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
        Disable<Transform>(roadCount);
        Disable<Transform>(ERPCount);
        Disable<Transform>(trafficCount);
    }

    public void EnableAllWhite()
    {
        Enable<Transform>(drawRoadWhite);
        Enable<Transform>(removeRoadWhite);

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
    }


    public void ResetAll()
    {
        EnableAllNormalExcept();
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

    public void RevealERP()
    {
        revealERPButton = true;
        Enable<Transform>(drawERP);

        Disable<Transform>(moneyText);
        //Disable<Transform>(counterText);
        Disable<Transform>(roadCount);
        Disable<Transform>(trafficCount);

        Enable<Transform>(erpIntro);

        closing = true;

        Time.timeScale = 0f;

        //Disable<Transform>(displayArrowWhite);
        //Disable<Transform>(displayArrow);
        combinedUI.CloseAllUIExcept(UIType.None);

        Disable<Transform>(GameObject.Find("stringname").GetComponent<Transform>());
    }

    public void RevealTraffic()
    {
        revealTrafficButton = true;
        Enable<Transform>(drawTraffic);

        Disable<Transform>(moneyText);
        //Disable<Transform>(counterText);
        Disable<Transform>(roadCount);
        Debug.Log("Revealing traffic ");
        Enable<Transform>(trafficIntro);

        closing = true;

        Time.timeScale = 0f;

        //Disable<Transform>(displayArrowWhite);
        //Disable<Transform>(displayArrow);
        combinedUI.CloseAllUIExcept(UIType.None);

        Disable<Transform>(GameObject.Find("stringname").GetComponent<Transform>());
    }

}