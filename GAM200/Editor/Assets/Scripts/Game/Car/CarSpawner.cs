using System.Collections;
using System.Collections.Generic;
using System;

public struct EndStruct
{
    public uint entityId;
    public BuildingType bt;
    public Vector2Int endPos;

    public EndStruct(uint id, BuildingType _bt, Vector2Int ep)
    {
        entityId = id;
        bt = _bt;
        endPos = ep;
    }
}
public class CarSpawner : MonoBehaviour
{
    GameState gameState;

    float lifeTime;
    float maxLifeTime;

    PosIdSet[] possibleDest;
    Vector2Int selfPos;

    BuildingType outBt;
    PosIdSet posIdSet;

    int carCounter = 0;

    bool prevSpawnStatus;
    EndStruct spawnTarget;


    float secondaryTimer; //The secondary timer is for when the spawning fails and so it doesnt spam the spawncar

    public Queue<EndStruct> requestLine;
    public Queue<EndStruct> backlog; //For unsuccessful spawn

    public Queue<BuildingType> backlogNew; //For unsuccessful spawn

    //GameObject.FindWithId(id).GetComponent<StructureModel>()
    public void RequestSpawn(EndStruct es)
    {
        requestLine.Enqueue(es);
    }

    AIDirector aiDirector;

    float spawnTimer;
    float spawnTimerMax;

    float dt;
    public override void Start()
    {
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        lifeTime = 0f;
        maxLifeTime = 80f;

        possibleDest = new PosIdSet[(int)BuildingType.House];
        selfPos = new Vector2Int(transform.position);

        requestLine = new Queue<EndStruct>();
        backlog = new Queue<EndStruct>();

        backlogNew = new Queue<BuildingType>();

        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
        //    //spawnManager = GameObject.Find("SpawnManager").GetComponent<SpawnManager>();
        //    //maxTimer = aiDirector.carSpawnTimerInterval;
        //    //structureModel = GetComponent<StructureModel>();
        spawnTimer = 0f;
        spawnTimerMax = 4f;
        //spawnTimerMax = 10f;

        prevSpawnStatus = true;
        secondaryTimer = 0f;
    }
    //
    public override void Update()
    {
        dt = Time.deltaTime;

        //lifeTime += dt;
        //if (lifeTime > maxLifeTime)
        //{
        //    lifeTime = 0f;
        //    Debug.Log("CarSpawner lose lifetime");
        //    gameState.MissedDestinationTime(BuildingType.House);
        //}

        //Use Queue peek to show notification of the one that is needed
        spawnTimer += dt;
        //Debug.Log(spawnTimer);
        if (spawnTimer >= spawnTimerMax && carCounter == 0)
        {
            
            if (backlogNew.Count != 0)
            {
                if (aiDirector.SpawnAtTypeDest(selfPos, backlogNew.Peek()))
                {
                    backlogNew.Dequeue();

                    spawnTimer = 0f;
                    return;
                }
            }

            if (aiDirector.SelectADestAndSpawn(selfPos, possibleDest, out outBt, out posIdSet))
            {
                possibleDest[(int)outBt] = posIdSet;

                spawnTimer = 0f;
            }

            else
            {
                if (outBt != BuildingType.None)
                    backlogNew.Enqueue(outBt);

                Debug.Log("Enqueue " + outBt);
                spawnTimer = 0f;
            }
        }

        //Debug.Log("backlogNew " + backlogNew.Count);


        //if (requestLine.Count != 0 || backlog.Count != 0)
        //{
        //    spawnTimer += dt;
        //
        //    if (spawnTimer >= spawnTimerMax && carCounter == 0)
        //    {
        //
        //        if (backlog.Count != 0) {
        //            spawnTarget = backlog.Dequeue();
        //
        //            if (SpawnCurrentSpawnTarget()) return;
        //        }
        //
        //        if (requestLine.Count != 0)
        //        {
        //            spawnTarget = requestLine.Dequeue();
        //
        //            SpawnCurrentSpawnTarget();
        //        }
        //    }
        //}
    }

    //bool SpawnCurrentSpawnTarget()
    //{
    //    prevSpawnStatus = aiDirector.SpawnCar(transform.position, spawnTarget.entityId, spawnTarget.bt, spawnTarget.endPos, RouteType.HouseToDest);
    //    if (prevSpawnStatus)
    //    {
    //        spawnTimer = 0f;
    //        return true;
    //    }
    //
    //    backlog.Enqueue(spawnTarget);
    //
    //    return false;
    //}

    public override void OnTriggerEnter(uint entId)
    {
        ++carCounter;
    }

    public override void OnTriggerExit(uint entId)
    {
        --carCounter;
    }

    /*public Prefab[] carPrefabs;

    public override void Awake()
    {
        carPrefabs = new Prefab[1];
        carPrefabs[0] = new Prefab("Car");

    }

    public override void Start()
    {
        if (transform == null) Console.WriteLine("Stuff");
        //if (SelectACarPrefab() == null) Console.WriteLine("Stuff2222");
        //Console.WriteLine(SelectACarPrefab().name);
        Instantiate(SelectACarPrefab(), transform);


    }

    private Prefab SelectACarPrefab()
    {
        var randomIndex = Random.Range(0, carPrefabs.Length);
        return carPrefabs[randomIndex];
    }*/
}
