using System;
using System.Collections;
using System.Collections.Generic;

public class KeysController : MonoBehaviour
{
    public Action OnRoadPlacement, OnHousePlacement, OnSpecialPlacement;

    public AIDirector aiDirector;

    // Start is called before the first frame update
    public override void Start()
    {
        aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
    }
}
