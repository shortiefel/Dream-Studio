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

    private Prefab notifiPrefab;
    private GameObject notifiSymbol;
    public override void Start()
    {
        transform = GetComponent<Transform>();
        texure = GetComponent<Texture>();
        notification = GetComponent<Notification>();
        //carSpawner = GetComponent<CarSpawner>();
        
        if (notification != null)
        {
            notifiPrefab = new Prefab("Notification");
            Vector2 center = transform.localPosition;
            
            notifiSymbol = Instantiate(notifiPrefab, new Vector3(center.x, center.y + 0.7f, 0f));
        }
    }

    public override void Update()
    {
        if (notification != null && notification.shouldShow == true)
        {
            Console.WriteLine("Reshowing noti");
            Enable<Transform>(notifiSymbol.transform);
            notification.shouldShow = false;
        }
    }

    /*public void CreateModel(Prefab model)
    {
        //var structure = Instantiate(model, transform);
        //yHeight = structure.transform.position.y;
    }*/

    public void SwapModel(Prefab model, float rotation)
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
            //notification.transform.
            notification.ResetTimer();
        }
    }
}