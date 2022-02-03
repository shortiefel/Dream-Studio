using System;

public class RollingCredits : MonoBehaviour
{

    Camera cam;
    float timer, startHeight, EndHeight;
    Transform Rolling;

    Vector2 targetPosition;
    Vector2 startPosition;

    public override void Start()
    {
        timer = 0;
        Rolling = GameObject.Find("RollingText").GetComponent<Transform>();

        cam = GetComponent<Camera>();
        startHeight = cam.height;
        EndHeight = 10f;
    }

    public override void Update()
    {
        timer += Time.unscaledDeltaTime;
        float h = cam.height = Mathf.Lerp(startHeight, EndHeight, timer);
        //if (timer > 0)
        //{
            transform.position = new Vector2(Mathf.Lerp(startPosition.x, targetPosition.x, timer), Mathf.Lerp(startPosition.y, targetPosition.y, timer));
            
        //}
        Debug.Log(h);
       


    }
}