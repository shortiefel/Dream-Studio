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

struct TimerGroup
{
    public float timer;
    public bool active;
    //public int count;

    public TimerGroup(float _timer, bool _active)
    {
        timer = _timer;
        active = _active;
        //count = 0;
    }
}
public class CarSpawner : MonoBehaviour
{
    GameState gameState;

    float warningLifeTime;
    float maxLifeTime;

    PosIdSet[] possibleDest; //Contains previously spawned dest (for efficency)
    Vector2Int selfPos;

    BuildingType outBt;
    PosIdSet posIdSet;

    int carCounter = 0;

    //bool prevSpawnStatus;
    //EndStruct spawnTarget;

    private GameObject notifiSymbol;
    private Texture notifiTexture;
    private bool isNotifiActive;
    private BuildingType currentNotifiType;
    private float notifiFlashTimer;
    private bool notifiFlashDirection; //true = minus, false = plus

    public Queue<EndStruct> requestLine;
    public Queue<EndStruct> backlog; //For unsuccessful spawn

    public Queue<BuildingType> backlogNew; //For unsuccessful spawn
    //Dictionary<BuildingType, int> backlogCounter; //For unsuccessful spawn

    //GameObject.FindWithId(id).GetComponent<StructureModel>()
    public void RequestSpawn(EndStruct es)
    {
        requestLine.Enqueue(es);
    }

    AIDirector aiDirector;

    float spawnTimer;
    float spawnTimerMax;

    float dt;

    TimerGroup[] lifeTimeArray;

    public override void Start()
    {
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        maxLifeTime = 80f;
        //maxLifeTime = 20f;
        warningLifeTime = 0.7f * maxLifeTime;

        possibleDest = new PosIdSet[(int)BuildingType.House];
        selfPos = new Vector2Int(transform.position);

        requestLine = new Queue<EndStruct>();
        backlog = new Queue<EndStruct>();

        backlogNew = new Queue<BuildingType>();
        //backlogCounter = new Dictionary<BuildingType, int>();

        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
        //    //spawnManager = GameObject.Find("SpawnManager").GetComponent<SpawnManager>();
        //    //maxTimer = aiDirector.carSpawnTimerInterval;
        //    //structureModel = GetComponent<StructureModel>();
        spawnTimer = 0f;
        spawnTimerMax = 4f;
        //spawnTimerMax = 10f;

        //prevSpawnStatus = true;

        notifiSymbol = Instantiate(new Prefab("Popup"), new Vector3(transform.position.x, transform.position.y + 1f, 0f), 4);
        notifiTexture = notifiSymbol.GetComponent<Texture>();
        Disable<Transform>(notifiSymbol.transform);
        isNotifiActive = false;
        currentNotifiType = BuildingType.Hospital;
        notifiFlashTimer = 1f;
        notifiFlashDirection = true;


        lifeTimeArray = new TimerGroup[(int)BuildingType.House];
        lifeTimeArray[(int)BuildingType.Hospital] = new TimerGroup(0f, false);
        lifeTimeArray[(int)BuildingType.Mall] = new TimerGroup(0f, false);
        lifeTimeArray[(int)BuildingType.Office] = new TimerGroup(0f, false);
        lifeTimeArray[(int)BuildingType.Park] = new TimerGroup(0f, false);
        lifeTimeArray[(int)BuildingType.PoliceStation] = new TimerGroup(0f, false);

    }
    //
    public override void Update()
    {
        dt = Time.deltaTime;

        CheckLifetime(dt);

        if (Input.GetKey(KeyCode.X))
            for (int i = 0; i < (int)BuildingType.House; i++)
            {
                Debug.Log((BuildingType)i + " " + lifeTimeArray[i].timer);
            }
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
                BuildingType _bt = backlogNew.Peek();
                //Debug.Log("Trying to s")
                if (aiDirector.SpawnAtTypeDest(selfPos, _bt))
                {
                    backlogNew.Dequeue();
                    DisableNotification(_bt);

                    spawnTimer = 0f;
                    return;
                }

                else
                {
                    EnableNotification(_bt);
                }
            }

            if (aiDirector.SelectADestAndSpawn(selfPos, possibleDest, out outBt, out posIdSet))
            {
                //Debug.Log("    " + posIdSet.pos);
                possibleDest[(int)outBt] = posIdSet;
                //Debug.Log(" aaaa " + possibleDest[(int)outBt].pos);

                lifeTimeArray[(int)outBt].timer = 0f;
                lifeTimeArray[(int)outBt].active = false;

                spawnTimer = 0f;
            }

            else
            {
                if (outBt != BuildingType.None)
                {
                    if (lifeTimeArray[(int)outBt].active) return;
                    backlogNew.Enqueue(outBt);
                    EnableNotification(outBt);
                }

                Debug.Log("Enqueue " + outBt);
                spawnTimer = 0f;
            }
        }

    }

    public override void OnTriggerEnter(uint entId)
    {
        ++carCounter;
    }

    public override void OnTriggerExit(uint entId)
    {
        --carCounter;
    }

    private void EnableNotification(BuildingType _bt)
    {
        //lifeTimeArray[(int)_bt].count = 1;
        lifeTimeArray[(int)_bt].active = true;

        if (isNotifiActive) return;

        currentNotifiType = _bt;
        Enable<Transform>(notifiSymbol.transform);
        isNotifiActive = true;

        switch (_bt)
        {
            case BuildingType.Hospital:
                {
                    notifiTexture.ChangeTexture("Game/Houses/Hospital");
                    break;
                }
            case BuildingType.Mall:
                {
                    notifiTexture.ChangeTexture("Game/Houses/ShoppingMall");
                    break;
                }
            case BuildingType.Office:
                {
                    notifiTexture.ChangeTexture("Game/Houses/Office");
                    break;
                }
            case BuildingType.Park:
                {
                    notifiTexture.ChangeTexture("Game/Houses/Park");
                    break;
                }
            case BuildingType.PoliceStation:
                {
                    notifiTexture.ChangeTexture("Game/Houses/PoliceStation");
                    break;
                }

        }
    }

    private void DisableNotification(BuildingType _bt)
    {
        lifeTimeArray[(int)_bt].timer = 0f;
        //lifeTimeArray[(int)_bt].count = 0;
        lifeTimeArray[(int)_bt].active = false;

        Disable<Transform>(notifiSymbol.transform);
        isNotifiActive = false;

        notifiTexture.color = new Color(1f, 1f, 1f);
        notifiFlashTimer = 1f;
        notifiFlashDirection = true;
    }

    private void CheckLifetime(float dt)
    {
        for (int i = 0; i < (int)BuildingType.House; i++)
        {
            if (lifeTimeArray[i].active)
                lifeTimeArray[i].timer += dt;

            if (lifeTimeArray[i].timer > maxLifeTime)
            {
                lifeTimeArray[i].timer = 0f;
                gameState.MissedDestinationTime((BuildingType)i);

                if ((int)currentNotifiType == i)
                    notifiTexture.color = new Color(1f, 1f, 1f);
            }
        }

        if (lifeTimeArray[(int)currentNotifiType].timer > warningLifeTime)
        {
            if (notifiFlashDirection)
            {
                notifiFlashTimer -= dt;

                if (notifiFlashTimer < 0f) notifiFlashDirection = false;
            }
            else
            {
                notifiFlashTimer += dt;

                if (notifiFlashTimer > 1f) notifiFlashDirection = true;
            }

            notifiTexture.color = new Color(1f, notifiFlashTimer, notifiFlashTimer);
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
