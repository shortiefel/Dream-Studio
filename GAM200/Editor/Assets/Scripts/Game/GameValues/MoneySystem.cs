using System;

public class MoneySystem : MonoBehaviour
{
    //GameState gameState;
    Text textComp;

    public int money;

    public int erpCost;
    public int tlCost;
    public int roadCost;

    public int roadNum;
    public int tlNum;
    public int erpNum;
    public int roadTax;
    public int erpTax;
    public int trafficTax;
    public int totalTax;
    public int balance;

    private int erpBuyCount;
    private int tlBuyCount;

    RoadManager roadManager;
    ERPManager erpManager;
    TrafficLightManager trafficLightManager;
    GameState gameState;
    Receipt receipt;

    public override void Start()
    {
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();
        erpManager = GameObject.Find("ERPManager").GetComponent<ERPManager>();
        trafficLightManager = GameObject.Find("TrafficManager").GetComponent<TrafficLightManager>();
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
        receipt = GameObject.Find("Receipt").GetComponent<Receipt>();
        money = 1000;
        textComp = GetComponent<Text>();
        textComp.text = money.ToString();

        roadCost = 10;
        tlCost = 50;
        erpCost = 50;

        erpBuyCount = 0;
        tlBuyCount = 0;
    }

    public void AddMoney(int val)
    {
        money += val;
        textComp.text = money.ToString();
    }

    public void MinusMoney(int val)
    {

        money -= val;
        if (money < 1)
            money = 0;
        textComp.text = money.ToString();

        balance = money;
    }

    public int GetMoney()
    {
        return money;
    }

    public void TaxMoney()
    {
        roadNum = roadManager.taxRoadCount;
        tlNum = trafficLightManager.trafficlightTaxCount();
        erpNum = erpManager.erpTaxCount();

        roadTax =  roadNum* 3;
        trafficTax = tlNum * 4;
        erpTax = erpNum * 5;
        

        totalTax = roadTax + erpTax + trafficTax;

        MinusMoney(totalTax);

        if (balance < 0)
        {
            gameState.shouldEnd = true;
        }

        receipt.ShowReceipt();
    }

    //public int GetCurrRoad()
    //{
    //    return currRoad;
    //}

    public void BuyRoad()
    {
        money -= roadCost;
        textComp.text = money.ToString();
        ++roadManager.roadCount;
    }

    public void SellRoad()
    {
        if (roadManager.roadCount == 0) return;

        money = money + 10;
        textComp.text = money.ToString();
        --roadManager.roadCount;
    }

    public int GetErpCost()
    {
        return erpCost;
    }
    public void BuyErp()
    {
        money -= erpCost;
        textComp.text = money.ToString();
        ++roadManager.erpManager.erpCount;
        ++erpBuyCount;
        erpCost += (erpBuyCount * 10);
       
    }
    public void SellErp()
    {
        if (roadManager.erpManager.erpCount == 0) return;

        money = money + 10;
        textComp.text = money.ToString();
        --roadManager.erpManager.erpCount;
    }

    public int GetTLCost()
    {
        return tlCost;
    }
    public void BuyTrafficLight()
    {
        money -= tlCost;
        textComp.text = money.ToString();
        ++roadManager.trafficLightManager.tlCount;
        ++tlBuyCount;
        tlCost += (int)(tlBuyCount * 10);
       
    }
    public void SellTL()
    {
        if (roadManager.trafficLightManager.tlCount == 0) return;

        money += 25;
        textComp.text = money.ToString();
        --roadManager.trafficLightManager.tlCount;
    }

}

