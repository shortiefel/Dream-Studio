﻿using System;

public class QuitButton : MonoBehaviour
{
    Text text;
    Texture texture;

    Transform areYouSure;
    Transform quitYes;
    Transform quitNo;

    public override void Start()
    {
        Console.WriteLine("going in start play");

        text = GetComponent<Text>();
        texture = GameObject.Find("Quitbtn").GetComponent<Texture>();

        areYouSure = GameObject.Find("AreYouSureText").GetComponent<Transform>();
        quitYes = GameObject.Find("YesText").GetComponent<Transform>();
        quitNo = GameObject.Find("NoText").GetComponent<Transform>();

    }

    public override void OnMouseEnter()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }

    public override void OnMouseOver()
    {
        //Console.WriteLine("Quit selected");
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Enable<Transform>(areYouSure);
            Enable<Transform>(quitYes);
            Enable<Transform>(quitNo);
        }                     
    }                         

    public override void OnMouseExit()
    {
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(0f, 0f, 0f);
    }
}