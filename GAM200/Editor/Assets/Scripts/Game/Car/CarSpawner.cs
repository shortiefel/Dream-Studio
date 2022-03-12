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

    public Queue<EndStruct> requestLine;
    //GameObject.FindWithId(id).GetComponent<StructureModel>()
    public void RequestSpawn(EndStruct es)
    {
        requestLine.Enqueue(es);
    }

    AIDirector aiDirector;
    ////SpawnManager spawnManager;
    ////float timer;
    ////float maxTimer;
    ////StructureModel structureModel;
    ////
    ////Notification notification;
    float spawnTimer;
    float spawnTimerMax;
    public override void Start()
    {
        requestLine = new Queue<EndStruct>();

        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
        //    //spawnManager = GameObject.Find("SpawnManager").GetComponent<SpawnManager>();
        //    //maxTimer = aiDirector.carSpawnTimerInterval;
        //    //structureModel = GetComponent<StructureModel>();
        spawnTimer = 0f;
        spawnTimerMax = 0.6f;
        spawnTimerMax = 1f;
    }
    //
    public override void Update()
    {
        //Debug.Log("Count " + carCounter);
        //FOR TESTING TO BE REMOVED----------------------------
        if(Input.GetKeyDown(KeyCode.T))
        {
            if (requestLine.Count != 0)
            {
                EndStruct es = requestLine.Dequeue();
                aiDirector.SpawnCar(transform.position, es.entityId, es.bt, es.endPos);
                spawnTimer = 0f;
            }
        }
        //--------------------------------------------------------
        //Debug.Log(requestLine.Count);
        if (requestLine.Count != 0)
        {
            spawnTimer += Time.deltaTime;

            if (spawnTimer >= spawnTimerMax && carCounter == 0)
            {
                //Debug.Log("True Spawn");
                //Debug.Log("Spawn at " +  entityId + " line " + requestLine.Count);
                EndStruct es = requestLine.Dequeue();
                aiDirector.SpawnCar(transform.position, es.entityId, es.bt, es.endPos);
                spawnTimer = 0f;
            }
        }
        //    //timer += Time.deltaTime;
        //    //if (timer > maxTimer)
        //    //{
        //    //    if (aiDirector.SpawnAHouseCar(structureModel))
        //    //    {
        //    //        maxTimer += 3f;
        //    //        if (maxTimer > 10f) maxTimer = 10f;
        //    //    }
        //    //    //maxTimer = aiDirector.carSpawnTimerInterval;
        //    //    //spawnManager.CheckPosition();
        //    //    Debug.Log("carspawner");
        //    //
        //    //    timer = 0f;
        //    //    Debug.Log(maxTimer);
        //    //}
    }

    public override void OnTriggerEnter(Transform trans)
    {
        ++carCounter;
    }

    public override void OnTriggerExit(Transform trans)
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
