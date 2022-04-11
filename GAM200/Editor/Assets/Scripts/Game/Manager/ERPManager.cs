using System.Collections.Generic;

public class ERPManager : MonoBehaviour
{
    MoneySystem moneySystem;
    private TrafficLightManager trafficLightManager;
    private GameObject erpGO;

    private Dictionary<Vector2Int, uint> erpList;
    public override void Start()
    {
        erpList = new Dictionary<Vector2Int, uint>();

        moneySystem = GameObject.Find("MoneyText").GetComponent<MoneySystem>();

        erpGO = new GameObject(new Prefab("ERP"));

        trafficLightManager = GameObject.Find("TrafficManager").GetComponent<TrafficLightManager>();
    }


    
    public void Notify()
    {
        //Increase money
        MoneySystem.AddMoney(10, MoneySource.ERP);
    }

    public void RegisterERP(Vector2Int pos, uint id)
    {
        if (!erpList.ContainsKey(pos))
        {
            erpList.Add(pos, id);
            Debug.Log(pos);
        }
    }

    public bool IsERP(Vector2Int targetPos, uint entId = 0)
    {
        if (entId == 0) return erpList.ContainsKey(targetPos);
        if (!erpList.ContainsKey(targetPos)) return false;
        return erpList[targetPos] == entId;
    }

    public int erpTaxCount()
    {
        return erpList.Count;
    }

    public bool RequestPlacingERP(Vector2Int position)
    {
        if (erpList.ContainsKey(position))
            return false;
        if (trafficLightManager.IsTrafficLight(position))
            return false;
        if (moneySystem.BuyErp())
            Instantiate(erpGO, new Vector3(position.x, position.y, 0f), 3);
        return true;
    }

    public bool RequestRemovingERP(Vector2Int position)
    {

        if (!erpList.ContainsKey(position))
            return false;
        moneySystem.SellErp();
        Destroy(erpList[position]);
        erpList.Remove(position);
        return true;
    }
}
