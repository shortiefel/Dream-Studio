using System.Collections.Generic;

public class ERPManager : MonoBehaviour
{
    private int noOfERP;

    MoneySystem moneySystem;

    private bool toDraw; //To Remove ------------------------------------------------------
    GameObject erpGO; //TO Remove
    Camera mainCamera; //TO Remove

    private Dictionary<Vector2Int, uint> erpList;

    public override void Start()
    {
        noOfERP = 0;
        erpList = new Dictionary<Vector2Int, uint>();

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();

        erpGO = new GameObject(new Prefab("ERP")); //To Remove
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
        moneySystem.AddMoney(20);
    }

    public void RegisterERP(Vector2Int pos, uint id)
    {
        if (!erpList.ContainsKey(pos))
            erpList.Add(pos, id);
    }

    public void RemoveERP(Vector2Int pos)
    {
        Debug.Log("Removing");
        erpList.Remove(pos);
    }

    public bool IsERP(Vector2Int posToCheck)
    {
        if (erpList.ContainsKey(posToCheck)) return true;
        return false;
    }

}
