
public enum UIType
{
    Pause = 0,
    Time,
    Store,
    Road, //Bottom left button that build road and stuff
    None
}
public class CombinedUI : MonoBehaviour
{
 
    PauseMenu pauseMenu;
    TimeSystem timeSystem;
    //ButtonStore buttonStore;
    public ButtonRoadTab roadTab;
    public ButtonBuildingsTab buildingsTab;

    Transform pauseIcon;
    Transform timerButton;
    Transform roadTabTransform;
    Transform buildingsTabTransform;

    Transform moneyText;
    Transform coinSymbol;
    Transform dayClock;
    Transform dayTimer;
    Transform maintenancefee;
    Transform maintenanceIcon;
    Transform ampm;
    Transform listOfCostText;
    UI listOfCostDestUI;

    bool isRoadTabOpen;
    bool isBuildingsTabOpen;
    bool isClockOpen;

    public override void Start()
    {
        pauseMenu = GameObject.Find("PauseIcon").GetComponent<PauseMenu>();
        timeSystem = GameObject.Find("TimerIcon").GetComponent<TimeSystem>();
        roadTab = GameObject.Find("DisplayRoadBtn").GetComponent<ButtonRoadTab>();
        buildingsTab = GameObject.Find("DisplayBuildingsBtn").GetComponent<ButtonBuildingsTab>();

        pauseIcon = GameObject.Find("PauseIcon").GetComponent<Transform>();
        timerButton = GameObject.Find("TimerIcon").GetComponent<Transform>();
        roadTabTransform = GameObject.Find("DisplayRoadBtn").GetComponent<Transform>();
        buildingsTabTransform = GameObject.Find("DisplayBuildingsBtn").GetComponent<Transform>();


        moneyText = GameObject.Find("MoneyText").GetComponent<Transform>();
        coinSymbol = GameObject.Find("CoinBag").GetComponent<Transform>();
        dayClock = GameObject.Find("DayClock").GetComponent<Transform>();
        dayTimer = GameObject.Find("Clock").GetComponent<Transform>();
        ampm = GameObject.Find("AMPM").GetComponent<Transform>();
        maintenancefee = GameObject.Find("MaintenanceFee").GetComponent<Transform>();
        maintenanceIcon = GameObject.Find("MaintenanceIcon").GetComponent<Transform>();

        listOfCostText = GameObject.Find("ListOfCostText").GetComponent<Transform>();
        listOfCostDestUI = GameObject.Find("ListOfCostDest").GetComponent<UI>();

        isRoadTabOpen = false;
        isBuildingsTabOpen = false;
        isClockOpen = false;
    }

    public void CloseAllUIExcept(UIType uitype)
    {
        if (roadTab.roadTabIsOn) isRoadTabOpen = true;
        else isRoadTabOpen = false;
        if (buildingsTab.buildingsTabIsOn) isBuildingsTabOpen = true;
        else isBuildingsTabOpen = false;

        if (timeSystem.isOn) isClockOpen = true;
        else isClockOpen = false;

        switch (uitype)
        {
            case UIType.Pause:
                {
                    SceneManager.drawNonUI = false;

                    timeSystem.SwitchTabTimer(false, false);
                    //buttonStore.SwitchTabStore(false, false);
                    roadTab.SwitchTabRoad(false, true);
                    buildingsTab.SwitchTabBuildings(false, true);

                    Disable<Transform>(timerButton);
                    Disable<Transform>(roadTabTransform);
                    Disable<Transform>(buildingsTabTransform);

                    Disable<Transform>(moneyText);
                    Disable<Transform>(coinSymbol);
                    Disable<Transform>(dayClock);

                    Disable<Transform>(listOfCostText);
                    listOfCostDestUI.alpha = 0f;
                    break;             
                }
            //case UIType.Time:
            //    {
            //        pauseMenu.SwitchTabPause(false, false);
            //        buttonStore.SwitchTabStore(false, false);
            //        buttonRoad.SwitchTabRoad(false, false);
            //
            //        Disable<Transform>(pauseIcon);
            //        Disable<Transform>(storeButton);
            //        Disable<Transform>(displayArrow);
            //        break;
            //    }
            case UIType.Store:
                {
                    SceneManager.drawNonUI = false;

                    pauseMenu.SwitchTabPause(false, false);
                    timeSystem.SwitchTabTimer(false, false);
                    roadTab.SwitchTabRoad(false, true);
                    buildingsTab.SwitchTabBuildings(false, true);

                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(timerButton);
                    Disable<Transform>(roadTabTransform);
                    Disable<Transform>(buildingsTabTransform);
                    break;
                }
            case UIType.Road:
                {
                    SceneManager.drawNonUI = false;


                    pauseMenu.SwitchTabPause(false, false);
                    timeSystem.SwitchTabTimer(false, false);
                    //buttonStore.SwitchTabStore(false, false);
                    //roadTab.SwitchTabRoad(false, true);
                    //buildingsTab.SwitchTabBuildings(false, true);

                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(timerButton);
                    //Disable<Transform>(roadTabTransform);
                    //Disable<Transform>(buildingsTabTransform);
                    Disable<Transform>(dayClock);
                    Disable<Transform>(dayTimer);
                    Disable<Transform>(ampm);
                    Disable<Transform>(maintenancefee);
                    Disable<Transform>(maintenanceIcon);

                    Disable<Transform>(listOfCostText);
                    listOfCostDestUI.alpha = 0f;
                    break;
                }
            case UIType.None:
                {
                    SceneManager.drawNonUI = false;


                    pauseMenu.SwitchTabPause(false, false);
                    timeSystem.SwitchTabTimer(false, false);
                    //buttonStore.SwitchTabStore(false, false);
                    roadTab.SwitchTabRoad(false, true);
                    buildingsTab.SwitchTabBuildings(false, true);

                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(timerButton);
                    Disable<Transform>(roadTabTransform);
                    Disable<Transform>(buildingsTabTransform);
                    Disable<Transform>(dayClock);
                    Disable<Transform>(dayTimer);
                    Disable<Transform>(ampm);
                    Disable<Transform>(maintenancefee);
                    Disable<Transform>(maintenanceIcon);

                    Disable<Transform>(listOfCostText);
                    listOfCostDestUI.alpha = 0f;
                    break;
                }
        }
    }

    public void EnableAllMasterButton()
    {
        SceneManager.drawNonUI = true;

        Enable<Transform>(pauseIcon);
        Enable<Transform>(timerButton);

        if (isRoadTabOpen)
        {
            roadTab.SwitchTabRoad(true);
            roadTab.CallFunction(ButtonType.Latest);
        }
        if (isBuildingsTabOpen)
        {
            buildingsTab.SwitchTabBuildings(true);
            buildingsTab.CallFunction(ButtonType.Latest);
        }

        if (isClockOpen)
        {
            timeSystem.SwitchTabTimer(true);
        }
            //Enable<Transform>(displayArrow);
        Enable<Transform>(roadTabTransform);
        Enable<Transform>(buildingsTabTransform);
        Enable<Transform>(moneyText);
        Enable<Transform>(coinSymbol);
        Enable<Transform>(dayClock);
        Enable<Transform>(dayTimer);
        Enable<Transform>(ampm);
        Enable<Transform>(maintenancefee);
        Enable<Transform>(maintenanceIcon);

        Enable<Transform>(listOfCostText);
        listOfCostDestUI.alpha = 1f;
    }


}
