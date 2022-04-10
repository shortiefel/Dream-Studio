using System.Collections;
using System.Collections.Generic;
using System;


struct DestToHouseSet
{
    public Vector2 startPos;
    public Vector2Int endPos;
    public BuildingType bt;

    public DestToHouseSet(Vector2 _startPos, Vector2Int _endPos, BuildingType _bt)
    {
        startPos = _startPos;
        endPos = _endPos;
        bt = _bt;
    }
}

//struct TimerGroup
//{
//    public float timer;
//    public bool active;
//
//    public TimerGroup(float _timer, bool _active)
//    {
//        timer = _timer;
//        active = _active;
//    }
//}
public class CarSpawner : MonoBehaviour
{
    //-------------Only in House-----------------
    Text popupText;
    float popupTextTimer;
    float popupTextTimerMax;
    Queue<int> popupTextQueue;

    Vector2 popupTextStartPos;
    float popupTextEndYPos;

    bool requireFading;
    float fadeTimer;
    float fadeTimerMax;

    private GameObject notifiSymbol;
    private Texture notifiTexture;
    private bool isNotifiActive;
    private BuildingType currentNotifiType;
    private float notifiFlashTimer;
    private bool notifiFlashDirection; //true = minus, false = plus

    Queue<BuildingType> backlog; //For unsuccessful spawn
    BuildingType backlogType = BuildingType.None; //For unsuccessful spawn
    float backlogTimer = 0f;

    float warningLifeTime;
    float maxLifeTime;

    //PosIdSet[] possibleDest; //Contains previously spawned dest (for efficency)
    //TimerGroup[] lifeTimeArray;

    BuildingType outBt;
    //PosIdSet posIdSet;

    int carSpawnCounter = 2;

    //-------------------------------------------

    //-------------Only in Destination-----------------
    BuildingType buildingType;

    Queue<DestToHouseSet> destToHouseQueue;
    //-------------------------------------------------


    GameState gameState;
    AIDirector aiDirector;

    Vector2Int selfPos;
    

    int carCounter = 0;
    float spawnTimer;
    float spawnTimerMax;

    float dt;


    public override void Start()
    {
        //-------------Only in House-----------------
        popupText = GetComponent<Text>();

        if (popupText != null)
        {
            popupText.alpha = 0f;
            popupTextTimer = 0f;
            popupTextTimerMax = 1f;
            popupTextQueue = new Queue<int>();

            popupTextStartPos = new Vector2(-0.29f, 0f);
            popupTextEndYPos = 0.8f;

            requireFading = false;
            fadeTimer = 0f;
            fadeTimerMax = 0.8f * popupTextTimerMax;

            notifiSymbol = Instantiate(new Prefab("Popup"), new Vector3(transform.position.x, transform.position.y + 1f, 0f), 4);
            notifiTexture = notifiSymbol.GetComponent<Texture>();
            Disable<Transform>(notifiSymbol.transform);
            isNotifiActive = false;
            currentNotifiType = BuildingType.Hospital;
            notifiFlashTimer = 1f;
            notifiFlashDirection = true;

            backlog = new Queue<BuildingType>();

            //maxLifeTime = 80f;
            maxLifeTime = 30f;
            warningLifeTime = 0.7f * maxLifeTime;

            //possibleDest = new PosIdSet[(int)BuildingType.House];

            //lifeTimeArray = new TimerGroup[(int)BuildingType.House];
            //lifeTimeArray[(int)BuildingType.Hospital] = new TimerGroup(0f, false);
            //lifeTimeArray[(int)BuildingType.Mall] = new TimerGroup(0f, false);
            //lifeTimeArray[(int)BuildingType.Office] = new TimerGroup(0f, false);
            //lifeTimeArray[(int)BuildingType.Park] = new TimerGroup(0f, false);
            //lifeTimeArray[(int)BuildingType.PoliceStation] = new TimerGroup(0f, false);

        }
        //-------------------------------------------
        else
        {
            destToHouseQueue = new Queue<DestToHouseSet>();

            Texture texure = GetComponent<Texture>();
            switch (texure.RetrieveTexture())
            {
                case "Office":
                    buildingType = BuildingType.Office;
                    break;

                case "Hospital":
                    buildingType = BuildingType.Hospital;
                    break;

                case "Park":
                    buildingType = BuildingType.Park;
                    break;

                case "ShoppingMall":
                    buildingType = BuildingType.Mall;
                    break;
                case "PoliceStation":
                    buildingType = BuildingType.PoliceStation;
                    break;
            }
        }
        //-------------------------------------------

        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();

        selfPos = new Vector2Int(transform.position);
        
        spawnTimer = 0f;
        if (popupText != null)
            spawnTimerMax = 4f;
        else
            spawnTimerMax = 0.2f;



    }
    //
    public override void Update()
    {
        dt = Time.deltaTime;

        //if(Input.GetKey(KeyCode.V)) return; //TO REMOVE
        if (Input.GetKeyDown(KeyCode.C)) gameState.ReachedDestination(BuildingType.Hospital); //TO REMOVE

        //-----------------------------------------Only in House-------------------------------------
        //Only House has popupText
        if (popupText != null)
        {
            //if (Input.GetKeyDown(KeyCode.C))
            //    for (int i = 0; i < (int)BuildingType.House; i++)
            //    {
            //        Debug.Log(entityId + " " + (BuildingType)i + " " + lifeTimeArray[i].active + " time: " + lifeTimeArray[i].timer);
            //    }

            PopupText();

            CheckLifetime(dt);
            spawnTimer += dt;
            if (carSpawnCounter != 0 && spawnTimer >= spawnTimerMax && carCounter == 0)
            //if (spawnTimer >= spawnTimerMax && carCounter == 0)
            {
                //Debug.Log("Attempt spawning ");
                spawnTimer = 0f;

                //if (backlog.Count != 0)
                if (backlogType != BuildingType.None)
                {
                    //BuildingType _bt = backlog.Peek();
                    //Debug.Log("Trying to s")
                    //if (aiDirector.SpawnRetryWithType(selfPos, _bt, entityId))
                    if (aiDirector.SpawnRetryWithType(selfPos, backlogType, entityId))
                    {
                        --carSpawnCounter;

                        //backlog.Dequeue();
                        backlogType = BuildingType.None;
                        //DisableNotification(_bt);
                        DisableNotification();

                        //spawnTimer = 0f;
                        return;
                    }

                    //else
                    //{
                    //    EnableNotification();
                    //}
                }

                //if (aiDirector.SelectADestAndSpawn(selfPos, entityId, possibleDest, out outBt, out posIdSet))
                if (aiDirector.SelectADestAndSpawn(selfPos, entityId, out outBt))
                {
                    --carSpawnCounter;

                    //Debug.Log("    " + posIdSet.pos);
                    //possibleDest[(int)outBt] = posIdSet;
                    //Debug.Log(" aaaa " + possibleDest[(int)outBt].pos);

                    //lifeTimeArray[(int)outBt].timer = 0f;
                    //lifeTimeArray[(int)outBt].active = false;

                    if (outBt == backlogType)
                    {
                        backlogType = BuildingType.None;
                        backlogTimer = 0f;
                    }

                    //spawnTimer = 0f;
                }

                else
                {
                    //if (outBt != BuildingType.None)
                    //{
                    //    if (lifeTimeArray[(int)outBt].active) return;
                    //    //backlog.Enqueue(outBt);
                    //    backlogType = outBt;
                    //    //EnableNotification(outBt);
                    //    EnableNotification(backlogType);
                    //
                    //    //
                    //}
                    //Debug.Log("Try spawn " + outBt);
                    if (outBt == BuildingType.None) return;
                    //if (backlogType != BuildingType.None || lifeTimeArray[(int)outBt].active) return;
                    if (backlogType != BuildingType.None) return;
                    //backlog.Enqueue(outBt);
                    backlogType = outBt;
                    //EnableNotification(outBt);
                    EnableNotification();
                    //Debug.Log("Set fail " + outBt);

                    //Debug.Log("Enqueue " + outBt);


                    //spawnTimer = 0f;
                }
            }
        }
        //-----------------------------------------Only in Destination-------------------------------
        else
        {
            spawnTimer += Time.deltaTime;
            if (destToHouseQueue.Count != 0 && spawnTimer > spawnTimerMax && carCounter == 0)
            {
                spawnTimer = 0f;
                DestToHouseSet dts = destToHouseQueue.Dequeue();
                aiDirector.SpawnCar(dts.startPos, 0, dts.bt, dts.endPos, RouteType.DestToHouse);
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

    //-----------------------------------------Only in House-------------------------------------

    private void PopupText()
    {
        popupTextTimer += dt;
        if (popupTextQueue.Count != 0 && popupTextTimer > popupTextTimerMax)
        {
            popupTextTimer = 0f;

            popupText.alpha = 1f;

            int value = popupTextQueue.Dequeue();
            if (value > 0)
            {
                popupText.text = "+" + value.ToString();
                popupText.color = new Color(0f, 1f, 0f);
            }
            else
            {
                popupText.text = value.ToString();
                popupText.color = new Color(1f, 0f, 0f);
            }

            requireFading = true;
            fadeTimer = 0f;
            popupText.position = popupTextStartPos;
        }

        if (requireFading)
        {
            fadeTimer += Time.fixedDeltaTime;

            popupText.position = new Vector2(popupText.position.x, Mathf.Lerp(popupText.position.y, popupTextEndYPos, fadeTimer));

            if (fadeTimer > fadeTimerMax)
            {
                popupText.alpha -= 0.1f;
                if (popupText.alpha <= 0f)
                {
                    fadeTimer = 0f;
                    requireFading = false;
                }
            }
        }
    }
    //private void EnableNotification(BuildingType _bt)
    private void EnableNotification()
    {
        //lifeTimeArray[(int)_bt].count = 1;
        //lifeTimeArray[(int)_bt].active = true;
        //backlogType = _bt;

        if (isNotifiActive) return;

        //currentNotifiType = _bt;
        Enable<Transform>(notifiSymbol.transform);
        isNotifiActive = true;

        switch (backlogType)
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

    //private void DisableNotification(BuildingType _bt)
    private void DisableNotification()
    {
        //lifeTimeArray[(int)_bt].timer = 0f;
        ////lifeTimeArray[(int)_bt].count = 0;
        //lifeTimeArray[(int)_bt].active = false;

        Disable<Transform>(notifiSymbol.transform);
        isNotifiActive = false;

        notifiTexture.color = new Color(1f, 1f, 1f);
        notifiFlashTimer = 1f;
        notifiFlashDirection = true;
    }

    private void CheckLifetime(float dt)
    {
        if (backlogType != BuildingType.None)
            backlogTimer += dt;

        if (backlogTimer > maxLifeTime)
        {
            popupTextQueue.Enqueue(-GameState.minusMoneyValue);

            backlogTimer = 0f;
            gameState.MissedDestinationTime(backlogType);

            notifiTexture.color = new Color(1f, 1f, 1f);
        }

        if (backlogTimer > warningLifeTime)
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

        //for (int i = 0; i < (int)BuildingType.House; i++)
        //{
        //    if (lifeTimeArray[i].active)
        //        lifeTimeArray[i].timer += dt;
        //
        //    if (lifeTimeArray[i].timer > maxLifeTime)
        //    {
        //        popupTextQueue.Enqueue(-GameState.minusMoneyValue);
        //
        //        lifeTimeArray[i].timer = 0f;
        //        gameState.MissedDestinationTime((BuildingType)i);
        //
        //        if ((int)currentNotifiType == i)
        //            notifiTexture.color = new Color(1f, 1f, 1f);
        //    }
        //}

        //if (lifeTimeArray[(int)currentNotifiType].timer > warningLifeTime)
        //{
        //    if (notifiFlashDirection)
        //    {
        //        notifiFlashTimer -= dt;
        //
        //        if (notifiFlashTimer < 0f) notifiFlashDirection = false;
        //    }
        //    else
        //    {
        //        notifiFlashTimer += dt;
        //
        //        if (notifiFlashTimer > 1f) notifiFlashDirection = true;
        //    }
        //
        //    notifiTexture.color = new Color(1f, notifiFlashTimer, notifiFlashTimer);
        //}
    }

    public void DisplayPopup()
    {
        carSpawnCounter++;
        popupTextQueue.Enqueue(GameState.addMoneyValue);
    }

    //If destroyed before reaching destination
    public void AddToCarCounter()
    {
        carSpawnCounter++;
    }
    //-------------------------------------------------------------------------------------------

    //-----------------------------------------Only in Destination-------------------------------
    public void Notify(Vector2 spawnPoint, Vector2Int nextDest)
    {
        gameState.ReachedDestination(buildingType);

        destToHouseQueue.Enqueue(new DestToHouseSet(spawnPoint, nextDest, buildingType));
    }
    //-------------------------------------------------------------------------------------------
}
