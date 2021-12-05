using System.Collections;
using System.Collections.Generic;
using System;
public class CarSpawner : MonoBehaviour
{
    AIDirector aiDirector;
    SpawnManager spawnManager;
    float timer;
    float maxTimer;
    StructureModel structureModel;
    public override void Start()
    {
        timer = 0f;
        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
        spawnManager = GameObject.Find("SpawnManager").GetComponent<SpawnManager>();
        maxTimer = aiDirector.carSpawnTimerInterval;
        structureModel = GetComponent<StructureModel>();
    }

    public override void Update()
    {
        timer += Time.deltaTime;
        if (timer > maxTimer)
        {
            aiDirector.SpawnAHouseCar(structureModel);
            //maxTimer = aiDirector.carSpawnTimerInterval;
            //spawnManager.CheckPosition();
            Debug.Log("carspawner");

            timer = 0f;
            maxTimer += 3f;
            Debug.Log(maxTimer);
        }
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
