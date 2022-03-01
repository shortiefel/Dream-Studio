using System.Collections.Generic;

public class ERPManager : MonoBehaviour
{
    MoneySystem moneySystem;
    private TrafficLightManager trafficLightManager;
    //private bool toDraw; //To Remove ------------------------------------------------------
    private GameObject erpGO;
    //Camera mainCamera; //TO Remove

    private Dictionary<Vector2Int, uint> erpList;

    public int erpCount;

    Transform ERPInfoText;
    Transform ERPInfo;


    public override void Start()
    {
        erpList = new Dictionary<Vector2Int, uint>();

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();

        erpGO = new GameObject(new Prefab("ERP"));

        trafficLightManager = GameObject.Find("TrafficManager").GetComponent<TrafficLightManager>();
        //mainCamera = GameObject.Find("Camera").GetComponent<Camera>(); //To Remove

        erpCount = 1;

        ERPInfoText = GameObject.Find("ERPPopInfoText").GetComponent<Transform>();
        ERPInfo = GameObject.Find("ERPPopInfo").GetComponent<Transform>();

        Disable<Transform>(ERPInfoText);
        Disable<Transform>(ERPInfo);

    }

    //public override void Update()
    //{
    //    //To Remove ------------------------------------------------------
    //    if (toDraw && Input.GetMouseButtonDown(MouseCode.Left))
    //    {
    //        Vector3Int mousePos = Vector3Int.RoundToInt(mainCamera.ScreenToWorldPoint(Input.GetMousePosition()));
    //    
    //        Instantiate(erpGO, new Vector3(mousePos.x, mousePos.y, 0f));
    //    }
    //    if (Input.GetKeyDown(KeyCode.F))
    //    {
    //        toDraw = !toDraw;
    //    }
    //    //To Remove ------------------------------------------------------
    //}

    public void Notify()
    {
        //Increase money
        moneySystem.AddMoney(10);
    }

    public void RegisterERP(Vector2Int pos, uint id)
    {
        if (!erpList.ContainsKey(pos))
        {
            erpList.Add(pos, id);
            Debug.Log(pos);
        }
    }

    //public void RemoveERP(Vector2Int pos)
    //{
    //    erpList.Remove(pos);
    //}

    public bool IsERP(Vector2Int posToCheck)
    {
        if (erpList.ContainsKey(posToCheck)) return true;
        return false;
    }


    public bool RequestPlacingERP(Vector2Int position)
    {
        Disable<Transform>(ERPInfoText);
        Disable<Transform>(ERPInfo);

        if (erpCount <= 0)
        {
            Enable<Transform>(ERPInfoText);
            Enable<Transform>(ERPInfo);
            return false;
        }

        if (erpList.ContainsKey(position))
            return false;
        if (trafficLightManager.IsTrafficLight(position))
            return false;

        --erpCount;
        Instantiate(erpGO, new Vector3(position.x, position.y, 0f));
        return true;
    }

    public bool RequestRemovingERP(Vector2Int position)
    {
        Disable<Transform>(ERPInfoText);
        Disable<Transform>(ERPInfo);

        if (!erpList.ContainsKey(position))
            return false;

        ++erpCount;
        //moneySystem.DestoryErp();
        Destroy(erpList[position]);
        erpList.Remove(position);
        return true;
    }
}
