public class TrafficLight : MonoBehaviour
{
    //True for left and right
    //False for top and bottom
    public bool state;
    private bool toState;

    private int carCounter;

    private Texture texture;

    private float timer;
    private float switchTimer;

    private TrafficLightManager tlm;

    public override void Start()
    {
        tlm = GameObject.Find("TrafficLightManager").GetComponent<TrafficLightManager>();
        tlm.RegisterTrafficLight(transform.position, entityId);

        state = toState = true;
        texture = gameObject.GetComponent<Texture>();
        carCounter = 0;

        timer = 0f;
        switchTimer = 2f;
    }

    public void RequestSwap(bool inState)
    {
        if (state != inState)
            toState = inState;
    }

    private void SwapState()
    {
        toState = state = !state;
        if (state)
            texture.color = new Color(1, 0, 0, 1);
        else
            texture.color = new Color(0, 1, 0, 1);
    }

    public override void Update()
    {
        //if (carCounter == 0 && state != toState)
        //    SwapState();
        timer += Time.deltaTime;
        if (timer >= switchTimer)
        {
            timer = 0f;
            SwapState();
        }
    }

    public override void OnTriggerEnter(uint id)
    {
        ++carCounter;
        Debug.Log("The id is " + id);
    }

    public override void OnTriggerExit(uint id)
    {
        --carCounter;
    }

    public override void OnDestroy()
    {
        tlm.RemoveTrafficLight(transform.position);
    }
}

