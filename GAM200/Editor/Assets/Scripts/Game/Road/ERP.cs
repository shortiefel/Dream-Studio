using System.Collections.Generic;

public class ERP : MonoBehaviour
{
    private ERPManager erpManager;

    public override void Start()
    {
        erpManager = GameObject.Find("ERPManager").GetComponent<ERPManager>();

        erpManager.RegisterERP(Vector2Int.RoundToInt(transform.position), entityId);
    }

    public override void OnDestroy()
    {
        erpManager.RemoveERP(Vector2Int.RoundToInt(transform.position));
    }

    public override void OnTriggerEnter(uint id)
    {
        erpManager.Notify();
    }
}
