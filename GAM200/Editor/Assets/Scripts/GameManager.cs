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

    //private void Start()
    public override void Start()
    {
        //uiController.OnRoadPlacement += RoadPlacementHandler;
        //uiController.OnHousePlacement += HousePlacementHandler;
        //uiController.OnSpecialPlacement += SpecialPlacementHandler;

        Debug.Log("Start function");

        roadManager = GetComponent<RoadManager>();
        inputManager = GetComponent<InputManager>();
        structureManager = GetComponent<StructureManager>();

        inputManager.OnMouseClick += roadManager.PlaceRoad;
        inputManager.OnMouseHold += roadManager.PlaceRoad;
        inputManager.OnMouseUp += roadManager.FinishPlacingRoad;

    }

    private void SpecialPlacementHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceSpecial;
    }


    // place notification icon here
    private void HousePlacementHandler()
    {
        ClearInputActions();
        inputManager.OnMouseClick += structureManager.PlaceHouse;
        //StartCoroutine(waitABit(new Vector2Int(structureManager.PlaceHouse.x, structureManager.PlaceHouse.y)));
        Debug.Log("call place house");
    }


    private void RoadPlacementHandler()
    {
        ClearInputActions();

        inputManager.OnMouseClick += roadManager.PlaceRoad;
        inputManager.OnMouseHold += roadManager.PlaceRoad;
        inputManager.OnMouseUp += roadManager.FinishPlacingRoad;
    }

    private void ClearInputActions()
    {
        inputManager.OnMouseClick = null;
        inputManager.OnMouseHold = null;
        inputManager.OnMouseUp = null;
    }

    //private void Update()
    public override void Update()
    {
        //cameraMovement.MoveCamera(new Vector2(inputManager.CameraMovementVector.x, inputManager.CameraMovementVector.y));
    }
}