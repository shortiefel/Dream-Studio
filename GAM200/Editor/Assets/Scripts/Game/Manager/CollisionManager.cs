using System.Collections.Generic;

//Car is not included as checking for Cars might be too expensive
//Considering that it could go 5 times higher than the other things
public enum CollisionType
{
    Unknown = 0,
    ERP,
    Traffic
}

public class CollisionManager : MonoBehaviour
{
    private TrafficManager tm;
    private ERPManager em;

    private Dictionary<uint, uint> raycastCollisionRecord;

    public override void Start()
    {
        tm = GameObject.Find("TrafficManager").GetComponent<TrafficManager>();
        em = GameObject.Find("ERPManager").GetComponent<ERPManager>();

        raycastCollisionRecord = new Dictionary<uint, uint>();
    }

    public CollisionType CollisionTypeCheck(Vector2Int targetPos)
    {
        if (tm.IsTrafficLight(targetPos))
        {
            return CollisionType.Traffic;
        }

        else if (em.IsERP(targetPos))
        {
            return CollisionType.ERP;
        }


        return CollisionType.Unknown;
    }

    public override void Update()
    {

    }

    public void AddRaycastCollision(uint owner, uint target)
    {
        raycastCollisionRecord.Add(owner, target);
    }

    public void RemoveRaycastCollision(uint owner)
    {

        raycastCollisionRecord.Remove(owner);
    }
}
