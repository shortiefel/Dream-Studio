using System.Collections;

public class ClockTutorial : MonoBehaviour
{
    Text timeText;
    Text ampmText;

    private int hour = 8;
    private int minutes = 0;
    private string ampm;
    private float timer;
    private bool switched = false;

    public override void Start()
    {
        ampmText = GameObject.Find("AMPM").GetComponent<Text>();

        timeText = GetComponent<Text>();
        timer = 48f;
        ampm = "AM";
        //timeText.text = hour.ToString() + " : " + minutes.ToString();
        timeText.text = string.Format("{0:00} : {1:00}", hour, minutes);

        ampmText.text = ampm.ToString();
    }

    public override void Update()
    {
        timer += Time.deltaTime;

        hour = (int)(timer / 6);
        minutes = (int)(timer - hour * 6);
        minutes *= 10;
        //timeText.text = hour.ToString() + " : " + minutes.ToString();

        if (timer > 72f && switched == false)
        {

            if (ampm == "AM")
                ampm = "PM";

            else if (ampm == "PM")
                ampm = "AM";

            switched = true;
        }

        if (timer >= 78f)
        {
            timer = 6f;
            switched = false;
        }

        timeText.text = string.Format("{0:00} : {1:00}", hour, minutes);
        ampmText.text = ampm.ToString();
    }
}