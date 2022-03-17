public enum StoreButtonType
{
    RoadBuy = 1,
    RoadSell,
    TrafficBuy,
    TrafficSell,
    ERPBuy,
    ERPSell,
    BackToGame
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
    //GameObject StoreBack;

    GameObject CostTitle;
    GameObject RoadCost;
    GameObject TLCost;
    GameObject ERPCost;

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

    public override void Start()
    {
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
        texture.color = new Color(0f, 0f, 0f);

        Storebtn = GameObject.Find("Storebtn");
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

        Disable<Transform>(Storebtn.transform);
        Disable<Transform>(StoreBG.transform);
        //Disable<Transform>(StoreBack.transform);
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

        Disable<Transform>(RoadCost.transform);
        Disable<Transform>(TLCost.transform);
        Disable<Transform>(ERPCost.transform);


        //stopTime = false;
        //stopTimer = 0f;


        combinedUI = GameObject.Find("CombinedUI").GetComponent<CombinedUI>();
    }

    public void SwitchTabStore(bool type, bool reenable = true)
    {
        if (type)
        {
            if (revealCartButton == true)
            {
                Enable<Transform>(StoreBG.transform);
                //Enable<Transform>(StoreBack.transform);
                Enable<Transform>(StoreHeader.transform);
                Enable<Transform>(ItemHeader.transform);
                Enable<Transform>(QtyHeader.transform);
                Enable<Transform>(RoadIcon.transform);
                Enable<Transform>(RoadBuy.transform);
                Enable<Transform>(RoadSell.transform);
                Enable<Transform>(RoadNo.transform);
            }

            if (combinedUI.buttonRoad.revealTrafficButton)
            {
                Enable<Transform>(TrafficIcon.transform);
                Enable<Transform>(TrafficBuy.transform);
                Enable<Transform>(TrafficSell.transform);
                Enable<Transform>(TrafficNo.transform);
                Enable<Transform>(TLCost.transform);
            }

            if (combinedUI.buttonRoad.revealERPButton)
            {
                Enable<Transform>(ERPIcon.transform);
                Enable<Transform>(ERPBuy.transform);
                Enable<Transform>(ERPSell.transform);
                Enable<Transform>(ERPNo.transform);
                Enable<Transform>(ERPCost.transform);
            }

            Enable<Transform>(CostTitle.transform);
            Enable<Transform>(RoadCost.transform);
            

            //stopTime = true;

            //Disable<Transform>(Storebtn.transform);
            //Enable<Transform>(StoreBack.transform);

            //Disable<Transform>(displayArrow);
            //Disable<Transform>(displayArrowWhite);
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
            Disable<Transform>(StoreBG.transform);
            //Disable<Transform>(StoreBack.transform);
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

            if (reenable)
            {
                Enable<Transform>(displayArrow);
                Enable<Transform>(timerButton);
                Enable<Transform>(pauseIcon);

                if (combinedUI != null)
                    combinedUI.EnableAllMasterButton();
            }

            Disable<Transform>(CostTitle.transform);
            Disable<Transform>(RoadCost.transform);
            Disable<Transform>(TLCost.transform);
            Disable<Transform>(ERPCost.transform);

            
            

            //Enable<Transform>(Storebtn.transform);
            //Disable<Transform>(StoreBack.transform);
        }
    }
   

   private void StoreAction()
    {
        //Debug.Log("Store");
        //gameState.InvertPause();
        bool state = !gameState.GetPause();
        gameState.SetPause(state);
        SwitchTabStore(state);
    }

    public override void Update()
    {
        if (!gameState.GetDrawMode())
        {
            if (Input.GetKeyDown(KeyCode.Escape))
            {
                //Enable<Transform>(Storebtn.transform);
                //Disable<Transform>(StoreBack.transform);
                StoreAction();
            }
        }

        //if (stopTime)
        //{
        //    stopTimer += Time.deltaTime;
        //
        //    float newTimer = 5f * stopTimer;
        //
        //    if (stopTimer > 0.1f)
        //    {
        //        stopTimer = 0f;
        //        stopTime = false;
        //
        //        //Enable<Transform>(Storebtn.transform);
        //        //Disable<Transform>(StoreBack.transform);
        //        Disable<Transform>(displayArrow);
        //        Disable<Transform>(displayArrowWhite);
        //        Disable<Transform>(pauseIcon);
        //
        //        Disable<Transform>(timerButton);
        //
        //        Time.timeScale = 0f;
        //    }
        //}
    }


    public override void OnMouseEnter()
    {
        texture.color = new Color(1f, 1f, 1f);
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
        texture.color = new Color(0f, 0f, 0f);
    }

    internal void ResumeAction()
    {
        StoreAction();
    }

    public void RevealStore()
    {
        revealCartButton = true;
        Enable<Transform>(Storebtn.transform);
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


