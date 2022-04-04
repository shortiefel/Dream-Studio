public class Clock : MonoBehaviour
{
    Text timeText;

    private int hour = 8;
    private int minutes = 0;
    private float timer;

    public override void Start()
    {
        timeText = GetComponent<Text>();
        timer = 96f;
        //timeText.text = hour.ToString() + " : " + minutes.ToString();
        timeText.text = string.Format("{0:00}:{1:00}", hour, minutes);
    }

    public override void Update()
    {
        timer += Time.deltaTime;

        hour = (int)(timer / 12);
        minutes = (int)(timer - hour * 12);
        minutes *= 5;
        //timeText.text = hour.ToString() + " : " + minutes.ToString();
        timeText.text = string.Format("{0:00}:{1:00}", hour, minutes);

        if (timer == 240f)
        {
            timer = 0f;
        }
    }
}