using System;

public class ButtonStoreClick : MonoBehaviour
{

    StoreButtonType st;

    //Text RoadNo;
    //Text TrafficNo;
    //Text ERPNo;


    //Text RoadNoDisplay;


    //public int RoadText;
    //public int TrafficText;
    //public int ERPText;

    //RoadManager roadManager;
    public MoneySystem moneySystem;


    int currMoney;
    int tl;

    public override void Start()
    {

        //RoadText = 0;
        //TrafficText = 0;
        //ERPText = 0;

        //RoadNoDisplay = GameObject.Find("currRoadDisplay").GetComponent<Text>();
        //GameObject go = GameObject.Find("MoneyText");
        //if (go != null)
        //moneySystem = go.GetComponent<MoneySystem>();

        //roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();
        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();

        //RoadNo = GameObject.Find("RoadQty").GetComponent<Text>();
        //TrafficNo = GameObject.Find("TrafficQty").GetComponent<Text>();
        //ERPNo = GameObject.Find("ERPQty").GetComponent<Text>();

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

    }

    public override void OnMouseOver()
    {
        switch (st)
        {
            case StoreButtonType.RoadBuy:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {

                        moneySystem.BuyRoad();
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
                        //--roadManager.roadCount;
                        //RoadNo.text = roadManager.currRoad.ToString();
                    }

                    break;
                }
            case StoreButtonType.ERPBuy:
                {

                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.BuyErp();
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
                        //--roadManager.erpManager.erpCount;
                        //ERPNo.text = ERPText.ToString();
                    }

                    break;
                }

            case StoreButtonType.TrafficBuy:
                {

                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        moneySystem.BuyTrafficLight();
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
                        //--roadManager.trafficLightManager.tlCount;
                        //TrafficNo.text = TrafficText.ToString();
                    }

                    break;
                }
        }
    }

}