using System;
using System.Collections.Generic;
using System.Linq;


public class TimeSystem : MonoBehaviour
{
    public override void Update()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            Time.timeScale = 1f;
        }

        if (Input.GetKeyDown(KeyCode.W))
        {
            Time.timeScale = 0f;
        }

        if (Input.GetKeyDown(KeyCode.E))
        {
            Time.timeScale = 3f;
        }
    }
}