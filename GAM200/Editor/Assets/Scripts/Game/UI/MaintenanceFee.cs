public class MaintenanceFee : MonoBehaviour
{
    MoneySystem moneySystem;
    Text feeCost;
    static public int MaintenanceCost;
    public override void Start()
    {
        MaintenanceCost = 0;
        feeCost = GetComponent<Text>();
        feeCost.text = MaintenanceCost.ToString();
        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();
    }

    public override void Update()
    {
        MaintenanceCost = moneySystem.getTaxMoney();
        feeCost.text = MaintenanceCost.ToString();
    }
}