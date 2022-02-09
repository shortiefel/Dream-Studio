using System;
public class CameraMovement : MonoBehaviour
{
    
    Camera cam;

    public bool toZoom;

    bool hasEnter;
    float targetHeight, startHeight;
    float t;

    Vector2 targetPosition;
    Vector2 startPosition;

    Vector3 mousePosition;
    float mouseMultiply;

    public override void Start()
    {
        toZoom = false;

        cam = GetComponent<Camera>();
        startHeight = cam.height;

        targetHeight = 4f;
        t = 0f;
        hasEnter = false;

        mousePosition = Input.GetMousePosition();
        mouseMultiply = 0.3f;
    }

    public override void Update()
    {
        //For when game lose and zoom in to the target
        if (toZoom)
        {
            t += Time.unscaledDeltaTime;
            if (t > 1f) t = 1f;
            float h = cam.height = Mathf.Lerp(startHeight, targetHeight, t);
            transform.position = new Vector2(Mathf.Lerp(startPosition.x, targetPosition.x, t), Mathf.Lerp(startPosition.y, targetPosition.y, t));
            Debug.Log(h);
            if (h < targetHeight + 0.2)
            {
                toZoom = false;
                Time.timeScale = 1f;
                SceneManager.LoadScene("GameOver");
            }
        }

        else
        {
            if (Input.GetMouseButton(MouseCode.Right))
            {
                Vector3 offset = Input.GetMousePosition() - mousePosition;
                transform.position -= new Vector2(offset.x * mouseMultiply, offset.y * mouseMultiply);
            }
        }

        mousePosition = Input.GetMousePosition();
    }

    public void SetTargetPosition(Vector2 _pos)
    {
        if (hasEnter) return;
        targetPosition = _pos;
        startPosition = transform.position;
        hasEnter = true;
    }

}