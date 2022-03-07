using System;

public class ButtonStoreClick : MonoBehaviour
{

    StoreButtonType st;
    public MoneySystem moneySystem;

   // GameState gameState;

    public override void Start()
    {

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();


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
                        moneySystem.BuyErp();
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
                        moneySystem.BuyTrafficLight();

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