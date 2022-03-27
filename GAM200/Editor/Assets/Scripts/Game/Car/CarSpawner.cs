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

    int carCounter = 0;
    bool prevSpawnStatus;
    EndStruct spawnTarget;

    float secondaryTimer; //The secondary timer is for when the spawning fails and so it doesnt spam the spawncar

    public Queue<EndStruct> requestLine;
    public Queue<EndStruct> backlog; //For unsuccessful spawn

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
        requestLine = new Queue<EndStruct>();
        backlog = new Queue<EndStruct>();

        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
        //    //spawnManager = GameObject.Find("SpawnManager").GetComponent<SpawnManager>();
        //    //maxTimer = aiDirector.carSpawnTimerInterval;
        //    //structureModel = GetComponent<StructureModel>();
        spawnTimer = 0f;
        spawnTimerMax = 1f;

        prevSpawnStatus = true;
        secondaryTimer = 0f;
    }
    //
    public override void Update()
    {
        dt = Time.deltaTime;
        //Debug.Log(entityId + " " + requestLine.Count + " " + backlog.Count);
        //If previous car spawn fails, try again in 2 second)
        //if (!prevSpawnStatus) {
        //    secondaryTimer += dt;
        //    if (secondaryTimer < 2f)
        //        return;
        //    secondaryTimer = 0f;
        //    Debug.Log("Retrying again");
        //}

        //Debug.Log("Count " + carCounter);
        //FOR TESTING TO BE REMOVED----------------------------
        if (Input.GetKeyDown(KeyCode.T) && Input.GetKey(KeyCode.Shift))
        {
            if (backlog.Count != 0)
            {
                spawnTarget = backlog.Dequeue();

                if (SpawnCurrentSpawnTarget()) return;
                //Debug.Log("Try main queue");
            }

            if (requestLine.Count != 0)
            {
                spawnTarget = requestLine.Dequeue();

                SpawnCurrentSpawnTarget();
            }
        }
        //--------------------------------------------------------

        //Debug.Log(requestLine.Count + " backlog " + backlog.Count);
        if (requestLine.Count != 0 || backlog.Count != 0)
        {
            spawnTimer += dt;

            if (spawnTimer >= spawnTimerMax && carCounter == 0)
            {

                if (backlog.Count != 0) {
                    spawnTarget = backlog.Dequeue();

                    if (SpawnCurrentSpawnTarget()) return;
                }

                if (requestLine.Count != 0)
                {
                    spawnTarget = requestLine.Dequeue();

                    SpawnCurrentSpawnTarget();
                }
            }
        }
    }

    bool SpawnCurrentSpawnTarget()
    {
        prevSpawnStatus = aiDirector.SpawnCar(transform.position, spawnTarget.entityId, spawnTarget.bt, spawnTarget.endPos);
        if (prevSpawnStatus)
        {
            spawnTimer = 0f;
            return true;
        }

        backlog.Enqueue(spawnTarget);

        return false;
    }

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
