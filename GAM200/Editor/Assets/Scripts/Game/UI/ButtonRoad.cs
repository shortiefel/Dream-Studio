using System;

public enum ButtonType
{
    Draw = 0,
    Remove,
    ERP,
    TrafficLight
}

public class ButtonRoad : MonoBehaviour
{
    PlacementManager placementManager;

    UI buttonUI;
    bool buttonType;
    bool activeType;
    //bool drawRoadMode;
    //bool deleteRoadMode;
    Transform drawRoadWhite;
    Transform drawRoad;

    Transform removeRoad;
    Transform removeRoadWhite;

    Transform drawERP;
    Transform drawERPWhite;

    Transform drawTraffic;
    Transform drawTrafficWhite;

    GameManager gameManager;
    //InputManager inputManager;

    GameState gameState;

    private Camera mainCamera;

    

    public override void Start()
    {
        //Have one more script that is checking if its draw/remove/erp/traffic then when onmouseover and onclick will call the different functions that is stored here to enable or
        //disable the different effect.

        mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        buttonUI = GetComponent<UI>();
        gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        drawRoadWhite = GameObject.Find("DrawRoadWhite").GetComponent<Transform>();
        drawRoad = GameObject.Find("DrawRoad").GetComponent<Transform>();
        removeRoad = GameObject.Find("RemoveRoad").GetComponent<Transform>();
        removeRoadWhite = GameObject.Find("RemoveRoadWhite").GetComponent<Transform>();

        drawERP = GameObject.Find("ERPbtn").GetComponent<Transform>();
        drawERPWhite = GameObject.Find("ERPbtnWhite").GetComponent<Transform>();

        drawTraffic = GameObject.Find("TrafficLight").GetComponent<Transform>();
        drawTrafficWhite = GameObject.Find("TrafficLightWhite").GetComponent<Transform>();


        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(drawERPWhite);
        Disable<Transform>(drawTrafficWhite);

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
    public void CallFunction(ButtonType _bt, bool _activeType)
    {
        Debug.Log("Calling " + _bt + " " + _activeType);
        DisableAll();

        if (_activeType)
        {
            switch (_bt)
            {
                case ButtonType.Draw:
                    {
                        gameManager.RoadPlacementHandler();
                        Enable<Transform>(drawRoadWhite);

                        Enable<Transform>(removeRoad);
                        Enable<Transform>(drawERP);
                        Enable<Transform>(drawTraffic);
                        break;
                    }
                case ButtonType.Remove:
                    {
                        gameManager.RemoveRoadHandler();
                        Enable<Transform>(removeRoadWhite);

                        Enable<Transform>(drawRoad);
                        Enable<Transform>(drawERP);
                        Enable<Transform>(drawTraffic);
                        break;
                    }
                case ButtonType.ERP:
                    {
                        gameManager.RemoveRoadHandler();
                        Enable<Transform>(drawERPWhite);

                        Enable<Transform>(drawRoad);
                        Enable<Transform>(removeRoad);
                        Enable<Transform>(drawTraffic);
                        break;
                    }
                case ButtonType.TrafficLight:
                    {
                        gameManager.RemoveRoadHandler();
                        Enable<Transform>(drawTrafficWhite);

                        Enable<Transform>(drawRoad);
                        Enable<Transform>(removeRoad);
                        Enable<Transform>(drawERP);
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

            Enable<Transform>(drawRoad);
            Enable<Transform>(removeRoad);
            Enable<Transform>(drawERP);
            Enable<Transform>(drawTraffic);
        }
    }

    //public override void OnMouseEnter()
    //{
    //    buttonUI.color = new Color(1f, 0f, 0f);
    //}

    public override void Update()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Vector3 mousePos = mainCamera.ScreenToWorldPoint(Input.GetMousePosition());
            Vector2 startPos = placementManager.placementGrid.GetStartPoint();
            Vector2 endPos = placementManager.placementGrid.GetGridSize() + startPos;
            if (mousePos.x < startPos.x - 0.5 || mousePos.x > endPos.x - 0.5 ||
                mousePos.y < startPos.y - 0.5 || mousePos.y > endPos.y - 0.5)
            {
                ResetAll();
            }
        }
    }

    public override void OnMouseOver()
    {
        //if (Input.GetMouseButtonDown(MouseCode.Left))
        //{
        //    if (buttonType)
        //    {
        //        //Show draw road
        //        if (!activeType)
        //        {
        //            Disable<Transform>(drawRoad);
        //            Enable<Transform>(drawRoadWhite);
        //            //drawRoadMode = true;
        //            Disable<Transform>(removeRoadWhite);
        //            Enable<Transform>(removeRoad);
        //            Disable<Transform>(drawERP);
        //            Enable<Transform>(drawERPWhite);
        //            Disable<Transform>(drawTraffic);
        //            Enable<Transform>(drawTrafficWhite);
        //
        //            Enable<Transform>(drawRoadWhite);
        //            gameManager.RoadPlacementHandler();
        //            //SwitchMode();
        //            SceneManager.SetDrawMode(true);
        //            gameState.SetDrawMode(true);
        //            activeType = true;
        //        }
        //        else
        //        {
        //            DisableAll();
        //        }
        //
        //    }
        //
        //    else
        //    {
        //        //Show remove road
        //        if (!activeType)
        //        {
        //            Disable<Transform>(removeRoad);
        //            Enable<Transform>(removeRoadWhite);
        //            //deleteRoadMode = true;
        //            Enable<Transform>(drawRoad);
        //            Disable<Transform>(drawRoadWhite);
        //            Enable<Transform>(drawERP);
        //            Disable<Transform>(drawERPWhite);
        //            Enable<Transform>(drawTraffic);
        //            Disable<Transform>(drawTrafficWhite);
        //
        //            // SwitchMode();
        //            Enable<Transform>(removeRoadWhite);
        //            gameManager.RemoveRoadHandler();
        //
        //            SceneManager.SetDrawMode(true);
        //            gameState.SetDrawMode(true);
        //            activeType = true;
        //        }
        //        else
        //        {
        //            DisableAll();
        //        }
        //
        //    }
        //
        //}
    }

    public void ResetAll()
    {
        Enable<Transform>(drawRoad);
        Disable<Transform>(drawRoadWhite);
        Enable<Transform>(removeRoad);
        Disable<Transform>(removeRoadWhite);
        Enable<Transform>(drawERP);
        Disable<Transform>(drawERPWhite);
        Enable<Transform>(drawTraffic);
        Disable<Transform>(drawTrafficWhite);
        gameManager.ClearInputActions();

        SceneManager.SetDrawMode(false);
        gameState.SetDrawMode(false);
        //activeType = false;
    }

    public void DisableAll()
    {
        Disable<Transform>(drawRoad);
        Disable<Transform>(drawRoadWhite);
        Disable<Transform>(removeRoad);
        Disable<Transform>(removeRoadWhite);
        Disable<Transform>(drawERP);
        Disable<Transform>(drawERPWhite);
        Disable<Transform>(drawTraffic);
        Disable<Transform>(drawTrafficWhite);
        gameManager.ClearInputActions();

        SceneManager.SetDrawMode(false);
        gameState.SetDrawMode(false);
        //activeType = false;
    }

}