

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

    public override void Start()
    {
        tm = GameObject.Find("TrafficManager").GetComponent<TrafficManager>();
        em = GameObject.Find("ERPManager").GetComponent<ERPManager>();
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
}
