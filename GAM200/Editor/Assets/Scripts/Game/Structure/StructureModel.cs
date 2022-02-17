using System.Collections;
using System.Collections.Generic;
using System;

public class StructureModel : MonoBehaviour, INeedingRoad
{
    //float yHeight = 0;
    //private Transform transform;
    Texture texure;
    Notification notification;
    //CarSpawner carSpawner;
    public Vector2Int RoadPosition { get; set; }

    GameState gameState;
    //AIDirector aiDirector;

    Animation animation;
    StructureModel structureModel;

    //private Prefab notifiPrefab;
    private GameObject notifiSymbol;
    private AudioSource notificationSound;
    private AudioSource destroySound;

    AIDirector aiDirector;
    bool spawnBool;

    public BuildingType buildingType;

    public override void Start()
    {
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
        //aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
        structureModel = GetComponent<StructureModel>();

        transform = GetComponent<Transform>();
        texure = GetComponent<Texture>();
        notification = GetComponent<Notification>();
        //carSpawner = GetComponent<CarSpawner>();
        //animation = GetComponent<Animation>();
        spawnBool = false;

        if (notification != null)
        {
            //notifiPrefab = ;
            //Console.WriteLine("come in here --------------------------------------------------------------------------------");
            Vector2 center = transform.localPosition;
            
            notifiSymbol = Instantiate(new Prefab("Notification"), new Vector3(center.x, center.y + 0.7f, 0f), 4);
            //notification.SetAnimation(ref notifiSymbol.GetComponent<Animation>());
            animation = notifiSymbol.GetComponent<Animation>();
            //animation.Play("Appear");
            //notification.SetAnimation("Appear");
            //spawnBool = true;
            SetToSpawn();
            notificationSound = GetComponent<AudioSource>();
            destroySound = notifiSymbol.GetComponent<AudioSource>();
            //aiDirector.SpawnACar();

            //Have to be texture names without the extension
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
            }
        }

        else
        {
            buildingType = BuildingType.House;
        }

        Debug.Log("This is " + buildingType + " -------------------------");

        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
    }

    public override void Update()
    {
        
        if (notification != null)
        {
            if (!notification.NotificationUpdate())
            {
                gameState.shouldEnd = true;
                gameState.SetLoseHouse(transform.position);
            }

            if (notification.AppearCheck())
            {
                animation.Play("Stay");
            }

            if (notification.DestroyCheck())
            {
                Disable<Transform>(notifiSymbol.transform);
                destroySound.Play();
                notification.alreadyShowing = false;
                animation.Play("Stay");
            }

            if (notification.shouldShow == true)
            {
                //animation.Play("Appear");
                //notification.SetAnimation("Appear");
                //spawnBool = true;
                SetToSpawn();
                notificationSound.Play();
                notification.shouldShow = false;
                notification.ResetTimer();
                Enable<Transform>(notifiSymbol.transform);
                
            }

            //if (spawnBool && aiDirector != null)
            //    spawnBool = !(aiDirector.SpawnToDestination(structureModel));
            if (Input.GetKeyDown(KeyCode.C))
                aiDirector.SpawnToDestination(structureModel);
        }
    }

    /*public void CreateModel(Prefab model)
    {
        //var structure = Instantiate(model, transform);
        //yHeight = structure.transform.position.y;
    }*/

    public void SwapModel(GameObject model, float rotation)
    {
        /*foreach (Transform child in transform)
        {
            Destroy(child.gameObject);
        }*/

        texure.ChangeTexture(model.name);
        transform.angle = rotation;
        /*var structure = Instantiate(model, transform);
        structure.transform.localPosition = new Vector2(0, 0);
        structure.transform.angle = rotation;*/
    }

    /*
     * Notify house that a car has reached it
    */
    public void Notify()
    {
        if (notification != null)
        {
            //Disable<Transform>(notifiSymbol.transform);
            //if (notification != null)
            if (notification.alreadyShowing)
            {
                animation.Play("Destroy");
                notification.SetAnimation("Destroy");
            }
            //notification.transform.
            gameState.IncrementScore();
            notification.ResetTimer();
        }
    }

    internal void DeleteModel()
    {
        Destroy(entityId);
    }

    void SetToSpawn()
    {
        animation.Play("Appear");
        notification.SetAnimation("Appear");
        spawnBool = true;
    }
}