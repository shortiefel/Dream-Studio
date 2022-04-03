using System.Collections;


public class Receipt : MonoBehaviour
{
    GameObject roadNumber;
    GameObject tlNumber;
    GameObject erpNumber;

    GameObject roadTax;
    GameObject tlTax;
    GameObject erpTax;

    GameObject totalTax;
    GameObject balance;

    GameObject closeReceipt;

    Text roadNumberText;
    Text tlNumberText;
    Text erpNumberText;

    Text roadTaxText;
    Text tlTaxText;
    Text erpTaxText;

    Text totalTaxText;
    Text balanceText;

    MoneySystem moneySystem;

    GameState gameState;

    CombinedUI combinedUI;

    public override void Start()
    {
        roadNumber = GameObject.Find("RoadNum");
        roadNumberText = roadNumber.GetComponent<Text>();
        Disable<Transform>(roadNumber.transform);

        tlNumber = GameObject.Find("TrafficLightNum");
        tlNumberText = tlNumber.GetComponent<Text>();
        Disable<Transform>(tlNumber.transform);

        erpNumber = GameObject.Find("ERPNum");
        erpNumberText = erpNumber.GetComponent<Text>();
        Disable<Transform>(erpNumber.transform);

        roadTax = GameObject.Find("RoadTax");
        roadTaxText = roadTax.GetComponent<Text>();
        Disable<Transform>(roadTax.transform);

        tlTax = GameObject.Find("TrafficLightTax");
        tlTaxText = tlTax.GetComponent<Text>();
        Disable<Transform>(tlTax.transform);

        erpTax = GameObject.Find("ERPTax");
        erpTaxText = erpTax.GetComponent<Text>();
        Disable<Transform>(erpTax.transform);

        totalTax = GameObject.Find("TotalTax");
        totalTaxText = totalTax.GetComponent<Text>();
        Disable<Transform>(totalTax.transform);

        balance = GameObject.Find("Balance");
        balanceText = balance.GetComponent<Text>();
        Disable<Transform>(balance.transform);

        closeReceipt = GameObject.Find("CloseReceipt");
        Disable<Transform>(closeReceipt.transform);

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();

        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();
    }

    public void ShowReceipt()
    {
        roadNumberText.text = moneySystem.roadNum.ToString();
        Enable<Transform>(roadNumber.transform);
        tlNumberText.text = moneySystem.tlNum.ToString();
        Enable<Transform>(tlNumber.transform);
        erpNumberText.text = moneySystem.erpNum.ToString();
        Enable<Transform>(erpNumber.transform);

        roadTaxText.text = moneySystem.roadTax.ToString();
        Enable<Transform>(roadTax.transform);
        tlTaxText.text = moneySystem.trafficTax.ToString();
        Enable<Transform>(tlTax.transform);
        erpTaxText.text = moneySystem.erpTax.ToString();
        Enable<Transform>(erpTax.transform);

        totalTaxText.text = moneySystem.totalTax.ToString();
        Enable<Transform>(totalTax.transform);
        balanceText.text = moneySystem.balance.ToString();
        Enable<Transform>(balance.transform);

        Enable<Transform>(closeReceipt.transform);

        combinedUI.CloseAllUIExcept(UIType.None);
        gameState.SetAllowPause(false);

    }
}