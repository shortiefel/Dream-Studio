
public class InstructionsMain : MonoBehaviour
{
    InstructionsClick instructions1Script;
    InstructionsClick instructions2Script;
    InstructionsClick instructions3Script;
    InstructionsClick instructions4Script;
    InstructionsClick instructions5Script;
    InstructionsClick instructions6Script;

    GameObject go1;
    GameObject go2;
    GameObject go3;
    GameObject go4;
    GameObject go5;
    GameObject go6;

    Tutorial tutorial;

    int stages;
    float timer;
    bool stateCheck;

    public override void Start()
    {
        instructions1Script = GameObject.Find("Instructions1").GetComponent<InstructionsClick>();
        instructions2Script = GameObject.Find("Instructions2").GetComponent<InstructionsClick>();
        instructions3Script = GameObject.Find("Instructions3").GetComponent<InstructionsClick>();
        instructions4Script = GameObject.Find("Instructions4").GetComponent<InstructionsClick>();
        instructions5Script = GameObject.Find("Instructions5").GetComponent<InstructionsClick>();
        instructions6Script = GameObject.Find("Instructions6").GetComponent<InstructionsClick>();

        go1 = GameObject.Find("Instructions1");
        go2 = GameObject.Find("Instructions2");
        go3 = GameObject.Find("Instructions3");
        go4 = GameObject.Find("Instructions4");
        go5 = GameObject.Find("Instructions5");
        go6 = GameObject.Find("Instructions6");

        go1.GetComponent<Animation>().Play("Open");


        tutorial = GameObject.Find("TutorialManager").GetComponent<Tutorial>();


        stages = 0;
        timer = 0;
        stateCheck = true;
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

    public override void Update()
    {
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
                if (stateCheck)
                {
                    instructions2Script.animation.Play("Close");
                    stateCheck = false;
                }
                if (CheckTimer())
                {
                    Disable<Transform>(go2.GetComponent<Transform>());

                    instructions3Script.animation.Play("Open");
                    Enable<Transform>(go3.GetComponent<Transform>());
                    stages++;
                    stateCheck = true;
                    instructions2Script.state = false;

                    tutorial.CheckPosition();
                }
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
        }
        else if (stages == 3)
        {
            if (instructions4Script.state)
            {
                if (stateCheck)
                {
                    instructions4Script.animation.Play("Close");
                    stateCheck = false;
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
        }
        else if (stages == 4)
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
        else if (stages == 5)
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

