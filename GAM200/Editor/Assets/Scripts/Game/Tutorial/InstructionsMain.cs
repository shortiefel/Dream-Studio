﻿
public class InstructionsMain : MonoBehaviour
{
    InstructionsClick instructions1Script;
    InstructionsClick instructions2Script;
    InstructionsClick instructions3Script;
    InstructionsClick instructions4Script;

    Tutorial tutorial;

    int stages;
    public override void Start()
    {
        instructions1Script = GameObject.Find("Instructions1").GetComponent<InstructionsClick>();
        instructions2Script = GameObject.Find("Instructions2").GetComponent<InstructionsClick>();
        instructions3Script = GameObject.Find("Instructions3").GetComponent<InstructionsClick>();
        instructions4Script = GameObject.Find("Instructions4").GetComponent<InstructionsClick>();

        tutorial = GameObject.Find("TutorialManager").GetComponent<Tutorial>();

        stages = 0;
    }

    public override void Update()
    {
        if (stages == 0)
        {
            if (instructions1Script.state)
            {
                Disable<Transform>(GameObject.Find("Instructions1").GetComponent<Transform>());
                Enable<Transform>(GameObject.Find("Instructions2").GetComponent<Transform>());
                stages++;
            }
        }

        else if (stages == 1)
        {
            if (instructions2Script.state)
            {
                Disable<Transform>(GameObject.Find("Instructions2").GetComponent<Transform>());
                Enable<Transform>(GameObject.Find("Instructions3").GetComponent<Transform>());
                //Spawn here
                tutorial.CheckPosition();
                stages++;
            }
        }
        else if (stages == 2)
        {
            if (instructions3Script.state)
            {
                Disable<Transform>(GameObject.Find("Instructions3").GetComponent<Transform>());
                Enable<Transform>(GameObject.Find("Instructions4").GetComponent<Transform>());
                stages++;
            }
        }
        else if (stages == 3)
        {
            if (instructions4Script.state)
            {
                Disable<Transform>(GameObject.Find("Instructions4").GetComponent<Transform>());
                //Enable<Transform>(GameObject.Find("Instructions4").GetComponent<Transform>());
                SceneManager.LoadScene("NewGame");
                stages++;
            }
        }
    }
}
