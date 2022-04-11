using System;
using System.Collections.Generic;

public class Test : MonoBehaviour
{
    static ButtonRoadTab roadTab;
    static ButtonBuildingsTab buildingsTab;

    static public ButtonType choosenButton = ButtonType.None;

    public override void Start()
    {
        roadTab = GameObject.Find("DisplayRoadBtn").GetComponent<ButtonRoadTab>();
        buildingsTab = GameObject.Find("DisplayBuildingsBtn").GetComponent<ButtonBuildingsTab>();
    }

    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.T1))
        {
            buildingsTab.SwitchTabBuildings(true);
            roadTab.SwitchTabRoad(false);
            buildingsTab.CallFunction(ButtonType.PlaceHospital);
        }
        if (Input.GetKeyDown(KeyCode.T2))
        {
            buildingsTab.SwitchTabBuildings(true);
            roadTab.SwitchTabRoad(false);
            buildingsTab.CallFunction(ButtonType.PlaceOffice);
        }
        if (Input.GetKeyDown(KeyCode.T3))
        {
            buildingsTab.SwitchTabBuildings(true);
            roadTab.SwitchTabRoad(false);
            buildingsTab.CallFunction(ButtonType.PlacePark);
        }
        if (Input.GetKeyDown(KeyCode.T4))
        {
            buildingsTab.SwitchTabBuildings(true);
            roadTab.SwitchTabRoad(false);
            buildingsTab.CallFunction(ButtonType.PlaceMall);
        }
        if (Input.GetKeyDown(KeyCode.T5))
        {
            roadTab.SwitchTabRoad(false);
            buildingsTab.SwitchTabBuildings(true);
            buildingsTab.CallFunction(ButtonType.PlacePoliceStation);
        }

        if (Input.GetKeyDown(KeyCode.T6))
        {
            buildingsTab.SwitchTabBuildings(false);
            roadTab.SwitchTabRoad(true);
            //ButtonRoadTab.choosenButton = ButtonType.None;
            //roadTab.SwitchTabRoad(true);
            roadTab.CallFunction(ButtonType.Draw);
        }
        if (Input.GetKeyDown(KeyCode.T7))
        {
         
            roadTab.CallFunction(ButtonType.Draw);
        }
    }

}