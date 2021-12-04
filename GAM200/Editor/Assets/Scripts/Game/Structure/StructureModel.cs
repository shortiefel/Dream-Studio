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

    Animation animation;

    //private Prefab notifiPrefab;
    private GameObject notifiSymbol;
    public override void Start()
    {
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        transform = GetComponent<Transform>();
        texure = GetComponent<Texture>();
        notification = GetComponent<Notification>();
        //carSpawner = GetComponent<CarSpawner>();
        animation = GetComponent<Animation>();

        if (notification != null)
        {
            //notifiPrefab = ;
            Vector2 center = transform.localPosition;
            
            notifiSymbol = Instantiate(new Prefab("Notification"), new Vector3(center.x, center.y + 0.7f, 0f), 4);
        }
    }

    public override void Update()
    {
        if (notification != null && notification.shouldShow == true)
        {
            Enable<Transform>(notifiSymbol.transform);
            notification.shouldShow = false;
            notification.ResetTimer();
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
            Disable<Transform>(notifiSymbol.transform);
            if (animation != null)
                animation.Play("Destroy");
            //notification.transform.
            gameState.IncrementScore();
            notification.ResetTimer();
        }
    }
}