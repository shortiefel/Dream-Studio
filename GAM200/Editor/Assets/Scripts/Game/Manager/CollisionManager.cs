using System.Collections.Generic;
using System;
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
        //if (Input.GetKey(KeyCode.Y)) Debug.Log(raycastCollisionRecord.Count);
        //Console.WriteLine("Resetting---------------------------------------------------");
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
                    //if (owner > target)
                    {
                        //Debug.Log("Olrder taget--------------------------------");
                        if (Input.GetKey(KeyCode.C) )
                        {
                            TimeSystem.StopTime();
                            //GameObject.Find("GameManager").GetComponent<GameState>().SetPause(true);
                        }
                    }
                    //-----------------

                    

                    //Return false everytime raycastCollisionRecord[owner] has target and raycastCollisionRecord[target] has owner
                    //Logic behind it is that, each entity's script get run 1 after another, if 2 cars were to raycast each other,
                    //the first car would not find the other entityId, while the second car would find the other entityId
                    return false;
                }
            }
        }
        return true;
    }
}
