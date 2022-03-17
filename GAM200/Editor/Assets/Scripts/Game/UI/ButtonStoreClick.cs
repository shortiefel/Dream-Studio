using System;

public class ButtonStoreClick : MonoBehaviour
{

    StoreButtonType st;
    public MoneySystem moneySystem;

    public bool state;
    //public Animation animation;
    // GameState gameState;

    Text CostRoad;
    Text CostTL;
    Text CostERP;

    ButtonStore buttonStore;

    public override void Start()
    {

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();

        state = false;
        //animation = GetComponent<Animation>();

        CostRoad = GameObject.Find("RoadCost").GetComponent<Text>();
        CostTL = GameObject.Find("TrafficCost").GetComponent<Text>();
        CostERP = GameObject.Find("ERPCost").GetComponent<Text>();

        if (entityId == GameObject.Find("RoadPlus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.RoadBuy;
        }
        else if (entityId == GameObject.Find("RoadMinus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.RoadSell;
        }
        else if (entityId == GameObject.Find("TrafficMinus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.TrafficSell;
        }
        else if (entityId == GameObject.Find("TrafficPlus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.TrafficBuy;
        }
        else if (entityId == GameObject.Find("ERPMinus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPSell;
        }
        else if (entityId == GameObject.Find("ERPPlus").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.ERPBuy;
        }
        else if (entityId == GameObject.Find("StoreCloseButton").GetComponent<Transform>().entityId)
        {
            st = StoreButtonType.CloseStore;
        }

        CostRoad.text = moneySystem.roadCost.ToString();
        CostERP.text = moneySystem.erpCost.ToString();
        CostTL.text = moneySystem.tlCost.ToString();

        buttonStore = GameObject.Find("Storebtn").GetComponent<ButtonStore>();
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

            case StoreButtonType.RoadBuy:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {

                        //moneySystem.BuyRoad();
                        CostRoad.text = moneySystem.roadCost.ToString();

                        if (moneySystem.GetMoney() >= 20)
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