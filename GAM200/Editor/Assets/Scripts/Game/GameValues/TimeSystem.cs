using System;
using System.Collections.Generic;
using System.Linq;


public class TimeSystem : MonoBehaviour
{
    public override void Update()
    {
        //Normal time
        if (Input.GetKeyDown(KeyCode.Q))
        {
            NormalTime();
        }
        //Stop time
        if (Input.GetKeyDown(KeyCode.W))
        {
            StopTime();
        }
        //Speed up time
        if (Input.GetKeyDown(KeyCode.E))
        {
            SpeedUpTime();
        }
    }

    public void NormalTime()
    {
        Time.timeScale = 1f;
    }

    public void StopTime()
    {
        Time.timeScale = 0f;
    }

    public void SpeedUpTime()
    {
        Time.timeScale = 1.5f;
    }
}