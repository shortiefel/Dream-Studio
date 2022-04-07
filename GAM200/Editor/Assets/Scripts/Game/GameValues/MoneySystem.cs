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
    DestPolice,
    RemoveCar,
    Ignore
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
    static Text textComp;
    static public int money;

    public int erpCost;
    public int tlCost;
    public int roadCost;
    public int parkCost;
    public int hospitalCost;
    public int officeCost;
    public int shoppingmallCost;
    public int policestationCost;

    public int roadNum;
    public int tlNum;
    public int erpNum;
    public int roadTax;
    public int erpTax;
    public int trafficTax;
    public int totalTax;
    static public int balance;
    public int road_counter;
    public int traffic_counter;
    public int erp_counter;
    public int park_counter;
    public int hospital_counter;
    public int office_counter;
    public int shoppingmall_counter;
    public int policestation_counter;

    public bool road_bool;
    public bool traffic_bool;
    public bool erp_bool;

    private int erpBuyCount;
    private int tlBuyCount;
    private int parkBuyCount;
    private int hospitalBuyCount;
    private int officeBuyCount;
    private int shoppingmallBuyCount;
    private int policestationBuyCount;
    static private AudioSource purchaseSound;


    RoadManager roadManager;
    ERPManager erpManager;
    TrafficLightManager trafficLightManager;
    GameState gameState;
    Receipt receipt;

    static Queue<MoneyInfoTextStruct> listOfCost;
    float listOfCostTimer;
    float listOfCostFadeTimer;
    float listOfCostTimerFadeTimeMax;
    float listOfCostTimerMax;
    Transform listOfCostTransform;
    Text listOfCostText;
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
    Transform infoDestTransform;
    //Transform infoDestOffice;
    //Transform infoDestPark;
    //Transform infoDestMall;

    UI infoDestTexture;

    Transform storePopText;
    Transform storePopInfo;
    static bool displayText = false;
    float timer = 0f;

    float dt;

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
        parkCost = 100;
        hospitalCost = 100;
        officeCost = 100;
        shoppingmallCost = 100;
        policestationCost = 100;

        road_counter = 0;
        traffic_counter = 0;
        erp_counter = 0;
        park_counter = 0;
        hospital_counter = 0;
        office_counter = 0;
        shoppingmall_counter = 0;
        policestation_counter = 0;

        erpBuyCount = 0;
        tlBuyCount = 0;
        parkBuyCount = 0;
        hospitalBuyCount = 0;
        officeBuyCount = 0;
        shoppingmallBuyCount = 0;
        policestationBuyCount = 0;

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
            listOfCostTransform = goListCost.GetComponent<Transform>();
            listOfCostText = goListCost.GetComponent<Text>();
        }
        requireFading = false;
        textStartPosition = new Vector2(62f, 41.1f);
        textYFinalPosition = 34.9f;

        imageStartPosition = new Vector2(56.7f, 41.1f);
        imageYFinalPosition = 35.5f;

        purchaseSound = GameObject.Find("MoneyText").GetComponent<AudioSource>();

        GameObject goImageDestImage = GameObject.Find("ListOfCostDest");
        if (goImageDestImage != null)
        {
            infoDestTransform = goImageDestImage.GetComponent<Transform>();
            infoDestTexture = goImageDestImage.GetComponent<UI>();
        }

        storePopText = GameObject.Find("ShopPopText").GetComponent<Transform>();
        storePopInfo = GameObject.Find("ShopPopInfo").GetComponent<Transform>();
        Disable<Transform>(storePopText);
        Disable<Transform>(storePopInfo);
    }


    public override void FixedUpdate()
    {
        //if (Input.GetKeyDown(KeyCode.H))
        //{
        //    AddMoney(100, MoneySource.DestHospital);
        //}
        //Debug.Log(listOfCost.Count);

        dt = Time.fixedDeltaTime;

        if (displayText == true)
        {
            timer += Time.fixedDeltaTime;
            if (timer > 1.5f)
            {
                Disable<Transform>(storePopText);
                Disable<Transform>(storePopInfo);
                timer = 0f;
                displayText = false;
            }
        }

        if (requireFading)
        {
            listOfCostFadeTimer += dt;
            listOfCostTransform.position = new Vector2(listOfCostTransform.position.x, Mathf.Lerp(listOfCostTransform.position.y, textYFinalPosition, listOfCostFadeTimer));

            infoDestTransform.position = new Vector2(infoDestTransform.position.x, Mathf.Lerp(infoDestTransform.position.y, imageYFinalPosition, listOfCostFadeTimer));

            if (listOfCostFadeTimer > listOfCostTimerFadeTimeMax)
            {
                listOfCostText.alpha -= 0.1f;
                if (listOfCostText.alpha <= 0f)
                {
                    Disable<Transform>(infoDestTransform);
                    listOfCostFadeTimer = 0f;
                    requireFading = false;
                }
            }
        }

        if (listOfCost.Count != 0)
        {
            listOfCostTimer += dt * 2f;

            if (listOfCostTimer > listOfCostTimerMax)
            {
                listOfCostTimer = 0f;
                MoneyInfoTextStruct info = listOfCost.Dequeue();

                listOfCostText.alpha = 1f;
                
                if (info.cost > 0)
                {
                    listOfCostText.text = "+" + info.cost.ToString();
                    listOfCostText.color = new Color(0f, 1f, 0f);
                }

                else
                {
                    listOfCostText.text = info.cost.ToString();
                    listOfCostText.color = new Color(1f, 0f, 0f);
                }

                requireFading = true;
                listOfCostFadeTimer = 0f;

                listOfCostTransform.position = textStartPosition;
                currentSource = info.source;

                Enable<Transform>(infoDestTransform);
                infoDestTransform.position = imageStartPosition;

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
                    case MoneySource.RemoveCar:
                        {
                            infoDestTexture.ChangeTexture("CarIcon");
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

    static public void AddMoney(int val, MoneySource ms)
    {
        money += val;
        textComp.text = money.ToString();

        //Debug.Log("Adding money");
        if (ms != MoneySource.Ignore)
            listOfCost.Enqueue(new MoneyInfoTextStruct(val, ms));
    }

    static public void MinusMoney(int val, MoneySource ms)
    {

        money -= val;
        textComp.text = money.ToString();

        balance = money;

        //Debug.Log("Minus money");
        if (ms != MoneySource.Ignore)
            listOfCost.Enqueue(new MoneyInfoTextStruct(-val, ms));
    }

    public int GetMoney()
    {
        return money;
    }

    static public void RemoveCarMoney()
    {
        MinusMoney(20, MoneySource.RemoveCar);
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

    public bool BuyRoad()
    {

        if (money >= 20)
        {
            MinusMoney(20, MoneySource.Store);
            //roadManager.roadCount++;	
            return true;
        }
        else
        {
            displayText = true;
        }
        return false;
    }

    public void SellRoad()
    {
        AddMoney(10, MoneySource.Store);
    }

    public bool BuyErp()
    {
        if (money >= erpCost)
        {
            MinusMoney(erpCost, MoneySource.Store);
            erpCost *= (int)(1.1);
            return true;
        }
        else
        {
            displayText = true;
            
            Enable<Transform>(storePopText);
            Enable<Transform>(storePopInfo);
        }
        return false;
    }

    public void SellErp()
    {
        AddMoney((int)(erpCost * 0.5), MoneySource.Store);
    }

    public bool BuyTrafficLight()
    {
        if (money >= tlCost)
        {
            MinusMoney(tlCost, MoneySource.Store);
            tlCost *= (int)(1.1);
            return true;
        }
        else
        {
            displayText = true;
            Enable<Transform>(storePopText);
            Enable<Transform>(storePopInfo);
        }
        return false;
    }
    public void SellTL()
    {
        AddMoney((int)(tlCost * 0.5), MoneySource.Store);
    }

    public bool BuyPark()
    {
        if (money >= parkCost)
        {
            MinusMoney(parkCost, MoneySource.Store);
            parkCost *= 5;
            purchaseSound.Play();
            return true;
        }
        else
        {
            displayText = true;
            Enable<Transform>(storePopText);
            Enable<Transform>(storePopInfo);
        }
        return false;
    }
    public void SellPark()
    {
        AddMoney((int)(parkCost * 0.5), MoneySource.Store);
    }
    public bool BuyHospital()
    {
        if (money >= hospitalCost)
        {
            MinusMoney(hospitalCost, MoneySource.Store);
            hospitalCost *= 5;
            purchaseSound.Play();
            return true;
        }
        else
        {
            displayText = true;
            Enable<Transform>(storePopText);
            Enable<Transform>(storePopInfo);
        }
        return false;
    }
    public void SellHospital()
    {
        AddMoney((int)(hospitalCost * 0.5), MoneySource.Store);
    }
    public bool BuyOffice()
    {
        if (money >= officeCost)
        {
            MinusMoney(officeCost, MoneySource.Store);
            officeCost *= 5;
            purchaseSound.Play();
            return true;
        }
        else
        {
            displayText = true;
            Enable<Transform>(storePopText);
            Enable<Transform>(storePopInfo);
        }
        return false;
    }
    public void SellOffice()
    {
        AddMoney((int)(officeCost * 0.5), MoneySource.Store);
    }
    public bool BuyMall()
    {
        if (money >= shoppingmallCost)
        {
            MinusMoney(shoppingmallCost, MoneySource.Store);
            shoppingmallCost *= 5;
            purchaseSound.Play();
            return true;
        }
        else
        {
            displayText = true;
            Enable<Transform>(storePopText);
            Enable<Transform>(storePopInfo);
        }
        return false;
    }
    public void SellMall()
    {
        AddMoney((int)(shoppingmallCost * 0.5), MoneySource.Store);
    }
    public bool BuyPoliceStation()
    {
        if (money >= policestationCost)
        {
            MinusMoney(policestationCost, MoneySource.Store);
            policestationCost *= 5;
            purchaseSound.Play();
            return true;
        }
        else
        {
            displayText = true;
            Enable<Transform>(storePopText);
            Enable<Transform>(storePopInfo);
        }
        return false;
    }
    public void SellPoliceStation()
    {
        AddMoney((int)(policestationCost * 0.5), MoneySource.Store);
    }

    //public int road_count()	
    //{	
    //    return road_counter;	
    //}	
    //public int tl_count()	
    //{	
    //    return traffic_counter;	
    //}	
    //public int erp_count()	
    //{	
    //    return erp_counter;	
    //}	
    //public int park_count()	
    //{	
    //    return park_counter;	
    //}	
    //public int hospital_count()	
    //{	
    //    return hospital_counter;	
    //}	
    //public int office_count()	
    //{	
    //    return office_counter;	
    //}	
    //public int shoppingmall_count()	
    //{	
    //    return shoppingmall_counter;	
    //}	
    //public int policestation_count()	
    //{	
    //    return policestation_counter;	
    //}	
    //public int erpbuy_count()	
    //{	
    //    return erpBuyCount;	
    //}	
    //public int calculatetl_cost()	
    //{	
    //    int total_amount = 0;	
    //    int buyc = tlBuyCount ;	
    //    for (int i = 0; i < traffic_counter; i++)	
    //    {	
    //        total_amount += 50 + buyc * 10;	
    //        buyc++;	
    //    }	
    //    return total_amount;	
    //}	
    //public int calculateerp_cost()	
    //{	
    //    int total_amount = 0;	
    //    int buyc = erpBuyCount;	
    //    for (int i = 0; i < erp_counter; i++)	
    //    {	
    //        total_amount += 50 + buyc * 10;	
    //        buyc++;	
    //    }	
    //    return total_amount;	
    //}	
    //public int getParkCost()	
    //{	
    //    if (parkBuyCount == 0 && park_counter == 1)	
    //        return 100;	
    //    int total_amount = 0;	
    //    int temp = parkCost;	
    //    for(int i = 1; i < park_counter; i ++)	
    //    {	
    //        total_amount = (temp * 5);	
    //        temp = temp * 5;	
    //    }	
    //    return total_amount;	
    //}	
    //public bool get_r_bool()	
    //{	
    //    return road_bool;	
    //}	
    //public bool get_tl_bool()	
    //{	
    //    return traffic_bool;	
    //}	
    //public bool get_erp_bool()	
    //{	
    //    return erp_bool;	
    //}


    
}

