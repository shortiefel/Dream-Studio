﻿using System;

enum ZoomType
{
    In = 0,
    Out
}
public class CameraMovement : MonoBehaviour
{
    
    Camera cam;

    public bool toZoomLose;

    bool hasEnter;
    float targetHeight, startHeight;
    float t;

    Vector2 targetPosition;
    Vector2 startPosition;

    Vector3 mousePosition;
    float mouseMultiply;

    bool gameZoom;
    float minZoom;
    float maxZoom;
    ZoomType zt;

    public override void Start()
    {
        toZoomLose = false;

        cam = GetComponent<Camera>();
        startHeight = cam.height;

        targetHeight = 4f;
        t = 0f;
        hasEnter = false;

        mousePosition = Input.GetMousePosition();
        mouseMultiply = 0.15f;

        gameZoom = false;
        zt = ZoomType.Out;
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
            //Debug.Log(h);
            if (h < targetHeight + 0.2)
            {
                toZoomLose = false;
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

        if (gameZoom)
        {

        }
    }

    public void SetTargetPosition(Vector2 _pos)
    {
        if (hasEnter) return;
        targetPosition = _pos;
        startPosition = transform.position;
        hasEnter = true;
    }

    public void SetZoom()
    {
        gameZoom = true;
    }
}