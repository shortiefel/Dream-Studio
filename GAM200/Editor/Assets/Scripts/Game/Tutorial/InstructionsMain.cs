
public class InstructionsMain : MonoBehaviour
{
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

    Tutorial tutorial;
    RoadManager roadManager;

    Transform displayArrowGlow;
    Transform drawRoadGlow;
    Transform removeRoadGlow;

    Transform roadCount;

    int stages, count;
    float timer;
    bool stateCheck;

    bool clickCheck;

    public override void Start()
    {
        clickCheck = false;
        roadCount = GameObject.Find("currRoadDisplay").GetComponent<Transform>();

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


        go1.GetComponent<Animation>().Play("Open");


        tutorial = GameObject.Find("TutorialManager").GetComponent<Tutorial>();
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();

        displayArrowGlow = GameObject.Find("DisplayGlow").GetComponent<Transform>();
        drawRoadGlow = GameObject.Find("DrawRoadGlow").GetComponent<Transform>();
        removeRoadGlow = GameObject.Find("RemoveRoadGlow").GetComponent<Transform>();

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


    /**
  *     1. intro game (1 , 2) 
         2. teach user how to move camera (8)
         3. teach user how to zoom in (9)
         4. Click Display button (7)
         5. Show that road counter = 0 
         6. Click store (10)
         7. Buy road 
         8. draw road (3)
         9. Timer (11)
         10. Lets play (6) 
  */

    public override void Update()
    {

        /****************************************************************** INTRO GAME ******************************************************************************/
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

        /****************************************************************** CAMERA (WASD) ******************************************************************************/
        else if (stages == 1)
        {
            if (instructions2Script.state)
            {
                if (stateCheck)
                {
                    instructions2Script.animation.Play("Close");
                    stateCheck = false;
                }
                if (CheckTimer())
                {
                    Disable<Transform>(go2.GetComponent<Transform>());
                    instructions8Script.animation.Play("Open");
                    Enable<Transform>(go8.GetComponent<Transform>());
                    stages++;
                    stateCheck = true;
                    instructions2Script.state = false;

                   

                }
            }
        }

        /****************************************************************** SCROLL WHEEL  ******************************************************************************/
        else if (stages == 2)
        {
            if (Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.A)
                      || Input.GetKeyDown(KeyCode.S) || Input.GetKeyDown(KeyCode.D))
            {
                clickCheck = true;
            }

            if (clickCheck && instructions8Script.state)
            {
                if (stateCheck)
                {

                    instructions8Script.animation.Play("Close");
                    stateCheck = false;
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

        }

        /****************************************************************** DISPLAY BUTTON  ******************************************************************************/
        else if (stages == 3)
        {
            if (instructions9Script.state)
            {
                if (stateCheck)
                {
                    instructions9Script.animation.Play("Close");
                    stateCheck = false;
                }
                if (CheckTimer())
                {
                    Disable<Transform>(go9.GetComponent<Transform>());
                    instructions7Script.animation.Play("Open");
                    Enable<Transform>(go7.GetComponent<Transform>());
                    stages++;
                    stateCheck = true;
                    instructions7Script.state = false;

                    tutorial.CheckPosition();
                    count = roadManager.roadCount;

                    Enable<Transform>(displayArrowGlow);
                }
            }
        }

        /****************************************************************** ROAD DRAWING ******************************************************************************/
        else if (stages == 4)
        {
            if (instructions7Script.state)
            {
                if (stateCheck)
                {
                    instructions7Script.animation.Play("Close");
                    stateCheck = false;

                    Disable<Transform>(displayArrowGlow);
                }
                if (CheckTimer())
                {
                    Disable<Transform>(go7.GetComponent<Transform>());
                    instructions3Script.animation.Play("Open");
                    Enable<Transform>(go3.GetComponent<Transform>());
                    stages++;
                    stateCheck = true;
                    instructions3Script.state = false;

                    //Enable<Transform>(drawRoadGlow);
                }
            }
        }

        /****************************************************************** TIMER ******************************************************************************/
        else if (stages == 5)
        {
            if (instructions3Script.state)
            {
                if (roadManager.roadCount < 20)
                {
                    if (stateCheck)
                    {
                        instructions3Script.animation.Play("Close");
                        stateCheck = false;

                       ///Disable<Transform>(drawRoadGlow);
                    }
                    if (CheckTimer())
                    {
                        Disable<Transform>(go3.GetComponent<Transform>());
                        instructions11Script.animation.Play("Open");
                        Enable<Transform>(go11.GetComponent<Transform>());
                        stages++;
                        stateCheck = true;
                        instructions11Script.state = false;
                    }
                }

            }
        }

        /****************************************************************** REMOVE ROAD ******************************************************************************/
        else if (stages == 6)
        {
            if (instructions11Script.state)
            {
                if (stateCheck)
                {
                    instructions11Script.animation.Play("Close");
                    stateCheck = false;
                }
                if (CheckTimer())
                {
                    Disable<Transform>(go11.GetComponent<Transform>());
                    instructions4Script.animation.Play("Open");
                    Enable<Transform>(go4.GetComponent<Transform>());
                    stages++;
                    stateCheck = true;
                    instructions4Script.state = false;
                    count = roadManager.roadCount;

                    //Enable<Transform>(removeRoadGlow);

                }
            }
        }

        /****************************************************************** REMOVING  ******************************************************************************/
        else if (stages == 7)
        {
            if (instructions4Script.state)
            {
                if (roadManager.roadCount > count)
                {
                    if (stateCheck)
                    {
                        instructions4Script.animation.Play("Close");
                        stateCheck = false;

                        //Disable<Transform>(removeRoadGlow);
                    }
                    if (CheckTimer())
                    {

                        Disable<Transform>(removeRoadGlow);

                        Disable<Transform>(go4.GetComponent<Transform>());

                        instructions5Script.animation.Play("Open");
                        Enable<Transform>(go5.GetComponent<Transform>());
                        stages++;
                        stateCheck = true;
                        instructions4Script.state = false;
                    }
                }
            }
        }

        /****************************************************************** LOCATION PING ******************************************************************************/
        else if (stages == 8)
        {
            if (instructions5Script.state)
            {
                if (stateCheck)
                {
                    instructions5Script.animation.Play("Close");
                    stateCheck = false;
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
        }

        /****************************************************************** LOAD NEW GAME ******************************************************************************/
        else if (stages == 9)
        {
            if (instructions6Script.state)
            {
                if (stateCheck)
                {
                    instructions6Script.animation.Play("Close");
                    stateCheck = false;
                }
                if (CheckTimer())
                {
                    Disable<Transform>(go6.GetComponent<Transform>());

                    SceneManager.LoadScene("NewGame");
                    stages++;
                    stateCheck = true;
                    instructions6Script.state = false;
                }
            }
        }

     

    }
}
