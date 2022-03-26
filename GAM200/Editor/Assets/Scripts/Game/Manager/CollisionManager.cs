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

    private Dictionary<uint, SortedSet<uint>> raycastCollisionRecord;

    public override void Start()
    {
        tm = GameObject.Find("TrafficManager").GetComponent<TrafficManager>();
        em = GameObject.Find("ERPManager").GetComponent<ERPManager>();
        pm = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        raycastCollisionRecord = new Dictionary<uint, SortedSet<uint>>();
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
        if (Input.GetKey(KeyCode.Y)) Debug.Log(raycastCollisionRecord.Count);
        raycastCollisionRecord.Clear();
    }

    public void AddRaycastCollision(uint owner, uint target)
    {
        if (!raycastCollisionRecord.ContainsKey(owner))
        {
            SortedSet<uint> ss = new SortedSet<uint>();
            ss.Add(target);
            raycastCollisionRecord.Add(owner, ss);
        }
        else
        {
            //Debug.Log("Adding another one");
            raycastCollisionRecord[owner].Add(target);
        }
    }

    public void RemoveRaycastCollision(uint owner)
    {
        raycastCollisionRecord.Remove(owner);
    }

    //Decide which car to go first
    public bool CheckStopRaycastCollision(uint owner, uint target)
    {
        if (raycastCollisionRecord.ContainsKey(target))
        {
            foreach (var t in raycastCollisionRecord[target])
            //if (raycastCollisionRecord[target] == owner)
            {
                if (t == owner)
                {
                    //-----------------
                    //if (Input.GetKey(KeyCode.F) && owner > target)
                    if (owner > target)
                    {
                        Debug.Log("Olrder taget--------------------------------");
                        if (Input.GetKey(KeyCode.C) )
                        {
                            TimeSystem.StopTime();
                            //GameObject.Find("GameManager").GetComponent<GameState>().SetPause(true);
                        }
                    }
                    //-----------------
                    //Let the newer entity pass
                    //Logic behind it: Because the newer entity will have its' CarAi run later, it means that it will add to raycastCollisionRecord later
                    //And when two car raycast into each other, only the newer entity will detect in raycastCollisionRecord that raycastCollisionRecord[owner] = target and raycastCollisionRecord[target] = owner,
                    //Which is why the newer entity will be allowed to go
                    return !(owner > target);
                }
            }
        }
        return true;
    }
}
