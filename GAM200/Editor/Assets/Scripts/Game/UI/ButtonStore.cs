public enum StoreButtonType
{
    RoadPlus = 1,
    RoadMinus,
    RoadBuy,
    RoadSell,
    Roadx1,
    Roadx10,
    TrafficPlus,
    TrafficMinus,
    TrafficBuy,
    TrafficSell,
    Trafficx1,
    Trafficx10,
    ERPPlus,
    ERPMinus,
    ERPBuy,
    ERPSell,
    ERPx1,
    ERPx10,
    CloseStore
}

public class ButtonStore : MonoBehaviour
{
    bool StoreButtonType;

    GameObject StoreHeader;
    GameObject ItemHeader;
    GameObject QtyHeader;

    GameObject RoadIcon;
    GameObject RoadPlus;
    GameObject RoadMinus;
    GameObject RoadNo;
    GameObject RoadBuy;
    GameObject RoadSell;
    GameObject Roadx1;
    GameObject Roadx10;

    GameObject TrafficIcon;
    GameObject TrafficPlus;
    GameObject TrafficMinus;
    GameObject TrafficNo;
    GameObject TrafficBuy;
    GameObject TrafficSell;
    GameObject Trafficx1;
    GameObject Trafficx10;

    GameObject ERPIcon;
    GameObject ERPPlus;
    GameObject ERPMinus;
    GameObject ERPNo;
    GameObject ERPBuy;
    GameObject ERPSell;
    GameObject ERPx1;
    GameObject ERPx10;

    //GameObject Storebtn;
    GameObject StoreBG;
    //GameObject StoreBack;

    GameObject CostTitle;
    GameObject RoadCost;
    GameObject TLCost;
    GameObject ERPCost;

    //GameObject Roadbuy;
    //GameObject Trafficbuy;
    //GameObject ERPbuy;

    //Vector2 roadBuyPosition;
    //Vector2 trafficBuyPosition;
    //Vector2 ERPBuyPosition;


    Vector2 bgPosition;
    Vector2 hStorePosition;
    Vector2 hItemPosition;
    Vector2 hQtyPosition;
    Vector2 rIconPosition;
    Vector2 rAddPosition;
    Vector2 rMinusPosition;
    Vector2 rNoPosition;
    Vector2 rBuyPosition;
    Vector2 rSellPosition;
    Vector2 rx1Position;
    Vector2 rx10Position;
    Vector2 tIconPosition;
    Vector2 tAddPosition;
    Vector2 tMinusPosition;
    Vector2 tNoPosition;
    Vector2 tBuyPosition;
    Vector2 tSellPosition;
    Vector2 tx1Position;
    Vector2 tx10Position;
    Vector2 eIconPosition;
    Vector2 eAddPosition;
    Vector2 eMinusPosition;
    Vector2 eNoPosition;
    Vector2 eBuyPosition;
    Vector2 eSellPosition;
    Vector2 ex1Position;
    Vector2 ex10Position;
    //Vector2 sBackPosition;

    Vector2 hCostPosition;
    Vector2 roadCostPosition;
    Vector2 tlCostPosition;
    Vector2 erpCostPosition;

    //bool stopTime;
    //float stopTimer;

    GameState gameState;


    Transform displayArrow;
    Transform displayArrowWhite;
    Transform timerButton;
    Transform pauseIcon;

    Transform moneyText;
    Transform roadCount;

    UI texture;

    CombinedUI combinedUI;

    public bool revealCartButton;
    public bool closing;

    Transform storeIntro;

    Transform storeClose;
    public MoneySystem moneySystem;

    public override void Start()
    {

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();
        storeClose = GameObject.Find("StoreCloseButton").GetComponent<Transform>();

        roadCount = GameObject.Find("currRoadDisplay").GetComponent<Transform>();

        GameObject go3 = GameObject.Find("MoneyText");
        if (go3 != null)
            moneyText = go3.GetComponent<Transform>();

        revealCartButton = false;
        GameObject go = GameObject.Find("StoreIntro");
        if (go != null)
            storeIntro = go.GetComponent<Transform>();

        if (storeIntro != null)
            Disable<Transform>(storeIntro);

        closing = false;


        texture = GetComponent<UI>();
        //texture.color = new Color(0f, 0f, 0f);

        //Storebtn = GameObject.Find("Storebtn");
        StoreBG = GameObject.Find("StoreBG");
        //StoreBack = GameObject.Find("BackToGame");

        bgPosition = StoreBG.transform.position;
        //sBackPosition = StoreBack.transform.position;

        StoreHeader = GameObject.Find("StoreTitle");
        ItemHeader = GameObject.Find("ItemTitle");
        QtyHeader = GameObject.Find("QuantityTitle");

        hStorePosition = StoreHeader.transform.position;
        hItemPosition = ItemHeader.transform.position;
        hQtyPosition = QtyHeader.transform.position;

        RoadIcon = GameObject.Find("RoadCart");
        RoadPlus = GameObject.Find("RoadPlus");
        RoadMinus = GameObject.Find("RoadMinus");
        RoadNo = GameObject.Find("RoadQty");
        RoadBuy = GameObject.Find("RoadBuy");
        RoadSell = GameObject.Find("RoadSell");
        Roadx1 = GameObject.Find("Roadx1");
        Roadx10 = GameObject.Find("Roadx10");

        rIconPosition = RoadIcon.transform.position;
        rAddPosition = RoadPlus.transform.position;
        rMinusPosition = RoadMinus.transform.position;
        rNoPosition = RoadNo.transform.position;
        rBuyPosition = RoadBuy.transform.position;
        rSellPosition = RoadSell.transform.position;
        rx1Position = Roadx1.transform.position;
        rx10Position = Roadx10.transform.position;

        TrafficIcon = GameObject.Find("TrafficCart");
        TrafficPlus = GameObject.Find("TrafficPlus");
        TrafficMinus = GameObject.Find("TrafficMinus");
        TrafficNo = GameObject.Find("TrafficQty");
        TrafficBuy = GameObject.Find("TrafficBuy");
        TrafficSell = GameObject.Find("TrafficSell");
        Trafficx1 = GameObject.Find("Trafficx1");
        Trafficx10 = GameObject.Find("Trafficx10");

        tIconPosition = TrafficIcon.transform.position;
        tAddPosition = TrafficPlus.transform.position;
        tMinusPosition = TrafficMinus.transform.position;
        tNoPosition = TrafficNo.transform.position;
        tBuyPosition = TrafficBuy.transform.position;
        tSellPosition = TrafficSell.transform.position;
        tx1Position = Trafficx1.transform.position;
        tx10Position = Trafficx10.transform.position;

        ERPIcon = GameObject.Find("ERPCart");
        ERPPlus = GameObject.Find("ERPPlus");
        ERPMinus = GameObject.Find("ERPMinus");
        ERPNo = GameObject.Find("ERPQty");
        ERPBuy = GameObject.Find("ERPBuy");
        ERPSell = GameObject.Find("ERPSell");
        ERPx1 = GameObject.Find("ERPx1");
        ERPx10 = GameObject.Find("ERPx10");

        eIconPosition = ERPIcon.transform.position;
        eAddPosition = ERPPlus.transform.position;
        eMinusPosition = ERPMinus.transform.position;
        eNoPosition = ERPNo.transform.position;
        eBuyPosition = ERPBuy.transform.position;
        eSellPosition = ERPSell.transform.position;
        ex1Position = ERPx1.transform.position;
        ex10Position = ERPx10.transform.position;

        gameState = GameObject.Find("GameManager").GetComponent<GameState>();


        displayArrow = GameObject.Find("Displaybtn").GetComponent<Transform>();
        displayArrowWhite = GameObject.Find("DisplaybtnWhite").GetComponent<Transform>();
        timerButton = GameObject.Find("TimerIcon").GetComponent<Transform>();
        pauseIcon = GameObject.Find("PauseIcon").GetComponent<Transform>();



        CostTitle = GameObject.Find("CostTitle");
        hCostPosition = CostTitle.transform.position;

        RoadCost = GameObject.Find("RoadCost");
        TLCost = GameObject.Find("TrafficCost");
        ERPCost = GameObject.Find("ERPCost");

        roadCostPosition = RoadCost.transform.position;
        tlCostPosition = TLCost.transform.position;
        erpCostPosition = ERPCost.transform.position;

        Disable<Transform>(storeClose);

        //Disable<Transform>(Storebtn.transform);
        Disable<Transform>(StoreBG.transform);
        //Disable<Transform>(StoreBack.transform);
        Disable<Transform>(StoreHeader.transform);
        Disable<Transform>(ItemHeader.transform);
        Disable<Transform>(QtyHeader.transform);
        Disable<Transform>(RoadIcon.transform);
        Disable<Transform>(RoadPlus.transform);
        Disable<Transform>(RoadMinus.transform);
        Disable<Transform>(RoadNo.transform);
        Disable<Transform>(RoadBuy.transform);
        Disable<Transform>(RoadSell.transform);
        Disable<Transform>(Roadx1.transform);
        Disable<Transform>(Roadx10.transform);

        Disable<Transform>(TrafficIcon.transform);
        Disable<Transform>(TrafficPlus.transform);
        Disable<Transform>(TrafficMinus.transform);
        Disable<Transform>(TrafficNo.transform);
        Disable<Transform>(TrafficBuy.transform);
        Disable<Transform>(TrafficSell.transform);
        Disable<Transform>(Trafficx1.transform);
        Disable<Transform>(Trafficx10.transform);

        Disable<Transform>(ERPIcon.transform);
        Disable<Transform>(ERPPlus.transform);
        Disable<Transform>(ERPMinus.transform);
        Disable<Transform>(ERPNo.transform);
        Disable<Transform>(ERPBuy.transform);
        Disable<Transform>(ERPSell.transform);
        Disable<Transform>(ERPx1.transform);
        Disable<Transform>(ERPx10.transform);

        Disable<Transform>(RoadCost.transform);
        Disable<Transform>(TLCost.transform);
        Disable<Transform>(ERPCost.transform);




        combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();

        texture.color = new Color(1f, 1f, 1f);
    }

    public void SwitchTabStore(bool type, bool reenable = true)
    {
        if (type)
        {
            gameState.SetAllowPause(false);
            //if (revealCartButton == true)
            {
                Enable<Transform>(StoreBG.transform);
                //Enable<Transform>(StoreBack.transform);
                Enable<Transform>(RoadPlus.transform);
                Enable<Transform>(RoadMinus.transform);
                Enable<Transform>(RoadNo.transform);
                Enable<Transform>(RoadBuy.transform);
                Enable<Transform>(RoadSell.transform);
                Enable<Transform>(Roadx1.transform);
                Enable<Transform>(Roadx10.transform);
            }

            if (combinedUI.buttonRoad.revealTrafficButton)
            {
                //Enable<Transform>(TrafficIcon.transform);
                Enable<Transform>(TrafficPlus.transform);
                Enable<Transform>(TrafficMinus.transform);
                Enable<Transform>(TrafficNo.transform);
                Enable<Transform>(TrafficBuy.transform);
                Enable<Transform>(TrafficSell.transform);
                Enable<Transform>(TLCost.transform);
                Enable<Transform>(Trafficx1.transform);
                Enable<Transform>(Trafficx10.transform);
            }

            if (combinedUI.buttonRoad.revealERPButton)
            {
                //Enable<Transform>(ERPIcon.transform);
                Enable<Transform>(ERPPlus.transform);
                Enable<Transform>(ERPMinus.transform);
                Enable<Transform>(ERPNo.transform);
                Enable<Transform>(ERPBuy.transform);
                Enable<Transform>(ERPSell.transform);
                Enable<Transform>(ERPCost.transform);
                Enable<Transform>(ERPx1.transform);
                Enable<Transform>(ERPx10.transform);
            }

            //Enable<Transform>(CostTitle.transform);
            Enable<Transform>(RoadCost.transform);



            Enable<Transform>(storeClose);
            Disable<Transform>(transform);
            //stopTime = true;

            //Disable<Transform>(Storebtn.transform);
            //Enable<Transform>(StoreBack.transform);


            //Disable<Transform>(pauseIcon);
            //
            //Disable<Transform>(timerButton);
            //
            //Time.timeScale = 0f;

            if (combinedUI != null)
                combinedUI.CloseAllUIExcept(UIType.Store);
        }
        else
        {
            gameState.SetAllowPause(true);

            Disable<Transform>(StoreBG.transform);
            Disable<Transform>(StoreHeader.transform);
            Disable<Transform>(ItemHeader.transform);
            Disable<Transform>(QtyHeader.transform);
            Disable<Transform>(RoadIcon.transform);
            Disable<Transform>(RoadPlus.transform);
            Disable<Transform>(RoadMinus.transform);
            Disable<Transform>(RoadNo.transform);
            Disable<Transform>(RoadBuy.transform);
            Disable<Transform>(RoadSell.transform);
            Disable<Transform>(Roadx1.transform);
            Disable<Transform>(Roadx10.transform);

            Disable<Transform>(TrafficIcon.transform);
            Disable<Transform>(TrafficPlus.transform);
            Disable<Transform>(TrafficMinus.transform);
            Disable<Transform>(TrafficNo.transform);
            Disable<Transform>(TrafficBuy.transform);
            Disable<Transform>(TrafficSell.transform);
            Disable<Transform>(Trafficx1.transform);
            Disable<Transform>(Trafficx10.transform);

            Disable<Transform>(ERPIcon.transform);
            Disable<Transform>(ERPPlus.transform);
            Disable<Transform>(ERPMinus.transform);
            Disable<Transform>(ERPNo.transform);
            Disable<Transform>(ERPBuy.transform);
            Disable<Transform>(ERPSell.transform);
            Disable<Transform>(ERPx1.transform);
            Disable<Transform>(ERPx10.transform);

            if (reenable)
            {
                Enable<Transform>(displayArrow);
                Enable<Transform>(timerButton);
                Enable<Transform>(pauseIcon);

                if (combinedUI != null)
                    combinedUI.EnableAllMasterButton();

                Enable<Transform>(transform);
            }

            Disable<Transform>(CostTitle.transform);
            Disable<Transform>(RoadCost.transform);
            Disable<Transform>(TLCost.transform);
            Disable<Transform>(ERPCost.transform);

            Disable<Transform>(storeClose);
            
            //Enable<Transform>(Storebtn.transform);
            //Disable<Transform>(StoreBack.transform);
        }
    }
   

    public void StoreAction()
    {
         //Debug.Log("Store");
         //gameState.InvertPause();
         bool state = !gameState.GetPause();
         gameState.SetPause(state);
         SwitchTabStore(state);
    }

    public override void Update()
    {

        if(!moneySystem.get_r_bool())
        {
            Roadx1.GetComponent<UI>().ChangeTexture("Game/Store/x1Btn_Dark");
            Roadx10.GetComponent<UI>().ChangeTexture("Game/Store/x10Btn");
        }
        else
        {
            Roadx1.GetComponent<UI>().ChangeTexture("Game/Store/x1Btn");
            Roadx10.GetComponent<UI>().ChangeTexture("Game/Store/x10Btn_Dark");
        }
        if(!moneySystem.get_tl_bool())
        {
            Trafficx1.GetComponent<UI>().ChangeTexture("Game/Store/x1Btn_Dark");
            Trafficx10.GetComponent<UI>().ChangeTexture("Game/Store/x10Btn");
        }
        else
        {
            Trafficx1.GetComponent<UI>().ChangeTexture("Game/Store/x1Btn");
            Trafficx10.GetComponent<UI>().ChangeTexture("Game/Store/x10Btn_Dark");
        }
        if(!moneySystem.get_erp_bool())
        {
            ERPx1.GetComponent<UI>().ChangeTexture("Game/Store/x1Btn_Dark");
            ERPx10.GetComponent<UI>().ChangeTexture("Game/Store/x10Btn");
        }
        else
        {
            ERPx1.GetComponent<UI>().ChangeTexture("Game/Store/x1Btn");
            ERPx10.GetComponent<UI>().ChangeTexture("Game/Store/x10Btn_Dark");
        }

    }


    public override void OnMouseEnter()
    {
        texture.ChangeTexture("Game/Store/Store_Hover");
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            StoreAction();

        }
    }

    public override void OnMouseExit()
    {
        texture.ChangeTexture("Game/Store/Store");
    }

    internal void ResumeAction()
    {
        StoreAction();
    }

    public void RevealStore()
    {
        revealCartButton = true;
        //Enable<Transform>(Storebtn.transform);
        Enable<Transform>(storeIntro);

        Disable<Transform>(moneyText);
        Disable<Transform>(roadCount);
        Debug.Log("Revealing store ");

        closing = true;
        Time.timeScale = 0f;

        combinedUI.CloseAllUIExcept(UIType.None);
        Disable<Transform>(GameObject.Find("stringname").GetComponent<Transform>());
    }
}


