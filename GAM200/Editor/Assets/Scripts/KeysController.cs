using DreamExpress.AI;
using System;
using System.Collections;
using System.Collections.Generic;

public class KeysController : MonoBehaviour
{
    public Action OnRoadPlacement, OnHousePlacement, OnSpecialPlacement;

    public AIDirector aiDirector;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown("r"))
        {
            OnRoadPlacement?.Invoke();
        }

        else if (Input.GetKeyDown("h"))
        {
            //Debug.Log("pressed h");
            OnHousePlacement?.Invoke();
        }

        else if (Input.GetKeyDown("p"))
        {
            OnSpecialPlacement?.Invoke();
        }

        else if (Input.GetKeyDown("c"))
        {
            aiDirector.SpawnACar();
        }
    }
}
