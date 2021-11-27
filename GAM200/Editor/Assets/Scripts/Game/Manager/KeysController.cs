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

    // Update is called once per frame
    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.R))
        {
            //OnRoadPlacement?.Invoke();
            if (OnRoadPlacement != null)
                OnRoadPlacement.Invoke();
        }

        else if (Input.GetKeyDown(KeyCode.H))
        {
            //Debug.Log("pressed h");
            //OnHousePlacement?.Invoke();
            if (OnHousePlacement != null)
                OnHousePlacement.Invoke();
        }

        else if (Input.GetKeyDown(KeyCode.P))
        {
            //OnSpecialPlacement?.Invoke();
            if (OnSpecialPlacement != null)
                OnSpecialPlacement.Invoke();
        }

        else if (Input.GetKeyDown(KeyCode.C))
        {
            aiDirector.SpawnACar();
        }
    }
}
