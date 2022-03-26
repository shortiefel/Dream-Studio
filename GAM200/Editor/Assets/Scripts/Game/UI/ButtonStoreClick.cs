using System;

public class ButtonStoreClick : MonoBehaviour
{

    StoreButtonType st;
    public MoneySystem moneySystem;

    public bool state;


    Text CostRoad;
    Text CostTL;
    Text CostERP;

    Text storeRoadText;
    Text storeTrafficText;
    Text storeERPText;

    ButtonStore buttonStore;
    RoadManager roadManager;
    ERPManager erpManager;
    TrafficLightManager trafficLightManager;

    public override void Start()
    {

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();
        state = false;

        roadPlus = GameObject.Find("RoadPlus").GetComponent<ButtonStoreClick>();
        CostRoad = GameObject.Find("RoadCost").GetComponent<Text>();
        CostTL = GameObject.Find("TrafficCost").GetComponent<Text>();
        CostERP = GameObject.Find("ERPCost").GetComponent<Text>();

        storeRoadText = GameObject.Find("RoadQty").GetComponent<Text>();
        storeTrafficText = GameObject.Find("TrafficQty").GetComponent<Text>();
        storeERPText = GameObject.Find("ERPQty").GetComponent<Text>();

        if (entityId == GameObject.Find("RoadPlus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.RoadPlus;
        }
        else if (entityId == GameObject.Find("RoadMinus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.RoadMinus;
        }
        else if (entityId == GameObject.Find("RoadBuy").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.RoadBuy;
        }
        else if (entityId == GameObject.Find("RoadSell").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.RoadSell;
        }
        else if (entityId == GameObject.Find("Roadx1").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.Roadx1;
        }
        else if (entityId == GameObject.Find("Roadx10").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.Roadx10;
        }
        else if (entityId == GameObject.Find("TrafficPlus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.TrafficPlus;
        }
        else if (entityId == GameObject.Find("TrafficMinus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.TrafficMinus;
        }
        else if (entityId == GameObject.Find("TrafficBuy").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.TrafficBuy;
        }
        else if (entityId == GameObject.Find("TrafficSell").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.TrafficSell;
        }
        else if (entityId == GameObject.Find("Trafficx1").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.Trafficx1;
        }
        else if (entityId == GameObject.Find("Trafficx10").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.Trafficx10;
        }
        else if (entityId == GameObject.Find("ERPPlus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPPlus;
        }
        else if (entityId == GameObject.Find("ERPMinus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPMinus;
        }
        else if (entityId == GameObject.Find("ERPBuy").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPBuy;
        }
        else if (entityId == GameObject.Find("ERPSell").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPSell;
        }
        else if (entityId == GameObject.Find("ERPx1").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPx1;
        }
        else if (entityId == GameObject.Find("ERPx10").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPx10;
        }
        else if (entityId == GameObject.Find("StoreCloseButton").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.CloseStore;
        }

        CostRoad.text = "0";// moneySystem.roadCost.ToString();
        CostERP.text = "0"; //moneySystem.erpCost.ToString();
        CostTL.text = "0"; //moneySystem.tlCost.ToString();

        buttonStore = GameObject.Find("Storebtn").GetComponent<ButtonStore>();

        GameObject go = GameObject.Find("RoadManager");
        if (go != null)
            roadManager = go.GetComponent<RoadManager>();
        GameObject go2 = GameObject.Find("ERPManager");
        if (go2 != null)
            erpManager = go2.GetComponent<ERPManager>();

        GameObject go3 = GameObject.Find("TrafficManager");
        if (go3 != null)
            trafficLightManager = go3.GetComponent<TrafficLightManager>();
    }

    public override void OnMouseOver()
    {
        switch (st)
        {
            case StoreButtonType.CloseStore:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        buttonStore.StoreAction();
                    }

                    break;
                }
            case StoreButtonType.Roadx1:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.road_bool = false;
                    }
                    break;
                }
            case StoreButtonType.Roadx10:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.road_bool = true;
                    }
                    break;
                }
            case StoreButtonType.RoadPlus:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if(moneySystem.get_r_bool())
                        {
                            moneySystem.road_counter += 10;
                        }
                        else
                        {
                            moneySystem.road_counter++;
                        }
                        CostRoad.text = (moneySystem.road_count() * 20).ToString();
                    }
                    storeRoadText.text = moneySystem.road_count().ToString();
                    break;
                }
            case StoreButtonType.RoadMinus:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if (moneySystem.road_counter > 0)
                        {
                            if (moneySystem.get_r_bool() && moneySystem.road_counter >= 10)
                            {
                                moneySystem.road_counter -= 10;
                            }
                            else if(moneySystem.get_r_bool() && moneySystem.road_counter < 10)
                            {
                                moneySystem.road_counter = 0;
                            }
                            else
                            {
                                moneySystem.road_counter--;
                            }
                            CostRoad.text = (moneySystem.road_count() * 20).ToString();
                        }
                    }
                    storeRoadText.text = moneySystem.road_count().ToString();
                    break;
                }
            case StoreButtonType.RoadBuy:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if((moneySystem.road_count() > 0 ) && (moneySystem.road_count() * 20) < moneySystem.GetMoney())
                        {
                            moneySystem.BuyRoad(moneySystem.road_count());
                            moneySystem.road_counter = 0;
                        }
                        CostRoad.text = (moneySystem.road_count() * 20).ToString();

                    }
                    storeRoadText.text = moneySystem.road_count().ToString();
                    break;
                }
            case StoreButtonType.RoadSell:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if(roadManager.roadCount >= moneySystem.road_counter)
                        {
                            moneySystem.SellRoad(moneySystem.road_counter);
                            moneySystem.road_counter = 0;
                            CostRoad.text = (moneySystem.road_count() * 20).ToString();
                        }
                    }
                    storeRoadText.text = moneySystem.road_count().ToString();
                    break;
                }
            case StoreButtonType.ERPx1:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.erp_bool = false;
                    }
                    break;
                }
            case StoreButtonType.ERPx10:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.erp_bool = true;
                    }
                    break;
                }
            case StoreButtonType.ERPPlus:
                {

                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if (moneySystem.get_erp_bool())
                        {
                            moneySystem.erp_counter += 10;
                        }
                        else
                        {
                            moneySystem.erp_counter++;
                        }
                        CostERP.text = moneySystem.calculateerp_cost().ToString();
                    }
                    storeERPText.text = moneySystem.erp_count().ToString();
                    break;
                }
            case StoreButtonType.ERPMinus:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if(moneySystem.erp_counter > 0)
                        {
                            if (moneySystem.get_erp_bool() && moneySystem.erp_counter >= 10)
                            {
                                moneySystem.erp_counter -= 10;
                            }
                            else if (moneySystem.get_erp_bool() && moneySystem.erp_counter < 10)
                            {
                                moneySystem.erp_counter = 0;
                            }
                            else
                            {
                                moneySystem.erp_counter--;
                            }
                            CostERP.text = moneySystem.calculateerp_cost().ToString();
                        }
                    }
                    storeERPText.text = moneySystem.erp_count().ToString();
                    break;
                }
            case StoreButtonType.ERPBuy:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if (moneySystem.calculateerp_cost() <= moneySystem.money)
                        {
                            moneySystem.BuyErp(moneySystem.erp_count());
                            moneySystem.erp_counter = 0;
                        }
                        CostERP.text = moneySystem.calculateerp_cost().ToString();
                    }
                    storeERPText.text = moneySystem.erp_count().ToString();
                    break;
                }
            case StoreButtonType.ERPSell:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if(erpManager.erpCount >= moneySystem.erp_counter)
                        {
                            moneySystem.SellErp(moneySystem.erp_counter);
                            moneySystem.erp_counter = 0;
                            CostERP.text = (moneySystem.erp_count() * 20).ToString();
                        }
                    }
                    storeRoadText.text = moneySystem.road_count().ToString();
                    break;
                }
            case StoreButtonType.Trafficx1:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.traffic_bool = false;
                    }
                    break;
                }
            case StoreButtonType.Trafficx10:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.traffic_bool = true;
                    }
                    break;
                }
            case StoreButtonType.TrafficPlus:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if (moneySystem.get_tl_bool())
                        {
                            moneySystem.traffic_counter += 10;
                        }
                        else
                        {
                            moneySystem.traffic_counter++;
                        }
                        CostTL.text = moneySystem.calculatetl_cost().ToString();

                    }
                    storeTrafficText.text = moneySystem.tl_count().ToString();
                    break;
                }
            case StoreButtonType.TrafficMinus:
                {

                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if(moneySystem.traffic_counter > 0)
                        {
                            if (moneySystem.get_tl_bool() && moneySystem.traffic_counter >= 10)
                            {
                                moneySystem.traffic_counter -= 10;
                            }
                            else if (moneySystem.get_tl_bool() && moneySystem.traffic_counter < 10)
                            {
                                moneySystem.traffic_counter = 0;
                            }
                            else
                            {
                                moneySystem.traffic_counter--;
                            }
                            CostTL.text = moneySystem.calculatetl_cost().ToString();
                        }
                    }
                    storeTrafficText.text = moneySystem.tl_count().ToString();
                    break;
                }
            case StoreButtonType.TrafficBuy:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if (moneySystem.calculatetl_cost() <= moneySystem.money)
                        {
                            moneySystem.BuyTrafficLight(moneySystem.tl_count());
                            moneySystem.traffic_counter = 0;
                        }
                        CostTL.text = moneySystem.calculatetl_cost().ToString();
                    }
                    storeTrafficText.text = moneySystem.tl_count().ToString();
                    
                    break;
                }
            case StoreButtonType.TrafficSell:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        if(trafficLightManager.tlCount >= moneySystem.traffic_counter)
                        {
                            moneySystem.SellTL(moneySystem.traffic_counter);
                            moneySystem.traffic_counter = 0;
                            CostTL.text = (moneySystem.tl_count() * 20).ToString();
                        }
                    }
                    storeRoadText.text = moneySystem.road_count().ToString();
                    break;
                }
        }
    }

}