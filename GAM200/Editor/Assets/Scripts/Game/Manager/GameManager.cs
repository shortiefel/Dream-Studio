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
    }

    internal void RemoveStructureHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += RemoveStructure;
        inputManager.OnMouseHold += RemoveStructure;
        inputManager.OnMouseUp += roadManager.FinishRemovingRoad;
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
        //inputManager.OnMouseHold += roadManager.PlaceRoad;
        //inputManager.OnMouseUp += roadManager.FinishPlacingRoad;
    }

    internal void TrafficLightHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += roadManager.PlaceTrafficLight;
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

    internal void PlaceDestHospitalHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestHospital;
    }

    internal void PlaceDestOfficeHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestOffice;
    }

    internal void PlaceDestParkHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestPark;
    }

    internal void PlaceDestMallHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestMall;
    }

    internal void PlaceDestPoliceStationHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceDestPoliceStation;
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