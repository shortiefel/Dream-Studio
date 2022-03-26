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

    Transform infoStore;
    Transform infoERP;
    Transform infoTax;

    Transform infoDestHospital;
    Transform infoDestOffice;
    Transform infoDestPark;
    Transform infoDestMall;


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

        erpBuyCount = 0;
        tlBuyCount = 0;

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

        GameObject goImageStore = GameObject.Find("ListOfCostImageStore");
        if (goImageStore != null)
        {
            infoStore = goImageStore.GetComponent<Transform>();
        }

        GameObject goImageERP = GameObject.Find("ListOfCostERP");
        if (goImageERP != null)
        {
            infoERP = goImageERP.GetComponent<Transform>();
        }

        GameObject goImageTax = GameObject.Find("ListOfCostTax");
        if (goImageTax != null)
        {
            infoTax = goImageTax.GetComponent<Transform>();
        }


        GameObject goImageDestHospital = GameObject.Find("ListOfCostDestHospital");
        if (goImageDestHospital != null)
        {
            infoDestHospital = goImageDestHospital.GetComponent<Transform>();
        }

        GameObject goImageDestOffice = GameObject.Find("ListOfCostDestOffice");
        if (goImageDestOffice != null)
        {
            infoDestOffice = goImageDestOffice.GetComponent<Transform>();
        }

        GameObject goImageDestPark = GameObject.Find("ListOfCostDestPark");
        if (goImageDestPark != null)
        {
            infoDestPark = goImageDestPark.GetComponent<Transform>();
        }

        GameObject goImageDestMall = GameObject.Find("ListOfCostDestMall");
        if (goImageDestMall != null)
        {
            infoDestMall = goImageDestMall.GetComponent<Transform>();
        }

        //To add to scene file
        {
          //{
          //    "Entity": {
          //    "Name": "ListOfCostText",
          //    "Parent": 10001,
          //    "Child": []
          //  },
          //  "TransformComponent": {
          //    "Position": [ 62.0, 34.9 ],
          //    "LocalPosition": [ 0.0, 0.0 ],
          //    "Scale": [ 1.5, 1.5 ],
          //    "Angle": 0.0,
          //    "Layer": 2,
          //    "IsActive": true
          //  },
          //  "FontComponent": {
          //                  "Filepath": "Assets\\Fonts\\LemonMilkMedium-mLZYV.ttf",
          //    "Text": "-100",
          //    "Colour": [ 1.0, 1.0, 1.0, 1.0 ],
          //    "IsActive": true
          //  }
          //},
          //{
          //              "Entity": {
          //                  "Name": "ListOfCostImageStore",
          //    "Parent": 10001,
          //    "Child": []
          //  },
          //  "TransformComponent": {
          //                  "Position": [ 56.70000076293945, 35.5 ],
          //    "LocalPosition": [ 0.0, 0.0 ],
          //    "Scale": [ 2.0, 2.0 ],
          //    "Angle": 0.0,
          //    "Layer": 2,
          //    "IsActive": false
          //  },
          //  "UIComponent": {
          //                  "Filepath": "Assets\\Textures\\Game\\UI\\ShoppingCart.png",
          //    "Colour": [ 1.0, 1.0, 1.0, 1.0 ],
          //    "IsActive": true
          //  }
          //          },
          //{
          //              "Entity": {
          //                  "Name": "ListOfCostERP",
          //    "Parent": 10001,
          //    "Child": []
          //  },
          //  "TransformComponent": {
          //                  "Position": [ 56.70000076293945, 35.5 ],
          //    "LocalPosition": [ 0.0, 0.0 ],
          //    "Scale": [ 2.0, 2.0 ],
          //    "Angle": 0.0,
          //    "Layer": 2,
          //    "IsActive": false
          //  },
          //  "UIComponent": {
          //                  "Filepath": "Assets\\Textures\\Game\\ERP.png",
          //    "Colour": [ 1.0, 1.0, 1.0, 1.0 ],
          //    "IsActive": true
          //  }
          //          },
          //{
          //              "Entity": {
          //                  "Name": "ListOfCostTax",
          //    "Parent": 10001,
          //    "Child": []
          //  },
          //  "TransformComponent": {
          //                  "Position": [ 56.70000076293945, 35.5 ],
          //    "LocalPosition": [ 0.0, 0.0 ],
          //    "Scale": [ 2.0, 2.0 ],
          //    "Angle": 0.0,
          //    "Layer": 2,
          //    "IsActive": false
          //  },
          //  "UIComponent": {
          //                  "Filepath": "Assets\\Textures\\Game\\UI\\New_BAG-01-08.png",
          //    "Colour": [ 1.0, 1.0, 1.0, 1.0 ],
          //    "IsActive": true
          //  }
          //          },
          //{
          //              "Entity": {
          //                  "Name": "ListOfCostDestHospital",
          //    "Parent": 10001,
          //    "Child": []
          //  },
          //  "TransformComponent": {
          //                  "Position": [ 56.70000076293945, 35.5 ],
          //    "LocalPosition": [ 0.0, 0.0 ],
          //    "Scale": [ 2.0, 2.0 ],
          //    "Angle": 0.0,
          //    "Layer": 2,
          //    "IsActive": false
          //  },
          //  "UIComponent": {
          //                  "Filepath": "Assets\\Textures\\Game\\Houses\\Hospital.png",
          //    "Colour": [ 1.0, 1.0, 1.0, 1.0 ],
          //    "IsActive": true
          //  }
          //          },
          //{
          //              "Entity": {
          //                  "Name": "ListOfCostDestOffice",
          //    "Parent": 10001,
          //    "Child": []
          //  },
          //  "TransformComponent": {
          //                  "Position": [ 56.70000076293945, 35.5 ],
          //    "LocalPosition": [ 0.0, 0.0 ],
          //    "Scale": [ 2.0, 2.0 ],
          //    "Angle": 0.0,
          //    "Layer": 2,
          //    "IsActive": false
          //  },
          //  "UIComponent": {
          //                  "Filepath": "Assets\\Textures\\Game\\Houses\\Office.png",
          //    "Colour": [ 1.0, 1.0, 1.0, 1.0 ],
          //    "IsActive": true
          //  }
          //          },
          //{
          //              "Entity": {
          //                  "Name": "ListOfCostDestPark",
          //    "Parent": 10001,
          //    "Child": []
          //  },
          //  "TransformComponent": {
          //                  "Position": [ 56.70000076293945, 35.5 ],
          //    "LocalPosition": [ 0.0, 0.0 ],
          //    "Scale": [ 2.0, 2.0 ],
          //    "Angle": 0.0,
          //    "Layer": 2,
          //    "IsActive": false
          //  },
          //  "UIComponent": {
          //                  "Filepath": "Assets\\Textures\\Game\\Houses\\Park.png",
          //    "Colour": [ 1.0, 1.0, 1.0, 1.0 ],
          //    "IsActive": true
          //  }
          //          },
          //{
          //              "Entity": {
          //                  "Name": "ListOfCostDestMall",
          //    "Parent": 10001,
          //    "Child": []
          //  },
          //  "TransformComponent": {
          //                  "Position": [ 56.70000076293945, 35.5 ],
          //    "LocalPosition": [ 0.0, 0.0 ],
          //    "Scale": [ 2.0, 2.0 ],
          //    "Angle": 0.0,
          //    "Layer": 2,
          //    "IsActive": false
          //  },
          //  "UIComponent": {
          //                  "Filepath": "Assets\\Textures\\Game\\Houses\\ShoppingMall.png",
          //    "Colour": [ 1.0, 1.0, 1.0, 1.0 ],
          //    "IsActive": true
          //  }
          //}
        }
    }


    public override void FixedUpdate()
    {
        //Debug.Log(listOfCost.Count);
        if (requireFading)
        {
            listOfCostFadeTimer += Time.fixedDeltaTime;
            listOfCostTimerTransform.position = new Vector2(listOfCostTimerTransform.position.x, Mathf.Lerp(listOfCostTimerTransform.position.y, textYFinalPosition, listOfCostFadeTimer));
            switch (currentSource)
            {
                case MoneySource.Store:
                    {
                        infoStore.position = new Vector2(infoStore.position.x, Mathf.Lerp(infoStore.position.y, imageYFinalPosition, listOfCostFadeTimer));
                        break;
                    }
                case MoneySource.ERP:
                    {
                        infoERP.position = new Vector2(infoERP.position.x, Mathf.Lerp(infoERP.position.y, imageYFinalPosition, listOfCostFadeTimer));
                        break;
                    }
                case MoneySource.Tax:
                    {
                        infoTax.position = new Vector2(infoTax.position.x, Mathf.Lerp(infoTax.position.y, imageYFinalPosition, listOfCostFadeTimer));
                        break;
                    }

                case MoneySource.DestHospital:
                    {
                        infoDestHospital.position = new Vector2(infoDestHospital.position.x, Mathf.Lerp(infoDestHospital.position.y, imageYFinalPosition, listOfCostFadeTimer));
                        break;
                    }
                case MoneySource.DestOffice:
                    {
                        infoDestOffice.position = new Vector2(infoDestOffice.position.x, Mathf.Lerp(infoDestOffice.position.y, imageYFinalPosition, listOfCostFadeTimer));
                        break;
                    }
                case MoneySource.DestPark:
                    {
                        infoDestPark.position = new Vector2(infoDestPark.position.x, Mathf.Lerp(infoDestPark.position.y, imageYFinalPosition, listOfCostFadeTimer));
                        break;
                    }
                case MoneySource.DestMall:
                    {
                        infoDestMall.position = new Vector2(infoDestMall.position.x, Mathf.Lerp(infoDestMall.position.y, imageYFinalPosition, listOfCostFadeTimer));
                        break;
                    }
            }

            if (listOfCostFadeTimer > listOfCostTimerFadeTimeMax)
            {
                listOfCostTimerText.alpha -= 0.1f;
                if (listOfCostTimerText.alpha <= 0f)
                {
                    switch (currentSource)
                    {
                        case MoneySource.Store:
                            {
                                Disable<Transform>(infoStore);
                                break;
                            }
                        case MoneySource.ERP:
                            {
                                Disable<Transform>(infoERP);
                                break;
                            }
                        case MoneySource.Tax:
                            {
                                Disable<Transform>(infoTax);
                                break;
                            }

                        case MoneySource.DestHospital:
                            {
                                Disable<Transform>(infoDestHospital);
                                break;
                            }
                        case MoneySource.DestOffice:
                            {
                                Disable<Transform>(infoDestOffice);
                                break;
                            }
                        case MoneySource.DestPark:
                            {
                                Disable<Transform>(infoDestPark);
                                break;
                            }
                        case MoneySource.DestMall:
                            {
                                Disable<Transform>(infoDestMall);
                                break;
                            }
                    }
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
                
                if (info.cost < 0)
                {
                    listOfCostTimerText.text = info.cost.ToString();
                    listOfCostTimerText.color = new Color(1f, 0f, 0f);
                }

                else
                {
                    listOfCostTimerText.text = "+" + info.cost.ToString();
                    listOfCostTimerText.color = new Color(0f, 1f, 0f);
                }

                requireFading = true;
                listOfCostFadeTimer = 0f;

                listOfCostTimerTransform.position = textStartPosition;
                currentSource = info.source;

                switch(currentSource)
                {
                    case MoneySource.Store:
                        {
                            Enable<Transform>(infoStore);
                            infoStore.position = imageStartPosition;
                            break;
                        }
                    case MoneySource.ERP:
                        {
                            Enable<Transform>(infoERP);
                            infoERP.position = imageStartPosition;
                            break;
                        }
                    case MoneySource.Tax:
                        {
                            Enable<Transform>(infoTax);
                            infoTax.position = imageStartPosition;
                            break;
                        }

                    case MoneySource.DestHospital:
                        {
                            Enable<Transform>(infoDestHospital);
                            infoDestHospital.position = imageStartPosition;
                            break;
                        }
                    case MoneySource.DestOffice:
                        {
                            Enable<Transform>(infoDestOffice);
                            infoDestOffice.position = imageStartPosition;
                            break;
                        }
                    case MoneySource.DestPark:
                        {
                            Enable<Transform>(infoDestPark);
                            infoDestPark.position = imageStartPosition;
                            break;
                        }
                    case MoneySource.DestMall:
                        {
                            Enable<Transform>(infoDestMall);
                            infoDestMall.position = imageStartPosition;
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

    //public int GetCurrRoad()
    //{
    //    return currRoad;
    //}

    public void BuyRoad()
    {
        //money -= roadCost;
        //textComp.text = money.ToString();
        MinusMoney(roadCost, MoneySource.Store);
        ++roadManager.roadCount;
    }

    public void SellRoad()
    {
        if (roadManager.roadCount == 0) return;

        //money = money + 10;
        //textComp.text = money.ToString();
        AddMoney(10, MoneySource.Store);
        --roadManager.roadCount;
    }

    public int GetErpCost()
    {
        return erpCost;
    }
    public void BuyErp()
    {
        //money -= erpCost;
        //textComp.text = money.ToString();
        MinusMoney(erpCost, MoneySource.Store);
        ++roadManager.erpManager.erpCount;
        ++erpBuyCount;
        erpCost += (erpBuyCount * 10);
       
    }
    public void SellErp()
    {
        if (roadManager.erpManager.erpCount == 0) return;

        //money = money + 10;
        //textComp.text = money.ToString();
        AddMoney(10, MoneySource.Store);
        --roadManager.erpManager.erpCount;
    }

    public int GetTLCost()
    {
        return tlCost;
    }
    public void BuyTrafficLight()
    {
        //money -= tlCost;
        //textComp.text = money.ToString();
        MinusMoney(tlCost, MoneySource.Store);
        ++roadManager.trafficLightManager.tlCount;
        ++tlBuyCount;
        tlCost += (int)(tlBuyCount * 10);
       
    }
    public void SellTL()
    {
        if (roadManager.trafficLightManager.tlCount == 0) return;

        //money += 25;
        //textComp.text = money.ToString();
        AddMoney(25, MoneySource.Store);
        --roadManager.trafficLightManager.tlCount;
    }

}

