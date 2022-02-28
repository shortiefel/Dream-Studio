using System;

public enum StoreButtonType
{
    RoadBuy = 1,
    RoadSell,
    TrafficBuy,
    TrafficSell,
    ERPBuy,
    ERPSell
}

public class ButtonStore : MonoBehaviour
{
    bool StoreButtonType;

    GameObject StoreHeader;
    GameObject ItemHeader;
    GameObject QtyHeader;

    GameObject RoadIcon;
    GameObject RoadBuy;
    GameObject RoadSell;
    GameObject RoadNo;

    GameObject TrafficIcon;
    GameObject TrafficBuy;
    GameObject TrafficSell;
    GameObject TrafficNo;

    GameObject ERPIcon;
    GameObject ERPBuy;
    GameObject ERPSell;
    GameObject ERPNo;

    GameObject Storebtn;
    GameObject StoreBG;

    Vector2 bgPosition;
    Vector2 hStorePosition;
    Vector2 hItemPosition;
    Vector2 hQtyPosition;
    Vector2 rIconPosition;
    Vector2 rAddPosition;
    Vector2 rMinusPosition;
    Vector2 rNoPosition;
    Vector2 tIconPosition;
    Vector2 tAddPosition;
    Vector2 tMinusPosition;
    Vector2 tNoPosition;
    Vector2 eIconPosition;
    Vector2 eAddPosition;
    Vector2 eMinusPosition;
    Vector2 eNoPosition;

    GameState gameState;
    bool stopTime;
    float stopTimer;

    UI texture;

    public override void Start()
    {
        texture = GetComponent<UI>();

        Storebtn = GameObject.Find("Storebtn");
        StoreBG = GameObject.Find("StoreBG");
        bgPosition = StoreBG.transform.position;

        StoreHeader = GameObject.Find("StoreTitle");
        ItemHeader = GameObject.Find("ItemTitle");
        QtyHeader = GameObject.Find("QuantityTitle");

        hStorePosition = StoreHeader.transform.position;
        hItemPosition = ItemHeader.transform.position;
        hQtyPosition = QtyHeader.transform.position;

        RoadIcon = GameObject.Find("RoadCart");
        RoadBuy = GameObject.Find("Roadadd");
        RoadSell = GameObject.Find("Roadminus");
        RoadNo = GameObject.Find("RoadQty");

        rIconPosition = RoadIcon.transform.position;
        rAddPosition = RoadBuy.transform.position;
        rMinusPosition = RoadSell.transform.position;
        rNoPosition = RoadNo.transform.position;

        TrafficIcon = GameObject.Find("TrafficCart");
        TrafficBuy = GameObject.Find("Trafficadd");
        TrafficSell = GameObject.Find("Trafficminus");
        TrafficNo = GameObject.Find("TrafficQty");

        tIconPosition = TrafficIcon.transform.position;
        tAddPosition = TrafficBuy.transform.position;
        tMinusPosition = TrafficSell.transform.position;
        tNoPosition = TrafficNo.transform.position;

        ERPIcon = GameObject.Find("ERPCart");
        ERPBuy = GameObject.Find("ERPadd");
        ERPSell = GameObject.Find("ERPminus");
        ERPNo = GameObject.Find("ERPQty");

        eIconPosition = ERPIcon.transform.position;
        eAddPosition = ERPBuy.transform.position;
        eMinusPosition = ERPSell.transform.position;
        eNoPosition = ERPNo.transform.position;


        Disable<Transform>(StoreBG.transform);
        Disable<Transform>(StoreHeader.transform);
        Disable<Transform>(ItemHeader.transform);
        Disable<Transform>(QtyHeader.transform);
        Disable<Transform>(RoadIcon.transform);
        Disable<Transform>(RoadBuy.transform);
        Disable<Transform>(RoadSell.transform);
        Disable<Transform>(RoadNo.transform);
        Disable<Transform>(TrafficIcon.transform);
        Disable<Transform>(TrafficBuy.transform);
        Disable<Transform>(TrafficSell.transform);
        Disable<Transform>(TrafficNo.transform);
        Disable<Transform>(ERPIcon.transform);
        Disable<Transform>(ERPBuy.transform);
        Disable<Transform>(ERPSell.transform);
        Disable<Transform>(ERPNo.transform);


        stopTime = false;
        stopTimer = 0f;

        //StoreBG.transform.position = new Vector2(bgPosition.x + 200f, StoreBG.transform.position.y);

    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Enable<Transform>(StoreBG.transform);
            Enable<Transform>(StoreBG.transform);
            Enable<Transform>(StoreHeader.transform);
            Enable<Transform>(ItemHeader.transform);
            Enable<Transform>(QtyHeader.transform);
            Enable<Transform>(RoadIcon.transform);
            Enable<Transform>(RoadBuy.transform);
            Enable<Transform>(RoadSell.transform);
            Enable<Transform>(RoadNo.transform);
            Enable<Transform>(TrafficIcon.transform);
            Enable<Transform>(TrafficBuy.transform);
            Enable<Transform>(TrafficSell.transform);
            Enable<Transform>(TrafficNo.transform);
            Enable<Transform>(ERPIcon.transform);
            Enable<Transform>(ERPBuy.transform);
            Enable<Transform>(ERPSell.transform);
            Enable<Transform>(ERPNo.transform);


        }
    }

    public override void OnMouseExit()
    {
        texture.color = new Color(0f, 0f, 0f);
    }

}


