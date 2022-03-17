using System.Collections.Generic;

//Car is not included as checking for Cars might be too expensive
//Considering that it could go 5 times higher than the other things
public enum CollisionType
{
    Unknown = 0,
    ERP,
    Traffic,
    Building
}

public class CollisionManager : MonoBehaviour
{
    private TrafficManager tm;
    private ERPManager em;
    private PlacementManager pm;

    private Dictionary<uint, uint> raycastCollisionRecord;

    public override void Start()
    {
        tm = GameObject.Find("TrafficManager").GetComponent<TrafficManager>();
        em = GameObject.Find("ERPManager").GetComponent<ERPManager>();
        pm = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        raycastCollisionRecord = new Dictionary<uint, uint>();
    }

    public CollisionType CollisionTypeCheck(Vector2Int targetPos, uint entId)
    {
        if (tm.IsTrafficLight(targetPos, entId))
        {
            return CollisionType.Traffic;
        }

        else if (em.IsERP(targetPos, entId))
        {
            return CollisionType.ERP;
        }

        else if (pm.IsBuilding(targetPos, entId))
        {
            return CollisionType.Building;
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
