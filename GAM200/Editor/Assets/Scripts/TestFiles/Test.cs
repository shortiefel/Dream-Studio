using System;
using System.Collections.Generic;

public class Test : MonoBehaviour
{


    public override void Start()
    {
    }

    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.F))
        {
            Instantiate(new GameObject(new Prefab("Box")));
        }
       
    }

    

}