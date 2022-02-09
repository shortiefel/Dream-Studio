using System.Collections.Generic;

public class ERPManager : MonoBehaviour
{
    private int noOfERP;

    MoneySystem moneySystem;
    private TrafficLightManager trafficLightManager;
    //private bool toDraw; //To Remove ------------------------------------------------------
    private GameObject erpGO;
    Camera mainCamera; //TO Remove

    private Dictionary<Vector2Int, uint> erpList;
    public override void Start()
    {
        noOfERP = 0;
        erpList = new Dictionary<Vector2Int, uint>();

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();

        erpGO = new GameObject(new Prefab("ERP"));
        mainCamera = GameObject.Find("Camera").GetComponent<Camera>(); //To Remove
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

    public void RemoveERP(Vector2Int pos)
    {
        erpList.Remove(pos);
    }

    public bool IsERP(Vector2Int posToCheck)
    {
        if (erpList.ContainsKey(posToCheck)) return true;
        return false;
    }


    public bool RequestPlacingERP(Vector2Int position)
    {
        trafficLightManager = GameObject.Find("TrafficManager").GetComponent<TrafficLightManager>();
        if (erpList.ContainsKey(position)) 
            return false;
        if (trafficLightManager.IsTrafficLight(position))
            return false;

        Instantiate(erpGO, new Vector3(position.x, position.y, 0f));
        return true;
    }

    public bool RequestRemovingERP(Vector2Int position)
    {
        if (!erpList.ContainsKey(position)) 
            return false;
       
        moneySystem.DestoryErp();
        Destroy(erpList[position]);
        erpList.Remove(position);
        return true;
    }
}
