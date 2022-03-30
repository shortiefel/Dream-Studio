using System.Collections;
using System.Collections.Generic;
using System;


public class StructureModel : MonoBehaviour, INeedingRoad
{
    public Vector2Int RoadPosition { get; set; }

    GameState gameState;

    //AIDirector aiDirector;

    Light light;

    //If true means its waiting for day
    bool waitForDayChange = false;
    bool nightStatus;

    public override void Start()
    {
        gameState = GameObject.Find("GameManager").GetComponent<GameState>();

        light = GetComponent<Light>();
        if (light != null)
        {

            if (gameState.GetNight())
            {
                waitForDayChange = true;
            }
            else
            {
                waitForDayChange = false;
                Disable<Light>(light);
            }
        }

        //aiDirector = GameObject.Find("AIDirector").GetComponent<AIDirector>();
    }

    public override void Update()
    {
        if (light != null)
        {
            nightStatus = gameState.GetNight();
            if (!waitForDayChange && nightStatus)
            {
                //Debug.Log("Change to turn on light");
                Enable<Light>(light);
                waitForDayChange = true;
            }

            else if (waitForDayChange && !nightStatus)
            {
                //Debug.Log("Change to turn off light");
                Disable<Light>(light);
                waitForDayChange = false;
            }
        }
    }

}