using System;

public class ScoreSystem : MonoBehaviour
{

    //Basically this file is misnamed, it is supposed to be used in end game screen just to display the highscore
    //and not to be confused with the score system in game 

    GameState gameState;
    Text textComp;

	public override void Start()
	{
		gameState = GameObject.Find("GameManager").GetComponent<GameState>();
        textComp = GameObject.Find("CounterText").GetComponent<Text>();
    }

    public override void Update()
    {
        textComp.text = gameState.GetHighscore().ToString();
    }
}

