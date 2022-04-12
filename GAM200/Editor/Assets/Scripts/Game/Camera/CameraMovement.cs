using System;

//public enum ZoomType
//{
//    In = 0,
//    Out
//}
public class CameraMovement : MonoBehaviour
{

    Camera cam;
    PlacementManager placementManager;

    public bool toZoomLose;
    public bool toZoomExpand;

    //public bool drawMode;

    bool hasEnter;
    float targetHeight, startHeight;
    //float tempZoomHeight;
    float t;

    Vector2 targetPosition;
    Vector2 startPosition;

    //Vector3 mousePosition;
    //float mouseMultiply;

    bool gameZoom;
    public float minZoom;
    public float maxZoom;
    //ZoomType zt;

    private float zoomHeight;

    public float minScrollSpeed;
    public float scrollSpeed;

    private Vector2 moveUpSpeed;
    private Vector2 moveRightSpeed;
    private float camSpeed, maxSpeed;

    private Vector2 cameraPosition;

    private bool positionChange;

    float dt;
    public override void Start()
    {
        toZoomLose = false;
        toZoomExpand = false;
        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        cam = GetComponent<Camera>();
        startHeight = cam.height;
        //tempZoomHeight = cam.height;
        targetHeight = 4f;
        t = 0f;
        hasEnter = false;

        //mousePosition = Input.GetMousePosition();
        //mouseMultiply = 0.15f;

        gameZoom = false;
        //zt = ZoomType.Out;

        zoomHeight = cam.height;

        minScrollSpeed = scrollSpeed = 60f;

        minZoom = 8f;
        maxZoom = 10f;
        camSpeed = 0f;
        maxSpeed = 10f;

        moveUpSpeed = 0.5f * transform.up;
        moveRightSpeed = 0.5f * transform.right;

        cameraPosition = transform.position;

        positionChange = false;
    }

    public override void Update()
    {
        dt = Time.unscaledDeltaTime;

        if (toZoomExpand)
        {
            t += dt;
            //if (t > 1f) t = 1f;
            zoomHeight = Mathf.Lerp(cam.height, maxZoom, t);
            if (zoomHeight >= maxZoom)
            {
                zoomHeight = maxZoom;
                t = 0.0f;
                toZoomExpand = false;
            }
            cam.height = zoomHeight;
        }

       
        cam.height = zoomHeight;

        if (Input.GetKey(KeyCode.W))
        {
            camSpeed = dt * maxSpeed * (zoomHeight / maxZoom);
            cameraPosition.y += camSpeed;
            positionChange = true;
        }
        else if (Input.GetKey(KeyCode.S))
        {
            camSpeed = dt * maxSpeed * (zoomHeight / maxZoom);
            cameraPosition.y -= camSpeed;
            positionChange = true;
        }
        if (Input.GetKey(KeyCode.A))
        {
            camSpeed = dt * maxSpeed * (zoomHeight / maxZoom);
            cameraPosition.x -= camSpeed;
            positionChange = true;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            camSpeed = dt * maxSpeed * (zoomHeight / maxZoom);
            cameraPosition.x += camSpeed;
            positionChange = true;
        }

        zoomHeight -= Input.GetMouseScroll().y * (scrollSpeed * (zoomHeight / maxZoom)) * dt;
        if (zoomHeight < minZoom) zoomHeight = minZoom;
        else if (zoomHeight > maxZoom) zoomHeight = maxZoom;

        if (positionChange)
        {
            //Check position before set (with the border)
            if (placementManager != null)
            {
                Vector2Int sp = placementManager.placementGrid.GetStartPoint();
                Vector2Int ep = placementManager.placementGrid.GetGridSize();
                ep += sp;

                if (cameraPosition.x < sp.x) cameraPosition.x = sp.x;
                else if (cameraPosition.x > ep.x) cameraPosition.x = ep.x;

                if (cameraPosition.y < sp.y) cameraPosition.y = sp.y;
                else if (cameraPosition.y > ep.y) cameraPosition.y = ep.y;
            }


            transform.position = cameraPosition;
            positionChange = false;
        }
    }

    public override void FixedUpdate()
    {
        //For when game lose and zoom in to the target
        if (toZoomLose)
        {
            t += Time.unscaledDeltaTime;
            if (t > 1f) t = 1f;
            float h = cam.height = Mathf.Lerp(startHeight, targetHeight, t);
            transform.position = new Vector2(Mathf.Lerp(startPosition.x, targetPosition.x, t), Mathf.Lerp(startPosition.y, targetPosition.y, t));

            if (h < targetHeight + 0.2)
            {
                toZoomLose = false;
                Time.timeScale = 1f;
                SceneManager.LoadScene("GameOver");
            }
        }
       

        //else if (drawMode)
        {
            //if (Input.GetMouseButton(MouseCode.Right))
            //{
            //    Vector3 offset = Input.GetMousePosition() - mousePosition;
            //    transform.position -= new Vector2(offset.x * mouseMultiply, offset.y * mouseMultiply);
            //    
            //}

            //if (Input.GetMouseButton(MouseCode.Middle))
            //{
            //    //Vector3 offset = Input.GetMousePosition() - mousePosition;
            //    //transform.position -= new Vector2(offset.x * mouseMultiply, offset.y * mouseMultiply);
            //    
            //}
            
        }

        //mousePosition = Input.GetMousePosition();

        //if (gameZoom)
        //{
        //    t += 5f * Time.unscaledDeltaTime;
        //    if (t > 1f) t = 1f;
        //    cam.height = Mathf.Lerp(startHeight, targetHeight, t);
        //}
    }

    public void SetTargetPosition(Vector2 _pos)
    {
        if (hasEnter) return;
        targetPosition = _pos;
        startPosition = transform.position;
        startHeight = cam.height;
        t = 0f;
        hasEnter = true;
    }

    //public void SetZoom(ZoomType _zoomType)
    //{
    //    zt = _zoomType;
    //    switch (zt)
    //    {
    //        case ZoomType.In:
    //            //zt = ZoomType.In;
    //            //targetHeight = minZoom;
    //            zoomHeight = minZoom;
    //            break;
    //        case ZoomType.Out:
    //            //zt = ZoomType.Out;
    //            //targetHeight = maxZoom;
    //            //zoomHeight = maxZoom;
    //            break;
    //    }
    //    //startHeight = cam.height;
    //    //t = 0f;
    //    //gameZoom = true;
    //}

    public void Expand()
    {
        maxZoom += 6f;
        scrollSpeed *= 1.3f;
        //minZoom *= 0.5f;
        toZoomExpand = true;
        //SetZoom(ZoomType.Out);
    }
}