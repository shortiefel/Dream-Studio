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
    public int road_counter;
    public int traffic_counter;
    public int erp_counter;

    public bool road_bool;
    public bool traffic_bool;
    public bool erp_bool;

    private int erpBuyCount;
    private int tlBuyCount;

    RoadManager roadManager;
    ERPManager erpManager;
    TrafficLightManager trafficLightManager;
    GameState gameState;
    Receipt receipt;

    public override void Start()
    {
        GameObject go = GameObject.Find("RoadManager");
        if (go != null)
            roadManager = go.GetComponent<RoadManager>();

        GameObject go2 = GameObject.Find("ERPManager");
        if (go2 != null)
            erpManager = go2.GetComponent<ERPManager>();

        GameObject go3 = GameObject.Find("TrafficManager");
        if (go3 != null)
            trafficLightManager = go3.GetComponent<TrafficLightManager>();

        GameObject go4 = GameObject.Find("GameManager");
        if (go4 != null)
            gameState = go4.GetComponent<GameState>();

        GameObject go5 = GameObject.Find("Receipt");
        if (go5 != null)
            receipt = go5.GetComponent<Receipt>();

        money = 100;
        textComp = GetComponent<Text>();
        textComp.text = money.ToString();

        roadCost = 20;
        tlCost = 50;
        erpCost = 50;
        road_counter = 0;
        traffic_counter = 0;
        erp_counter = 0;

        erpBuyCount = 0;
        tlBuyCount = 0;

        road_bool = false;
        traffic_bool = false;
        erp_bool = false;
    }

    public void AddMoney(int val)
    {
        money += val;
        textComp.text = money.ToString();
    }

    public void MinusMoney(int val)
    {

        money -= val;
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

        roadTax =  roadNum* 25;
        trafficTax = tlNum * 50;
        erpTax = erpNum * 75;
        

        totalTax = roadTax + erpTax + trafficTax;

        MinusMoney(totalTax);
        receipt.ShowReceipt();
        if (balance < 0)
        {
            gameState.shouldEnd = true;
        }

        
    }

    public void BuyRoad(int count)
    {
        money -= count * 20;
        textComp.text = money.ToString();
        roadManager.roadCount += count;
    }

    public void SellRoad(int count)
    {
        money += count * 10;
        textComp.text = money.ToString();
        roadManager.roadCount -= count;
    }

    public int GetErpCost()
    {
        return erpCost;
    }
    public void BuyErp(int count)
    {
        for (int i = 0; i < count; i++)
        {
            money -= erpCost;
            erpBuyCount++;
            erpCost = 50 + erpBuyCount * 10;
        }
        textComp.text = money.ToString();
        roadManager.erpManager.erpCount += count;

    }
    public void SellErp(int count)
    {
        money += count * (int)(erpCost + 0.5);
        textComp.text = money.ToString();
        roadManager.erpManager.erpCount -= count;
    }
    public void BuyTrafficLight(int count)
    {
        for (int i = 0; i < count; i++)
        {
            money -= tlCost;
            tlBuyCount++;
            tlCost = 50 + tlBuyCount * 10;
        }
        textComp.text = money.ToString();
        roadManager.trafficLightManager.tlCount += count;
    }
    public void SellTL(int count)
    {
        money += count * (int)(tlCost * 0.5);
        textComp.text = money.ToString();
        roadManager.trafficLightManager.tlCount -= count;
    }

    public int road_count()
    {
        return road_counter;
    }

    public int tl_count()
    {
        return traffic_counter;
    }

    public int erp_count()
    {
        return erp_counter;
    }

    public int erpbuy_count()
    {
        return erpBuyCount;
    }

    public int calculatetl_cost()
    {
        int total_amount = 0;
        int buyc = tlBuyCount ;
        for (int i = 0; i < traffic_counter; i++)
        {
            total_amount += 50 + buyc * 10;
            buyc++;
        }
        return total_amount;
    }

    public int calculateerp_cost()
    {
        int total_amount = 0;
        int buyc = erpBuyCount;
        for (int i = 0; i < erp_counter; i++)
        {
            total_amount += 50 + buyc * 10;
            buyc++;
        }
        return total_amount;
    }

    public bool get_r_bool()
    {
        return road_bool;
    }

    public bool get_tl_bool()
    {
        return traffic_bool;
    }

    public bool get_erp_bool()
    {
        return erp_bool;
    }
}

