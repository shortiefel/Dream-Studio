using System;

public class ButtonStoreClick : MonoBehaviour
{

    StoreButtonType st;
    public MoneySystem moneySystem;

    // GameState gameState;

    Text CostRoad;
    Text CostTL;
    Text CostERP;

    public override void Start()
    {

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();

        CostRoad = GameObject.Find("RoadCost").GetComponent<Text>();
        CostTL = GameObject.Find("TrafficCost").GetComponent<Text>();
        CostERP = GameObject.Find("ERPCost").GetComponent<Text>();

        if (entityId == GameObject.Find("Roadadd").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.RoadBuy;
        }
        else if (entityId == GameObject.Find("Roadminus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.RoadSell;
        }
        else if (entityId == GameObject.Find("Trafficminus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.TrafficSell;
        }
        else if (entityId == GameObject.Find("Trafficadd").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.TrafficBuy;
        }
        else if (entityId == GameObject.Find("ERPminus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPSell;
        }
        else if (entityId == GameObject.Find("ERPadd").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPBuy;
        }
        else if (entityId == GameObject.Find("BackToGame").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.BackToGame;
        }

        CostRoad.text = moneySystem.roadCost.ToString();
        CostERP.text = moneySystem.erpCost.ToString();
        CostTL.text = moneySystem.tlCost.ToString();

    }

    public override void OnMouseOver()
    {
        switch (st)
        {


            case StoreButtonType.RoadBuy:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {

                        //moneySystem.BuyRoad();
                        CostRoad.text = moneySystem.roadCost.ToString();

                        if (moneySystem.GetMoney() >= 10)
                        {
                            moneySystem.BuyRoad();
                        }
                        //++roadManager.roadCount;
                        //RoadNo.text = roadManager.currRoad.ToString();
                    }

                    break;
                }

            case StoreButtonType.RoadSell:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.SellRoad();
                   
                    }

                    break;
                }
            case StoreButtonType.ERPBuy:
                {

                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        //moneySystem.BuyErp();
                   
                        if(moneySystem.GetMoney() >= moneySystem.GetErpCost())
                        {
                            moneySystem.BuyErp();
                        }
                        CostERP.text = moneySystem.erpCost.ToString();

                        //++roadManager.erpManager.erpCount;
                        //ERPNo.text = ERPText.ToString();
                    }

                    break;
                }

            case StoreButtonType.ERPSell:
                {

                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.SellErp();
         
                    }

                    break;
                }

            case StoreButtonType.TrafficBuy:
                {

                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        //moneySystem.BuyTrafficLight();

                        if (moneySystem.GetMoney() >= moneySystem.GetTLCost())
                        {
                            moneySystem.BuyTrafficLight();

                        }
                        CostTL.text = moneySystem.tlCost.ToString();

                        //++roadManager.trafficLightManager.tlCount;
                        //TrafficNo.text = TrafficText.ToString();
                    }

                    break;
                }

            case StoreButtonType.TrafficSell:
                {

                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.SellTL();

                    }

                    break;
                }
        }
    }

}