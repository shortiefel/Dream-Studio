using System;
using System.Collections;
using System.Collections.Generic;

public class GameManager : MonoBehaviour
{
    //public CameraMovement cameraMovement;
    public RoadManager roadManager;
    public InputManager inputManager;

    //public UIController uiController;

    public StructureManager structureManager;
    public KeysController keysController;

    static public Transform smallHoverBox;
    static public Text smallHoverText;
    static public Transform bigHoverBox;
    static public Text bigHoverText;

    //private void Start()
    public override void Start()
    {
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();
        inputManager = GameObject.Find("InputManager").GetComponent<InputManager>();
        structureManager = GameObject.Find("StructureManager").GetComponent<StructureManager>();
        keysController = GameObject.Find("KeysController").GetComponent<KeysController>();

        //inputManager.OnMouseClick += roadManager.PlaceRoad;
        //inputManager.OnMouseHold += roadManager.PlaceRoad;
        //inputManager.OnMouseUp += roadManager.FinishPlacingRoad;

        keysController.OnRoadPlacement += RoadPlacementHandler;
        //keysController.OnHousePlacement += HousePlacementHandler;
        //keysController.OnSpecialPlacement += SpecialPlacementHandler;
        GameObject shGO = GameObject.Find("SmallHoverBox");
        smallHoverBox = shGO.GetComponent<Transform>();
        smallHoverText = shGO.GetComponent<Text>();
        GameObject bhGO = GameObject.Find("BigHoverBox");
        bigHoverBox = bhGO.GetComponent<Transform>();
        bigHoverText = bhGO.GetComponent<Text>();

        Disable<Transform>(smallHoverBox);
        Disable<Transform>(bigHoverBox);
    }

    //private void SpecialPlacementHandler()
    //{
    //    Debug.Log("Call Special");

    //    ClearInputActions();
    //    inputManager.OnMouseClick += structureManager.PlaceSpecial;
    //}


    //// place notification icon here
    //private void HousePlacementHandler()
    //{
    //    Debug.Log("call place house");

    //    ClearInputActions();
    //    inputManager.OnMouseClick += structureManager.PlaceHouse;
    //    //StartCoroutine(waitABit(new Vector2Int(structureManager.PlaceHouse.x, structureManager.PlaceHouse.y)));
    //}

    internal void RoadPlacementHandler()
    {
        //Debug.Log("Call Road");
        ClearInputActions();

        roadManager.ClearTemporaryRoad();
        inputManager.OnMouseClick += roadManager.PlaceRoad;
        inputManager.OnMouseHold += roadManager.PlaceRoad;
        inputManager.OnMouseUp += roadManager.FinishPlacingRoad;
        inputManager.OnMouseHover += HoverSmallIcon;
    }

    internal void RemoveStructureHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += RemoveStructure;
        //inputManager.OnMouseHold += RemoveStructure;
        inputManager.OnMouseUp += roadManager.FinishRemovingRoad;
        inputManager.OnMouseHover += HoverSmallIcon;
    }

    internal void RemoveStructure(Vector2Int pos)
    {
        roadManager.RemoveRoad(pos);
        structureManager.RemoveDestination(pos);
    }

    internal void ERPHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += roadManager.PlaceERP;
        inputManager.OnMouseHover += HoverSmallIcon;
        //inputManager.OnMouseHold += roadManager.PlaceRoad;
        //inputManager.OnMouseUp += roadManager.FinishPlacingRoad;
    }

    internal void TrafficLightHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += roadManager.PlaceTrafficLight;
        inputManager.OnMouseHover += HoverSmallIcon;
        //inputManager.OnMouseHold += roadManager.RemoveRoad;
        //inputManager.OnMouseUp += roadManager.FinishRemovingRoad;
    }

    internal void RemoveCarHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += roadManager.RemoveCarClick;
        inputManager.OnMouseHover += roadManager.RemoveCarHover;
    
        //inputManager.OnMouseHold += roadManager.RemoveRoad;
        //inputManager.OnMouseUp += roadManager.FinishRemovingRoad;
    }

    public void HoverSmallIcon(Vector2Int position)
    {
        if (!roadManager.placementManager.CheckIfPositionInBound(position)) return;
        smallHoverBox.position = position;

        switch (ButtonRoadTab.choosenButton)
        {
            case ButtonType.Remove:
                {
                    BuildingType bt;
                    if (roadManager.trafficLightManager.IsTrafficLight(position))
                    {
                        smallHoverText.text = "Cost: +" + (MoneySystem.tlCost / 4f);
                    }
                    
                    else if (roadManager.erpManager.IsERP(position))
                    {
                        smallHoverText.text = "Cost: +" + (MoneySystem.erpCost / 4f);
                    }
                    else if ((bt = structureManager.RequestRemovingDestination(position)) != BuildingType.None)
                    {
                        smallHoverText.text = "Cost: +" + (MoneySystem.GetCostOfDest(bt) / 10f);
                    }

                    else if (roadManager.placementManager.placementGrid.IsPosRoad(position))
                    {
                        smallHoverText.text = "Cost: +10";
                    }

                    else
                    {
                        smallHoverText.text = "Cost: 0";
                    }
                    break;
                }
            case ButtonType.ERP:
                {
                    smallHoverText.text = "Cost: -" + MoneySystem.erpCost.ToString();
                    break;
                }
            case ButtonType.TrafficLight:
                {
                    //Debug.Log(MoneySystem.tlCost);
                    smallHoverText.text = "Cost: -" + MoneySystem.tlCost.ToString();
                    break;
                }
        }

    }

    internal void PlaceDestHospitalHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestHospital;
        inputManager.OnMouseHover += HoverBigIcon;
    }

    internal void PlaceDestOfficeHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestOffice;
        inputManager.OnMouseHover += HoverBigIcon;
    }

    internal void PlaceDestParkHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestPark;
        inputManager.OnMouseHover += HoverBigIcon;
    }

    internal void PlaceDestMallHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestMall;
        inputManager.OnMouseHover += HoverBigIcon;
    }

    internal void PlaceDestPoliceStationHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestPoliceStation;
        inputManager.OnMouseHover += HoverBigIcon;
    }

    public void HoverBigIcon(Vector2Int position)
    {
        bigHoverBox.position = position + new Vector2(0.5f, 0.5f);

        switch (ButtonBuildingsTab.choosenButton)
        {
            case ButtonType.PlaceHospital:
                {
                    bigHoverText.text = "Cost: -" + MoneySystem.hospitalCost.ToString();
                    break;
                }
            case ButtonType.PlaceOffice:
                {
                    bigHoverText.text = "Cost: -" + MoneySystem.officeCost.ToString();
                    break;
                }
            case ButtonType.PlacePark:
                {
                    bigHoverText.text = "Cost: -" + MoneySystem.parkCost.ToString();
                    break;
                }
            case ButtonType.PlaceMall:
                {
                    bigHoverText.text = "Cost: -" + MoneySystem.shoppingmallCost.ToString();
                    break;
                }
            case ButtonType.PlacePoliceStation:
                {
                    bigHoverText.text = "Cost: -" + MoneySystem.policestationCost.ToString();
                    break;
                }
        }
    }

    internal void ClearInputActions()
    {
        inputManager.OnMouseClick = null;
        inputManager.OnMouseHold = null;
        inputManager.OnMouseUp = null;
        inputManager.OnMouseHover = null;
    }

    //private void Update()
    //public override void Update()
    //{
    //    //cameraMovement.MoveCamera(new Vector2(inputManager.CameraMovementVector.x, inputManager.CameraMovementVector.y));
    //    
    //}

    
}