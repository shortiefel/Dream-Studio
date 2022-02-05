using System.Collections.Generic;

public class ERP : MonoBehaviour
{
    private ERPManager erpManager;

    public override void Start()
    {
        GameObject go = GameObject.Find("ERPManager");
        if (go != null)
            erpManager = go.GetComponent<ERPManager>();

        if (erpManager != null)
            erpManager.RegisterERP(Vector2Int.RoundToInt(transform.position), entityId);
    }

    public override void OnTriggerEnter(uint id)
    {
        if (erpManager != null)
            erpManager.Notify();
    }

    //public override void OnDestroy()
    //{
    //    Debug.Log("erp destroy");
    //    if (erpManager != null)
    //        erpManager.RemoveERP(Vector2Int.RoundToInt(transform.position));
    //}
}
