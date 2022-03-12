
public enum UIType
{
    Pause = 0,
    Time,
    Store,
    Road //Bottom left button that build road and stuff
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

    }

    public void CloseAllUIExcept(UIType uitype)
    {
        switch (uitype)
        {
            case UIType.Pause:
                {
                    timeSystem.SwitchTabTimer(false, false);
                    buttonStore.SwitchTabStore(false, false);
                    buttonRoad.SwitchTabRoad(false, false);

                    Disable<Transform>(timerButton);
                    Disable<Transform>(storeButton);
                    Disable<Transform>(displayArrow);
                    break;
                }
            case UIType.Time:
                {
                    pauseMenu.SwitchTabPause(false);
                    buttonStore.SwitchTabStore(false, false);
                    buttonRoad.SwitchTabRoad(false, false);

                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(storeButton);
                    Disable<Transform>(displayArrow);
                    break;
                }
            case UIType.Store:
                {
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
                    pauseMenu.SwitchTabPause(false);
                    timeSystem.SwitchTabTimer(false);
                    buttonStore.SwitchTabStore(false, false);

                    Disable<Transform>(pauseIcon);
                    Disable<Transform>(timerButton);
                    Disable<Transform>(storeButton);
                    break;
                }
        }
    }

    public void EnableAllMasterButton()
    {
        Enable<Transform>(pauseIcon);
        Enable<Transform>(timerButton);
        Enable<Transform>(storeButton);
        Enable<Transform>(displayArrow);
    }


}
