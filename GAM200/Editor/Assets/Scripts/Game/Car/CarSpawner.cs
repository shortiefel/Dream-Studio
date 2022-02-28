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



    Queue<EndStruct> requestLine;
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
    public override void Start()
    {
        requestLine = new Queue<EndStruct>();

        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
    //    //spawnManager = GameObject.Find("SpawnManager").GetComponent<SpawnManager>();
    //    //maxTimer = aiDirector.carSpawnTimerInterval;
    //    //structureModel = GetComponent<StructureModel>();
    }
    //
    public override void Update()
    {
        if(Input.GetKeyDown(KeyCode.T))
        {
            if (requestLine.Count != 0)
            {
                EndStruct es = requestLine.Dequeue();
                aiDirector.SpawnCar(es.entityId, es.bt, es.endPos);
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
