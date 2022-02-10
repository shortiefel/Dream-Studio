using System;

public enum ButtonType
{
    Draw = 0,
    Remove,
    ERP,
    TrafficLight,
    Display
}

public class ButtonRoad : MonoBehaviour
{
    //PlacementManager placementManager;

    UI buttonUI;
    bool buttonType;
    bool activeType;
    //bool drawRoadMode;
    //bool deleteRoadMode;
    Transform drawRoadWhite;
    Transform drawRoad;
    Vector2 drawPosition;

    Transform removeRoad;
    Transform removeRoadWhite;
    Vector2 removePosition;

    Transform drawERP;
    Transform drawERPWhite;
    Vector2 erpPosition;

    Transform drawTraffic;
    Transform drawTrafficWhite;
    Vector2 trafficPosition;

    Transform displayArrow;
    Transform displayArrowWhite;

    Transform lineDivider1;
    Vector2 line1;
  

    GameManager gameManager;
    //InputManager inputManager;

    GameState gameState;

    private Camera mainCamera;


    public bool opening;
    public bool closing;
    float timer;

    float closeXPosition;

    float speedMultiply;

    public bool additionalButton;

    public override void Start()
    {
        //Have one more script that is checking if its draw/remove/erp/traffic then when onmouseover and onclick will call the different functions that is stored here to enable or
        //disable the different effect.

        mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

        //placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        buttonUI = GetComponent<UI>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

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

        displayArrow = GameObject.Find("Displaybtn").GetComponent<Transform>();
        displayArrowWhite = GameObject.Find("DisplaybtnWhite").GetComponent<Transform>();

        lineDivider1 = GameObject.Find("Line1").GetComponent<Transform>();
        line1 = lineDivider1.position;
   




        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(drawERPWhite);
        Disable<Transform>(drawTrafficWhite);

        Disable<Transform>(drawERP);
        Disable<Transform>(drawTraffic);

        Disable<Transform>(displayArrowWhite);

        opening = false;
        closing = false;
        timer = 0f;
        closeXPosition = -96f;
        speedMultiply = 5f;

        drawRoadWhite.position = new Vector2(closeXPosition, drawPosition.y);
        drawRoad.position = new Vector2(closeXPosition, drawPosition.y);

        removeRoad.position = new Vector2(closeXPosition, removePosition.y);
        removeRoadWhite.position = new Vector2(closeXPosition, removePosition.y);

        drawERP.position = new Vector2(closeXPosition, erpPosition.y);
        drawERPWhite.position = new Vector2(closeXPosition, erpPosition.y);

        drawTraffic.position = new Vector2(closeXPosition, trafficPosition.y);
        drawTrafficWhite.position = new Vector2(closeXPosition, trafficPosition.y);


        lineDivider1.position = new Vector2(closeXPosition, line1.y);
   

        additionalButton = false;


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
    public void SwitchTab(bool type)
    {
        if (type)
        {
            opening = true;

            Disable<Transform>(displayArrow);
            Enable<Transform>(displayArrowWhite);


            EnableAllNormal();

            Enable<Transform>(lineDivider1);
      

        }
        else
        {
            ResetAll();

            closing = true;

            Disable<Transform>(displayArrowWhite);
            Enable<Transform>(displayArrow);
        }
    }
    private void CloseTabs()
    {
        drawRoad.position = new Vector2(Mathf.Lerp(drawRoad.position.x, closeXPosition, timer), drawPosition.y);
        drawRoadWhite.position = new Vector2(Mathf.Lerp(drawRoadWhite.position.x, closeXPosition, timer), drawPosition.y);

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, closeXPosition, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, closeXPosition, timer), removePosition.y);

        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, closeXPosition, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, closeXPosition, timer), erpPosition.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, closeXPosition, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, closeXPosition, timer), trafficPosition.y);

        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, closeXPosition, timer), line1.y);
      


        timer += speedMultiply * Time.deltaTime;
        if (timer > 0.8f)
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

        removeRoad.position = new Vector2(Mathf.Lerp(removeRoad.position.x, removePosition.x, timer), removePosition.y);
        removeRoadWhite.position = new Vector2(Mathf.Lerp(removeRoadWhite.position.x, removePosition.x, timer), removePosition.y);

        drawERP.position = new Vector2(Mathf.Lerp(drawERP.position.x, erpPosition.x, timer), erpPosition.y);
        drawERPWhite.position = new Vector2(Mathf.Lerp(drawERPWhite.position.x, erpPosition.x, timer), erpPosition.y);

        drawTraffic.position = new Vector2(Mathf.Lerp(drawTraffic.position.x, trafficPosition.x, timer), trafficPosition.y);
        drawTrafficWhite.position = new Vector2(Mathf.Lerp(drawTrafficWhite.position.x, trafficPosition.x, timer), trafficPosition.y);

        lineDivider1.position = new Vector2(Mathf.Lerp(lineDivider1.position.x, line1.x, timer), line1.y);
     

        timer += speedMultiply * Time.deltaTime;
        if (timer > 0.8f)
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
            switch (_bt)
            {
                case ButtonType.Draw:
                    {
                        gameManager.RoadPlacementHandler();
                        Enable<Transform>(drawRoadWhite);

                        EnableAllNormal();

                        Disable<Transform>(drawRoad);
                        break;
                    }
                case ButtonType.Remove:
                    {
                        gameManager.RemoveRoadHandler();
                        Enable<Transform>(removeRoadWhite);

                        EnableAllNormal();

                        Disable<Transform>(removeRoad);
                        break;
                    }
                case ButtonType.ERP:
                    {
                        gameManager.ERPHandler();
                        Enable<Transform>(drawERPWhite);

                        EnableAllNormal();

                        Disable<Transform>(drawERP);
                        break;
                    }
                case ButtonType.TrafficLight:
                    {
                        gameManager.TrafficLightHandler();
                        Enable<Transform>(drawTrafficWhite);

                        EnableAllNormal();

                        Disable<Transform>(drawTraffic);
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

    //public override void OnMouseEnter()
    //{
    //    buttonUI.color = new Color(1f, 0f, 0f);
    //}

    public override void Update()
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

    public void EnableAllNormal()
    {
        Enable<Transform>(drawRoad);
        Enable<Transform>(removeRoad);

        if (additionalButton)
        {
            Enable<Transform>(drawERP);
            Enable<Transform>(drawTraffic);
        }
    }

    public void DisableAllNormal()
    {
        Disable<Transform>(drawRoad);
        Disable<Transform>(removeRoad);
        Disable<Transform>(drawERP);
        Disable<Transform>(drawTraffic);
    }

    public void EnableAllWhite()
    {
        Enable<Transform>(drawRoadWhite);
        Enable<Transform>(removeRoadWhite);
        if (additionalButton)
        {
            Enable<Transform>(drawERPWhite);
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

    public void RevealAdditional()
    {
        additionalButton = true;
        Enable<Transform>(drawERP);
        Enable<Transform>(drawTraffic);
    }

}