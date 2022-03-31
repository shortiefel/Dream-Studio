
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
    UI listOfCostImageStore;
    UI listOfCostERP;
    UI listOfCostTax;
    UI listOfCostDestHospital;
    UI listOfCostDestOffice;
    UI listOfCostDestPark;
    UI listOfCostDestMall;

    public override void Start()
    {
        pauseMenu = GameObject.Find("PauseIcon").GetComponent<PauseMenu>();
        timeSystem = GameObject.Find("TimerIcon").GetComponent<TimeSystem>();
        buttonStore = GameObject.Find("Storebtn").GetComponent<ButtonStore>();
        buttonRoad = GameObject.Find("ButtonRoad").GetComponent<ButtonRoad>();

        pauseIcon = GameObject.Find("PauseIcon").GetComponent<Transform>();
        timerButton = GameObject.Find("TimerIcon").GetComponent<Transform>();
        storeButton = GameObject.Find("Storebtn").GetComponent<Transform>();
        displayArrow = GameObject.Find("Displaybtn").GetComponent<Transform>();


        moneyText = GameObject.Find("MoneyText").GetComponent<Transform>();
        coinSymbol = GameObject.Find("CoinBag").GetComponent<Transform>();
        dayClock = GameObject.Find("DayClock").GetComponent<Transform>();


        listOfCostText = GameObject.Find("ListOfCostText").GetComponent<Transform>();
        listOfCostImageStore = GameObject.Find("ListOfCostImageStore").GetComponent<UI>();
        listOfCostERP = GameObject.Find("ListOfCostERP").GetComponent<UI>();
        listOfCostTax = GameObject.Find("ListOfCostTax").GetComponent<UI>();
        listOfCostDestHospital = GameObject.Find("ListOfCostDestHospital").GetComponent<UI>();
        listOfCostDestOffice = GameObject.Find("ListOfCostDestOffice").GetComponent<UI>();
        listOfCostDestPark = GameObject.Find("ListOfCostDestPark").GetComponent<UI>();
        listOfCostDestMall = GameObject.Find("ListOfCostDestMall").GetComponent<UI>();
    }

    public void CloseAllUIExcept(UIType uitype)
    {
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
                    listOfCostImageStore.alpha = 0f;
                    listOfCostERP.alpha = 0f;
                    listOfCostTax.alpha = 0f;
                    listOfCostDestHospital.alpha = 0f;
                    listOfCostDestOffice.alpha = 0f;
                    listOfCostDestPark.alpha = 0f;
                    listOfCostDestMall.alpha = 0f;
                    break;             
                }
            case UIType.Time:
                {
                    pauseMenu.SwitchTabPause(false, false);
                    buttonStore.SwitchTabStore(false, false);
                    buttonRoad.SwitchTabRoad(false, false);

                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(storeButton);
                    Disable<Transform>(displayArrow);
                    break;
                }
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
            case UIType.Road:
                {
                    pauseMenu.SwitchTabPause(false, false);
                    timeSystem.SwitchTabTimer(false, false);
                    buttonStore.SwitchTabStore(false, false);

                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(timerButton);
                    Disable<Transform>(storeButton);
                    break;
                }
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
                    listOfCostImageStore.alpha = 0f;
                    listOfCostERP.alpha = 0f;
                    listOfCostTax.alpha = 0f;
                    listOfCostDestHospital.alpha = 0f;
                    listOfCostDestOffice.alpha = 0f;
                    listOfCostDestPark.alpha = 0f;
                    listOfCostDestMall.alpha = 0f;
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
        Enable<Transform>(displayArrow);

        Enable<Transform>(moneyText);
        Enable<Transform>(coinSymbol);
        Enable<Transform>(dayClock);

        Enable<Transform>(listOfCostText);
        listOfCostImageStore.alpha = 1f;
        listOfCostERP.alpha = 1f;
        listOfCostTax.alpha = 1f;
        listOfCostDestHospital.alpha = 1f;
        listOfCostDestOffice.alpha = 1f;
        listOfCostDestPark.alpha = 1f;
        listOfCostDestMall.alpha = 1f;
    }


}
