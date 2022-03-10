using System;

public class MoneySystem : MonoBehaviour
{
    //GameState gameState;
    Text textComp;

    public int money;

    public int erpCost;
    public int tlCost;
    public int roadCost;

    private int erpBuyCount;
    private int tlBuyCount;

    RoadManager roadManager;

    public override void Start()
    {
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();
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
    }

    public int GetMoney()
    {
        return money;
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


    //public int GetCurrErp()
    //{
    //    return currErp;
    //}

    public void BuyErp()
    {
        money -= erpCost;
        textComp.text = money.ToString();
        ++roadManager.erpManager.erpCount;
        erpCost += (erpBuyCount * 10);
        ++erpBuyCount;
    }
    public void SellErp()
    {
        if (roadManager.erpManager.erpCount == 0) return;

        money = money + 10;
        textComp.text = money.ToString();
        --roadManager.erpManager.erpCount;
    }
    //public int GetCurrTL()
    //{
    //    return currTL;
    //}
    public void BuyTrafficLight()
    {
        money -= tlCost;
        textComp.text = money.ToString();
        ++roadManager.trafficLightManager.tlCount;
        tlCost += (int)(tlBuyCount * 10);
        ++tlBuyCount;
    }
    public void SellTL()
    {
        if (roadManager.trafficLightManager.tlCount == 0) return;

        money += 25;
        textComp.text = money.ToString();
        --roadManager.trafficLightManager.tlCount;
    }
}

