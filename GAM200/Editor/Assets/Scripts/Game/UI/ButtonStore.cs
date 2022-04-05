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
    ParkPlus,
    ParkMinus,
    ParkBuy,
    ParkSell,
    HospitalPlus,
    HospitalMinus,
    HospitalBuy,
    HospitalSell,
    OfficePlus,
    OfficeMinus,
    OfficeBuy,
    OfficeSell,
    ShoppingMallPlus,
    ShoppingMallMinus,
    ShoppingMallBuy,
    ShoppingMallSell,
    PoliceStationPlus,
    PoliceStationMinus,
    PoliceStationBuy,
    PoliceStationSell,
    RoadTab,
    BuildingTab,
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

    GameObject ParkPlus;
    GameObject ParkMinus;
    GameObject ParkNo;
    GameObject ParkBuy;
    GameObject ParkSell;

    GameObject HospitalPlus;
    GameObject HospitalMinus;
    GameObject HospitalNo;
    GameObject HospitalBuy;
    GameObject HospitalSell;

    GameObject OfficePlus;
    GameObject OfficeMinus;
    GameObject OfficeNo;
    GameObject OfficeBuy;
    GameObject OfficeSell;

    GameObject ShoppingMallPlus;
    GameObject ShoppingMallMinus;
    GameObject ShoppingMallNo;
    GameObject ShoppingMallBuy;
    GameObject ShoppingMallSell;

    GameObject PoliceStationPlus;
    GameObject PoliceStationMinus;
    GameObject PoliceStationNo;
    GameObject PoliceStationBuy;
    GameObject PoliceStationSell;

    //GameObject Storebtn;
    GameObject StoreBG;
    GameObject StoreBuildingBG;
    GameObject RoadTab;
    GameObject BuildingTab;

    GameObject RoadTabText;
    GameObject BuildingTabText;
    //GameObject StoreBack;

    GameObject CostTitle;
    GameObject RoadCost;
    GameObject TLCost;
    GameObject ERPCost;
    GameObject ParkCost;
    GameObject HospitalCost;
    GameObject OfficeCost;
    GameObject ShoppingMallCost;
    GameObject PoliceStationCost;

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

    //bool stopTime;
    //float stopTimer;

    GameState gameState;


    Transform displayArrow;
    //Transform displayArrowWhite;
    Transform timerButton;
    Transform pauseIcon;

    Transform moneyText;
    Transform roadCount;

    UI texture;

    CombinedUI combinedUI;

    public bool revealCartButton;
    public bool closing;
    public bool buildTabBool;
    public bool roadTabBool;

    Transform storeIntro;

    Transform storeClose;
    public MoneySystem moneySystem;

    public override void Start()
    {
        RoadTabText = GameObject.Find("RoadText");
        BuildingTabText = GameObject.Find("BuildingText");

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
        buildTabBool = false;
        roadTabBool = true;

        texture = GetComponent<UI>();
        //texture.color = new Color(0f, 0f, 0f);

        //Storebtn = GameObject.Find("Storebtn");
        StoreBG = GameObject.Find("StoreBG");
        StoreBuildingBG = GameObject.Find("StoreBuildingBG");
        RoadTab = GameObject.Find("RoadTab");
        BuildingTab = GameObject.Find("BuildingTab");
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

        ParkPlus = GameObject.Find("ParkPlus");
        ParkMinus = GameObject.Find("ParkMinus");
        ParkNo = GameObject.Find("ParkQty");
        ParkBuy = GameObject.Find("ParkBuy");
        ParkSell = GameObject.Find("ParkSell");

        HospitalPlus = GameObject.Find("HospitalPlus");
        HospitalMinus = GameObject.Find("HospitalMinus");
        HospitalNo = GameObject.Find("HospitalQty");
        HospitalBuy = GameObject.Find("HospitalBuy");
        HospitalSell = GameObject.Find("HospitalSell");

        OfficePlus = GameObject.Find("OfficePlus");
        OfficeMinus = GameObject.Find("OfficeMinus");
        OfficeNo = GameObject.Find("OfficeQty");
        OfficeBuy = GameObject.Find("OfficeBuy");
        OfficeSell = GameObject.Find("OfficeSell");

        ShoppingMallPlus = GameObject.Find("ShoppingMallPlus");
        ShoppingMallMinus = GameObject.Find("ShoppingMallMinus");
        ShoppingMallNo = GameObject.Find("ShoppingMallQty");
        ShoppingMallBuy = GameObject.Find("ShoppingMallBuy");
        ShoppingMallSell = GameObject.Find("ShoppingMallSell");

        PoliceStationPlus = GameObject.Find("PoliceStationPlus");
        PoliceStationMinus = GameObject.Find("PoliceStationMinus");
        PoliceStationNo = GameObject.Find("PoliceStationQty");
        PoliceStationBuy = GameObject.Find("PoliceStationBuy");
        PoliceStationSell = GameObject.Find("PoliceStationSell");

        gameState = GameObject.Find("GameManager").GetComponent<GameState>();


        displayArrow = GameObject.Find("Displaybtn").GetComponent<Transform>();
        //displayArrowWhite = GameObject.Find("DisplaybtnWhite").GetComponent<Transform>();
        timerButton = GameObject.Find("TimerIcon").GetComponent<Transform>();
        pauseIcon = GameObject.Find("PauseIcon").GetComponent<Transform>();



        CostTitle = GameObject.Find("CostTitle");
        hCostPosition = CostTitle.transform.position;

        RoadCost = GameObject.Find("RoadCost");
        TLCost = GameObject.Find("TrafficCost");
        ERPCost = GameObject.Find("ERPCost");
        ParkCost = GameObject.Find("ParkCost");
        HospitalCost = GameObject.Find("HospitalCost");
        OfficeCost = GameObject.Find("OfficeCost");
        ShoppingMallCost = GameObject.Find("ShoppingMallCost");
        PoliceStationCost = GameObject.Find("PoliceStationCost");

        Disable<Transform>(storeClose);

        //Disable<Transform>(Storebtn.transform);
        Disable<Transform>(StoreBG.transform);
        Disable<Transform>(StoreBuildingBG.transform);
        Disable<Transform>(RoadTab.transform);
        Disable<Transform>(BuildingTab.transform);
        Disable<Transform>(RoadTabText.transform);
        Disable<Transform>(BuildingTabText.transform);
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

        Disable<Transform>(ParkPlus.transform);
        Disable<Transform>(ParkMinus.transform);
        Disable<Transform>(ParkNo.transform);
        Disable<Transform>(ParkBuy.transform);
        Disable<Transform>(ParkSell.transform);

        Disable<Transform>(HospitalPlus.transform);
        Disable<Transform>(HospitalMinus.transform);
        Disable<Transform>(HospitalNo.transform);
        Disable<Transform>(HospitalBuy.transform);
        Disable<Transform>(HospitalSell.transform);

        Disable<Transform>(OfficePlus.transform);
        Disable<Transform>(OfficeMinus.transform);
        Disable<Transform>(OfficeNo.transform);
        Disable<Transform>(OfficeBuy.transform);
        Disable<Transform>(OfficeSell.transform);

        Disable<Transform>(ShoppingMallPlus.transform);
        Disable<Transform>(ShoppingMallMinus.transform);
        Disable<Transform>(ShoppingMallNo.transform);
        Disable<Transform>(ShoppingMallBuy.transform);
        Disable<Transform>(ShoppingMallSell.transform);

        Disable<Transform>(PoliceStationPlus.transform);
        Disable<Transform>(PoliceStationMinus.transform);
        Disable<Transform>(PoliceStationNo.transform);
        Disable<Transform>(PoliceStationBuy.transform);
        Disable<Transform>(PoliceStationSell.transform);

        Disable<Transform>(RoadCost.transform);
        Disable<Transform>(TLCost.transform);
        Disable<Transform>(ERPCost.transform);
        Disable<Transform>(ParkCost.transform);
        Disable<Transform>(HospitalCost.transform);
        Disable<Transform>(OfficeCost.transform);
        Disable<Transform>(ShoppingMallCost.transform);
        Disable<Transform>(PoliceStationCost.transform);

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
                Enable<Transform>(RoadTab.transform);
                Enable<Transform>(BuildingTab.transform);
                Enable<Transform>(RoadTabText.transform);
                Enable<Transform>(BuildingTabText.transform);
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
            Disable<Transform>(StoreBuildingBG.transform);
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

            Disable<Transform>(ParkPlus.transform);
            Disable<Transform>(ParkMinus.transform);
            Disable<Transform>(ParkNo.transform);
            Disable<Transform>(ParkBuy.transform);
            Disable<Transform>(ParkSell.transform);

            Disable<Transform>(HospitalPlus.transform);
            Disable<Transform>(HospitalMinus.transform);
            Disable<Transform>(HospitalNo.transform);
            Disable<Transform>(HospitalBuy.transform);
            Disable<Transform>(HospitalSell.transform);

            Disable<Transform>(OfficePlus.transform);
            Disable<Transform>(OfficeMinus.transform);
            Disable<Transform>(OfficeNo.transform);
            Disable<Transform>(OfficeBuy.transform);
            Disable<Transform>(OfficeSell.transform);

            Disable<Transform>(ShoppingMallPlus.transform);
            Disable<Transform>(ShoppingMallMinus.transform);
            Disable<Transform>(ShoppingMallNo.transform);
            Disable<Transform>(ShoppingMallBuy.transform);
            Disable<Transform>(ShoppingMallSell.transform);

            Disable<Transform>(PoliceStationPlus.transform);
            Disable<Transform>(PoliceStationMinus.transform);
            Disable<Transform>(PoliceStationNo.transform);
            Disable<Transform>(PoliceStationBuy.transform);
            Disable<Transform>(PoliceStationSell.transform);

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
            Disable<Transform>(ParkCost.transform);
            Disable<Transform>(HospitalCost.transform);
            Disable<Transform>(OfficeCost.transform);
            Disable<Transform>(ShoppingMallCost.transform);
            Disable<Transform>(PoliceStationCost.transform);

            Disable<Transform>(RoadTab.transform);
            Disable<Transform>(BuildingTab.transform);
            Disable<Transform>(RoadTabText.transform);
            Disable<Transform>(BuildingTabText.transform);

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

        InputManager.allowBuilding = false;
    }

    public override void OnMouseExit()
    {
        texture.ChangeTexture("Game/Store/Store");

        InputManager.allowBuilding = true;
    }

    internal void ResumeAction()
    {
        StoreAction();
    }

    public void ToggleStore()
    {
        if (roadTabBool)
        {
            buildTabBool = false;

            Enable<Transform>(StoreBG.transform);
            Disable<Transform>(StoreBuildingBG.transform);
            Enable<Transform>(RoadTab.transform);
            Enable<Transform>(BuildingTab.transform);
            Enable<Transform>(RoadPlus.transform);
            Enable<Transform>(RoadMinus.transform);
            Enable<Transform>(RoadNo.transform);
            Enable<Transform>(RoadBuy.transform);
            Enable<Transform>(RoadSell.transform);
            Enable<Transform>(Roadx1.transform);
            Enable<Transform>(Roadx10.transform);

            if (combinedUI.buttonRoad.revealTrafficButton)
            {
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
                Enable<Transform>(ERPPlus.transform);
                Enable<Transform>(ERPMinus.transform);
                Enable<Transform>(ERPNo.transform);
                Enable<Transform>(ERPBuy.transform);
                Enable<Transform>(ERPSell.transform);
                Enable<Transform>(ERPCost.transform);
                Enable<Transform>(ERPx1.transform);
                Enable<Transform>(ERPx10.transform);
            }

            Enable<Transform>(RoadCost.transform);

            //disable UI for building store 
            Disable<Transform>(ParkPlus.transform);
            Disable<Transform>(ParkMinus.transform);
            Disable<Transform>(ParkNo.transform);
            Disable<Transform>(ParkBuy.transform);
            Disable<Transform>(ParkSell.transform);

            Disable<Transform>(HospitalPlus.transform);
            Disable<Transform>(HospitalMinus.transform);
            Disable<Transform>(HospitalNo.transform);
            Disable<Transform>(HospitalBuy.transform);
            Disable<Transform>(HospitalSell.transform);

            Disable<Transform>(OfficePlus.transform);
            Disable<Transform>(OfficeMinus.transform);
            Disable<Transform>(OfficeNo.transform);
            Disable<Transform>(OfficeBuy.transform);
            Disable<Transform>(OfficeSell.transform);

            Disable<Transform>(ShoppingMallPlus.transform);
            Disable<Transform>(ShoppingMallMinus.transform);
            Disable<Transform>(ShoppingMallNo.transform);
            Disable<Transform>(ShoppingMallBuy.transform);
            Disable<Transform>(ShoppingMallSell.transform);

            Disable<Transform>(PoliceStationPlus.transform);
            Disable<Transform>(PoliceStationMinus.transform);
            Disable<Transform>(PoliceStationNo.transform);
            Disable<Transform>(PoliceStationBuy.transform);
            Disable<Transform>(PoliceStationSell.transform);

        }
        if(buildTabBool)
        {
            roadTabBool = false;

            Disable<Transform>(StoreBG.transform);
            Enable<Transform>(StoreBuildingBG.transform);
            Enable<Transform>(RoadTab.transform);
            Enable<Transform>(BuildingTab.transform);
            Disable<Transform>(RoadPlus.transform);
            Disable<Transform>(RoadMinus.transform);
            Disable<Transform>(RoadNo.transform);
            Disable<Transform>(RoadBuy.transform);
            Disable<Transform>(RoadSell.transform);
            Disable<Transform>(Roadx1.transform);
            Disable<Transform>(Roadx10.transform);

            Disable<Transform>(TrafficPlus.transform);
            Disable<Transform>(TrafficMinus.transform);
            Disable<Transform>(TrafficNo.transform);
            Disable<Transform>(TrafficBuy.transform);
            Disable<Transform>(TrafficSell.transform);
            Disable<Transform>(Trafficx1.transform);
            Disable<Transform>(Trafficx10.transform);

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

            //enable UI for building store
            Enable<Transform>(ParkPlus.transform);
            Enable<Transform>(ParkMinus.transform);
            Enable<Transform>(ParkNo.transform);
            Enable<Transform>(ParkBuy.transform);
            Enable<Transform>(ParkSell.transform);
            
            Enable<Transform>(HospitalPlus.transform);
            Enable<Transform>(HospitalMinus.transform);
            Enable<Transform>(HospitalNo.transform);
            Enable<Transform>(HospitalBuy.transform);
            Enable<Transform>(HospitalSell.transform);
            
            Enable<Transform>(OfficePlus.transform);
            Enable<Transform>(OfficeMinus.transform);
            Enable<Transform>(OfficeNo.transform);
            Enable<Transform>(OfficeBuy.transform);
            Enable<Transform>(OfficeSell.transform);
            
            Enable<Transform>(ShoppingMallPlus.transform);
            Enable<Transform>(ShoppingMallMinus.transform);
            Enable<Transform>(ShoppingMallNo.transform);
            Enable<Transform>(ShoppingMallBuy.transform);
            Enable<Transform>(ShoppingMallSell.transform);
            
            Enable<Transform>(PoliceStationPlus.transform);
            Enable<Transform>(PoliceStationMinus.transform);
            Enable<Transform>(PoliceStationNo.transform);
            Enable<Transform>(PoliceStationBuy.transform);
            Enable<Transform>(PoliceStationSell.transform);

       
        }
            
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

    public void SetroadTabBool(bool type)
    {
        roadTabBool = type;
    }

    public void SetbuildingTabBool(bool type)
    {
        buildTabBool = type;
    }
}


