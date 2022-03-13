﻿using System;

public class MenuHowToPlay : MonoBehaviour
{
    Text text;
    Texture texture;
    Camera cam;

    public override void Start()
    {
        

        text = GetComponent<Text>();
        texture = GameObject.Find("HowToPlaybtn").GetComponent<Texture>();
        cam = GameObject.Find("Camera").GetComponent<Camera>();
    }

    public override void OnMouseEnter()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }

    public override void OnMouseOver()
    {
        //Console.WriteLine(Input.GetMousePosition());
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Console.WriteLine("Play");
            SceneManager.LoadScene("MenuHowToPlay");
        }
    }

    public override void OnMouseExit()
    {
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(0f, 0f, 0f);
    }
}