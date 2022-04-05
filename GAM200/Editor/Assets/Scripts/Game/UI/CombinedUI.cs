
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
    ButtonStore buttonStore;
    public ButtonRoad buttonRoad;

    Transform pauseIcon;
    Transform timerButton;
    Transform storeButton;
    Transform displayArrow;

    Transform moneyText;
    Transform coinSymbol;
    Transform dayClock;

    Transform listOfCostText;
    UI listOfCostDestUI;

    bool isBuildOpen;
    bool isClockOpen;

    public override void Start()
    {
        pauseMenu = GameObject.Find("PauseIcon").GetComponent<PauseMenu>();
        timeSystem = GameObject.Find("TimerIcon").GetComponent<TimeSystem>();
        buttonStore = GameObject.Find("Storebtn").GetComponent<ButtonStore>();
        buttonRoad = GameObject.Find("Displaybtn").GetComponent<ButtonRoad>();

        pauseIcon = GameObject.Find("PauseIcon").GetComponent<Transform>();
        timerButton = GameObject.Find("TimerIcon").GetComponent<Transform>();
        storeButton = GameObject.Find("Storebtn").GetComponent<Transform>();
        displayArrow = GameObject.Find("Displaybtn").GetComponent<Transform>();


        moneyText = GameObject.Find("MoneyText").GetComponent<Transform>();
        coinSymbol = GameObject.Find("CoinBag").GetComponent<Transform>();
        dayClock = GameObject.Find("DayClock").GetComponent<Transform>();

        listOfCostText = GameObject.Find("ListOfCostText").GetComponent<Transform>();
        listOfCostDestUI = GameObject.Find("ListOfCostDest").GetComponent<UI>();

        isBuildOpen = false;
        isClockOpen = false;
    }

    public void CloseAllUIExcept(UIType uitype)
    {
        if (buttonRoad.isOn) isBuildOpen = true;
        else isBuildOpen = false;

        if (timeSystem.isOn) isClockOpen = true;
        else isClockOpen = false;

        switch (uitype)
        {
            case UIType.Pause:
                {
                    SceneManager.drawNonUI = false;

                    timeSystem.SwitchTabTimer(false, false);
                    buttonStore.SwitchTabStore(false, false);
                    buttonRoad.SwitchTabRoad(false, false);

                    Disable<Transform>(timerButton);
                    Disable<Transform>(storeButton);
                    Disable<Transform>(displayArrow);

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
                    buttonRoad.SwitchTabRoad(false, false);
                    
                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(timerButton);
                    Disable<Transform>(displayArrow);
                    break;
                }
            //case UIType.Road:
            //    {
            //        pauseMenu.SwitchTabPause(false, false);
            //        timeSystem.SwitchTabTimer(false, false);
            //        buttonStore.SwitchTabStore(false, false);
            //
            //        Disable<Transform>(pauseIcon);
            //        Disable<Transform>(timerButton);
            //        Disable<Transform>(storeButton);
            //        break;
            //    }
            case UIType.None:
                {
                    SceneManager.drawNonUI = false;


                    pauseMenu.SwitchTabPause(false, false);
                    timeSystem.SwitchTabTimer(false, false);
                    buttonStore.SwitchTabStore(false, false);
                    buttonRoad.SwitchTabRoad(false, false);

                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(timerButton);
                    Disable<Transform>(storeButton);
                    Disable<Transform>(displayArrow);

                    Disable<Transform>(dayClock);

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
        Enable<Transform>(storeButton);

        if (isBuildOpen)
        {
            buttonRoad.SwitchTabRoad(true);
            buttonRoad.CallFunction(ButtonType.Latest);

        }
        if (isClockOpen)
        {
            timeSystem.SwitchTabTimer(true);
        }

        else Enable<Transform>(displayArrow);

        Enable<Transform>(moneyText);
        Enable<Transform>(coinSymbol);
        Enable<Transform>(dayClock);

        Enable<Transform>(listOfCostText);
        listOfCostDestUI.alpha = 1f;
    }


}
