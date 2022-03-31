using System;
using System.Collections.Generic;

public enum MoneySource
{
    Store = 0,
    ERP,
    Tax,
    DestHospital,
    DestOffice,
    DestPark,
    DestMall,
    DestPolice
}

struct MoneyInfoTextStruct {
    public int cost;
    public MoneySource source;

    public MoneyInfoTextStruct(int _c, MoneySource _s)
    {
        cost = _c;
        source = _s;
    }
}
public class MoneySystem : MonoBehaviour
{
    //GameState gameState;
    Text textComp;

    int money;

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

    Queue<MoneyInfoTextStruct> listOfCost;
    float listOfCostTimer;
    float listOfCostFadeTimer;
    float listOfCostTimerFadeTimeMax;
    float listOfCostTimerMax;
    Transform listOfCostTimerTransform;
    Text listOfCostTimerText;
    bool requireFading;
    Vector2 textStartPosition;
    float textYFinalPosition;

    MoneySource currentSource;

    Vector2 imageStartPosition;
    float imageYFinalPosition;

    //Transform infoStore;
    //Transform infoERP;
    //Transform infoTax;

    //Transform infoDest;
    Transform infoDestHospital;
    //Transform infoDestOffice;
    //Transform infoDestPark;
    //Transform infoDestMall;

    UI infoDestTexture;


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
        listOfCostTimerMax = 1f;
        listOfCostTimer = listOfCostTimerMax;
        listOfCostFadeTimer = 0f;
        listOfCostTimerFadeTimeMax = 0.8f * listOfCostTimerMax;
        listOfCost = new Queue<MoneyInfoTextStruct>();
        GameObject goListCost = GameObject.Find("ListOfCostText");
        if (goListCost != null)
        {
            listOfCostTimerTransform = goListCost.GetComponent<Transform>();
            listOfCostTimerText = goListCost.GetComponent<Text>();
        }
        requireFading = false;
        textStartPosition = new Vector2(62f, 41.1f);
        textYFinalPosition = 34.9f;

        imageStartPosition = new Vector2(56.7f, 41.1f);
        imageYFinalPosition = 35.5f;

        //GameObject goImageStore = GameObject.Find("ListOfCostImageStore");
        //if (goImageStore != null)
        //{
        //    infoStore = goImageStore.GetComponent<Transform>();
        //}
        //
        //GameObject goImageERP = GameObject.Find("ListOfCostERP");
        //if (goImageERP != null)
        //{
        //    infoERP = goImageERP.GetComponent<Transform>();
        //}
        //
        //GameObject goImageTax = GameObject.Find("ListOfCostTax");
        //if (goImageTax != null)
        //{
        //    infoTax = goImageTax.GetComponent<Transform>();
        //}

        //GameObject goImageDest = GameObject.Find("ListOfCostDest");
        //if (goImageDest != null)
        //{
        //    infoDest = goImageDest.GetComponent<Transform>();
        //}

        GameObject goImageDestHospital = GameObject.Find("ListOfCostDestHospital");
        if (goImageDestHospital != null)
        {
            infoDestHospital = goImageDestHospital.GetComponent<Transform>();
            infoDestTexture = goImageDestHospital.GetComponent<UI>();
        }

        //GameObject goImageDestOffice = GameObject.Find("ListOfCostDestOffice");
        //if (goImageDestOffice != null)
        //{
        //    infoDestOffice = goImageDestOffice.GetComponent<Transform>();
        //}
        //
        //GameObject goImageDestPark = GameObject.Find("ListOfCostDestPark");
        //if (goImageDestPark != null)
        //{
        //    infoDestPark = goImageDestPark.GetComponent<Transform>();
        //}
        //
        //GameObject goImageDestMall = GameObject.Find("ListOfCostDestMall");
        //if (goImageDestMall != null)
        //{
        //    infoDestMall = goImageDestMall.GetComponent<Transform>();
        //}

        //NOTE: REMOVE THE OTHER GAME OBJECT (ListOfCost...)
    }


    public override void FixedUpdate()
    {
        if (Input.GetKeyDown(KeyCode.H))
        {
            AddMoney(100, MoneySource.DestHospital);
        }
        //Debug.Log(listOfCost.Count);
        if (requireFading)
        {
            listOfCostFadeTimer += Time.fixedDeltaTime;
            listOfCostTimerTransform.position = new Vector2(listOfCostTimerTransform.position.x, Mathf.Lerp(listOfCostTimerTransform.position.y, textYFinalPosition, listOfCostFadeTimer));

            infoDestHospital.position = new Vector2(infoDestHospital.position.x, Mathf.Lerp(infoDestHospital.position.y, imageYFinalPosition, listOfCostFadeTimer));

            if (listOfCostFadeTimer > listOfCostTimerFadeTimeMax)
            {
                listOfCostTimerText.alpha -= 0.1f;
                if (listOfCostTimerText.alpha <= 0f)
                {
                    Disable<Transform>(infoDestHospital);
                    listOfCostFadeTimer = 0f;
                    requireFading = false;
                }
            }
        }

        if (listOfCost.Count != 0)
        {
            listOfCostTimer += Time.fixedDeltaTime;

            if (listOfCostTimer > listOfCostTimerMax)
            {
                listOfCostTimer = 0f;
                MoneyInfoTextStruct info = listOfCost.Dequeue();

                listOfCostTimerText.alpha = 1f;
                
                if (info.cost > 0)
                {
                    listOfCostTimerText.text = "+" + info.cost.ToString();
                    listOfCostTimerText.color = new Color(0f, 1f, 0f);
                }

                else
                {
                    listOfCostTimerText.text = info.cost.ToString();
                    listOfCostTimerText.color = new Color(1f, 0f, 0f);
                }

                requireFading = true;
                listOfCostFadeTimer = 0f;

                listOfCostTimerTransform.position = textStartPosition;
                currentSource = info.source;

                Enable<Transform>(infoDestHospital);
                infoDestHospital.position = imageStartPosition;

                switch (currentSource)
                {
                    case MoneySource.Store:
                        {
                            infoDestTexture.ChangeTexture("Game/UI/ShoppingCart");
                            break;
                        }
                    case MoneySource.ERP:
                        {
                            infoDestTexture.ChangeTexture("Game/ERP");
                            break;
                        }
                    case MoneySource.Tax:
                        {
                            infoDestTexture.ChangeTexture("Game/UI/New_BAG-01-08");
                            break;
                        }

                    case MoneySource.DestHospital:
                        {
                            infoDestTexture.ChangeTexture("Game/Houses/Hospital");
                            break;
                        }
                    case MoneySource.DestOffice:
                        {
                            infoDestTexture.ChangeTexture("Game/Houses/Office");
                            break;
                        }
                    case MoneySource.DestPark:
                        {
                            infoDestTexture.ChangeTexture("Game/Houses/Park");
                            break;
                        }
                    case MoneySource.DestMall:
                        {
                            infoDestTexture.ChangeTexture("Game/Houses/ShoppingMall");
                            break;
                        }
                    case MoneySource.DestPolice:
                        {
                            infoDestTexture.ChangeTexture("Game/Houses/PoliceStation");
                            break;
                        }
                }
            }
        }

        //if (Input.GetKey(KeyCode.F))
        //{
        //    TimeSystem.NormalTime();
        //}

    }

    public void AddMoney(int val, MoneySource ms)
    {
        money += val;
        textComp.text = money.ToString();

        //Debug.Log("Adding money");
        listOfCost.Enqueue(new MoneyInfoTextStruct(val, ms));
    }

    public void MinusMoney(int val, MoneySource ms)
    {

        money -= val;
        textComp.text = money.ToString();

        balance = money;

        //Debug.Log("Minus money");
        listOfCost.Enqueue(new MoneyInfoTextStruct(-val, ms));
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

        MinusMoney(totalTax, MoneySource.Tax);
        receipt.ShowReceipt();
        if (balance < 0)
        {
            gameState.shouldEnd = true;
        }

        
    }

    public void BuyRoad(int count)
    {
        MinusMoney(count * 20, MoneySource.Store);
        roadManager.roadCount += count;
    }

    public void SellRoad(int count)
    {
        AddMoney(count * 10, MoneySource.Store);
        roadManager.roadCount -= count;
    }

    public int GetErpCost()
    {
        return erpCost;
    }
    public void BuyErp(int count)
    {
        int tempvalue = 0;
        for (int i = 0; i < count; i++)
        {
            tempvalue += erpCost;
            erpBuyCount++;
            erpCost = 50 + erpBuyCount * 10;
        }
        MinusMoney(tempvalue, MoneySource.Store);
        roadManager.erpManager.erpCount += count;
       
    }
    public void SellErp(int count)
    {
        AddMoney(count * (int)(erpCost * 0.5), MoneySource.Store);
        roadManager.erpManager.erpCount -= count;
    }
    public void BuyTrafficLight(int count)
    {
        int tempvalue = 0;
        for (int i = 0; i < count; i++)
        {
            tempvalue += tlCost;
            tlBuyCount++;
            tlCost = 50 + tlBuyCount * 10;
        }
        MinusMoney(tempvalue,MoneySource.Store);
        roadManager.trafficLightManager.tlCount += count;
    }
    public void SellTL(int count)
    {
        AddMoney(count * (int)(tlCost * 0.5), MoneySource.Store);
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

