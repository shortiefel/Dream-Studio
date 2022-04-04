using System;

public class HelperPageTip : MonoBehaviour
{

    CombinedUI combinedUI;
    GameState gameState;

    public override void Start()
    {
        combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
    }
    public override void Update()
    {
        if (transform.isActive && Input.GetMouseButtonDown(MouseCode.Left))
        {
            Disable<Transform>(transform);
            Time.timeScale = gameState.GetTimeScaleToRestore();

            Enable<Transform>(GameObject.Find("MoneyText").GetComponent<Transform>());
            //Enable<Transform>(GameObject.Find("CounterText").GetComponent<Transform>());
            //Enable<Transform>(GameObject.Find("Displaybtn").GetComponent<Transform>());

            combinedUI.EnableAllMasterButton();
        }
    }
}