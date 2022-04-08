﻿public class TutorialInstructions : MonoBehaviour
{

    /************** Instructions scripts (1-21)***********/
    InstructionsClick instructions1Script;
    InstructionsClick instructions2Script;
    InstructionsClick instructions3Script;
    InstructionsClick instructions4Script;
    InstructionsClick instructions5Script;
    InstructionsClick instructions6Script;
    InstructionsClick instructions7Script;
    InstructionsClick instructions8Script;
    InstructionsClick instructions9Script;
    InstructionsClick instructions10Script;
    InstructionsClick instructions11Script;
    InstructionsClick instructions12Script;
    InstructionsClick instructions13Script;
    InstructionsClick instructions14Script;
    InstructionsClick instructions15Script;
    InstructionsClick instructions16Script;
    InstructionsClick instructions17Script;
    InstructionsClick instructions18Script;
    InstructionsClick instructions19Script;
    InstructionsClick instructions20Script;
    InstructionsClick instructions21Script;

    /************** game objects***********/
    GameObject go1;
    GameObject go2;
    GameObject go3;
    GameObject go4;
    GameObject go5;
    GameObject go6;
    GameObject go7;
    GameObject go8;
    GameObject go9;
    GameObject go10;
    GameObject go11;
    GameObject go12;
    GameObject go13;
    GameObject go14;
    GameObject go15;
    GameObject go16;
    GameObject go17;
    GameObject go18;
    GameObject go19;
    GameObject go20;
    GameObject go21;

    Tutorial tutorial;
    RoadManager roadManager;

    Transform roadCount;

    int stages, count;
    float timer;
    bool stateCheck;

    bool clickCheck;


    public override void Start()
    {
        clickCheck = false;
        roadCount = GameObject.Find("currRoadDisplay").GetComponent<Transform>();

        /********************getting the objects****************************/
        instructions1Script = GameObject.Find("Instructions1").GetComponent<InstructionsClick>();
        instructions2Script = GameObject.Find("Instructions2").GetComponent<InstructionsClick>();
        instructions3Script = GameObject.Find("Instructions3").GetComponent<InstructionsClick>();
        instructions4Script = GameObject.Find("Instructions4").GetComponent<InstructionsClick>();
        instructions5Script = GameObject.Find("Instructions5").GetComponent<InstructionsClick>();
        instructions6Script = GameObject.Find("Instructions6").GetComponent<InstructionsClick>();
        instructions7Script = GameObject.Find("Instructions7").GetComponent<InstructionsClick>();
        instructions8Script = GameObject.Find("Instructions8").GetComponent<InstructionsClick>();
        instructions9Script = GameObject.Find("Instructions9").GetComponent<InstructionsClick>();
        instructions10Script = GameObject.Find("Instructions10").GetComponent<InstructionsClick>();
        instructions11Script = GameObject.Find("Instructions11").GetComponent<InstructionsClick>();
        instructions12Script = GameObject.Find("Instructions12").GetComponent<InstructionsClick>();
        instructions13Script = GameObject.Find("Instructions13").GetComponent<InstructionsClick>();
        instructions14Script = GameObject.Find("Instructions14").GetComponent<InstructionsClick>();
        instructions15Script = GameObject.Find("Instructions15").GetComponent<InstructionsClick>();
        instructions16Script = GameObject.Find("Instructions16").GetComponent<InstructionsClick>();
        instructions17Script = GameObject.Find("Instructions17").GetComponent<InstructionsClick>();
        instructions18Script = GameObject.Find("Instructions18").GetComponent<InstructionsClick>();
        instructions19Script = GameObject.Find("Instructions19").GetComponent<InstructionsClick>();
        instructions20Script = GameObject.Find("Instructions20").GetComponent<InstructionsClick>();
        instructions21Script = GameObject.Find("Instructions21").GetComponent<InstructionsClick>();

        /************** game objects***********/
        go1 = GameObject.Find("Instructions1");
        go2 = GameObject.Find("Instructions2");
        go3 = GameObject.Find("Instructions3");
        go4 = GameObject.Find("Instructions4");
        go5 = GameObject.Find("Instructions5");
        go6 = GameObject.Find("Instructions6");
        go7 = GameObject.Find("Instructions7");
        go8 = GameObject.Find("Instructions8");
        go9 = GameObject.Find("Instructions9");
        go10 = GameObject.Find("Instructions10");
        go11 = GameObject.Find("Instructions11");
        go12 = GameObject.Find("Instructions12");
        go13 = GameObject.Find("Instructions13");
        go14 = GameObject.Find("Instructions14");
        go15 = GameObject.Find("Instructions15");
        go16 = GameObject.Find("Instructions16");
        go17 = GameObject.Find("Instructions17");
        go18 = GameObject.Find("Instructions18");
        go19 = GameObject.Find("Instructions19");
        go20 = GameObject.Find("Instructions20");
        go21 = GameObject.Find("Instructions21");

        /************** animation 1 starts***********/
        go1.GetComponent<Animation>().Play("Open");

        /************** managers***********/
        tutorial = GameObject.Find("TutorialManager").GetComponent<Tutorial>();
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();

        stages = 0;
        timer = 0;
        stateCheck = true;

        Disable<Transform>(roadCount);

    }

    public bool CheckTimer()
    {
        timer += Time.deltaTime;
        if (timer > 0.4f)
        {
            timer = 0;
            return true;
        }
        return false;
    }

    public override void FixedUpdate()
    {
        /****************************Intro (1-3)********************************/

        if (stages == 0)
        {
            if (instructions1Script.state)
            {
                if (stateCheck)
                {
                    instructions1Script.animation.Play("Close");
                    stateCheck = false;
                }
                if (CheckTimer())
                {
                    Disable<Transform>(go1.GetComponent<Transform>());

                    instructions2Script.animation.Play("Open");
                    Enable<Transform>(go2.GetComponent<Transform>());
                    stages++;
                    stateCheck = true;
                    instructions1Script.state = false;
                }
            }
        }

        else if (stages == 1)
        {
            if (instructions2Script.state)
            {
                if(stateCheck)
                {
                    instructions2Script.animation.Play("Close");
                    stateCheck = false;
                }
            }
            if (CheckTimer())
            {
                Disable<Transform>(go2.GetComponent<Transform>());
                instructions3Script.animation.Play("Open");
                Enable<Transform>(go3.GetComponent<Transform>());
                stages++;
                stateCheck = true;
                instructions2Script.state = false;
            }
            
        }

        else if (stages == 2)
        {
            if (instructions3Script.state)
            {
                if (stateCheck)
                {
                    instructions3Script.animation.Play("Close");
                    stateCheck = false;
                }
            }
            if (CheckTimer())
            {
                Disable<Transform>(go3.GetComponent<Transform>());
                instructions4Script.animation.Play("Open");
                Enable<Transform>(go4.GetComponent<Transform>());
                stages++;
                stateCheck = true;
                instructions3Script.state = false;
            }

        }


        /****************************keypoints (4)********************************/

        else if (stages == 3)
        {
            if (instructions4Script.state)
            {
                if (stateCheck)
                {
                    instructions4Script.animation.Play("Close");
                    stateCheck = false;
                }
            }
            if (CheckTimer())
            {
                Disable<Transform>(go4.GetComponent<Transform>());
                instructions5Script.animation.Play("Open");
                Enable<Transform>(go5.GetComponent<Transform>());
                stages++;
                stateCheck = true;
                instructions4Script.state = false;
            }

        }

        /****************************WASD(5)********************************/

        else if (stages == 4)
        {
            if (Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.A)
                     || Input.GetKeyDown(KeyCode.S) || Input.GetKeyDown(KeyCode.D))
            {
                clickCheck = true;
            }

            if (clickCheck && instructions5Script.state)
            {
                if (stateCheck)
                {
                    instructions5Script.animation.Play("Close");
                    stateCheck = false;
                }
            }
            if (CheckTimer())
            {
                Disable<Transform>(go5.GetComponent<Transform>());
                instructions6Script.animation.Play("Open");
                Enable<Transform>(go6.GetComponent<Transform>());
                stages++;
                stateCheck = true;
                instructions5Script.state = false;
            }

        }

        /****************************zoom(6)********************************/

        else if (stages == 5)
        {
            if (instructions5Script.state)
            {
                if (stateCheck)
                {
                    instructions5Script.animation.Play("Close");
                    stateCheck = false;
                }
            }
            if (CheckTimer())
            {
                Disable<Transform>(go5.GetComponent<Transform>());
                instructions6Script.animation.Play("Open");
                Enable<Transform>(go6.GetComponent<Transform>());
                stages++;
                stateCheck = true;
                instructions5Script.state = false;
            }

        }

        /****************************clock (7-8)********************************/

        else if (stages == 6)
        {
            if (instructions6Script.state)
            {
                if (stateCheck)
                {
                    instructions6Script.animation.Play("Close");
                    stateCheck = false;
                }
            }
            if (CheckTimer())
            {
                Disable<Transform>(go6.GetComponent<Transform>());
                instructions7Script.animation.Play("Open");
                Enable<Transform>(go7.GetComponent<Transform>());
                stages++;
                stateCheck = true;
                instructions6Script.state = false;
            }

        }

        else if (stages == 7)
        {
            if (instructions7Script.state)
            {
                if (stateCheck)
                {
                    instructions7Script.animation.Play("Close");
                    stateCheck = false;
                }
            }
            if (CheckTimer())
            {
                Disable<Transform>(go7.GetComponent<Transform>());
                instructions8Script.animation.Play("Open");
                Enable<Transform>(go8.GetComponent<Transform>());
                stages++;
                stateCheck = true;
                instructions7Script.state = false;
            }

        }


        /****************************tut begin(9)********************************/

        else if (stages == 8)
        {
            if (instructions8Script.state)
            {
                if (stateCheck)
                {
                    instructions8Script.animation.Play("Close");
                    stateCheck = false;
                }
            }
            if (CheckTimer())
            {
                Disable<Transform>(go8.GetComponent<Transform>());
                instructions9Script.animation.Play("Open");
                Enable<Transform>(go9.GetComponent<Transform>());
                stages++;
                stateCheck = true;
                instructions8Script.state = false;
            }

        }


        /****************************build destination(10-12)********************************/

        else if (stages == 9)
        {
            if (instructions8Script.state)
            {
                if (stateCheck)
                {
                    instructions8Script.animation.Play("Close");
                    stateCheck = false;
                }
            }
            if (CheckTimer())
            {
                Disable<Transform>(go9.GetComponent<Transform>());
                instructions10Script.animation.Play("Open");
                Enable<Transform>(go10.GetComponent<Transform>());
                stages++;
                stateCheck = true;
                tutorial.CheckPosition();
                instructions8Script.state = false;
            }

        }

        /****************************build roads and car appear (13-15)********************************/


        /****************************removing car (16)********************************/


        /****************************removing road (17)********************************/


        /****************************receipt intro(18-20)********************************/


        /****************************move to game scene(21)********************************/

    }

}