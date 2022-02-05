public class TrafficLight : MonoBehaviour
{
    //True for left and right
    //False for top and bottom
    public bool state;
    private bool toState;

    private int carCounter;

    //private Texture texture;

    private float timer;
    private float switchTimer;

    private TrafficLightManager tlm;

    public override void Start()
    {
        GameObject go = GameObject.Find("TrafficManager");
        if (go != null)
            tlm = go.GetComponent<TrafficLightManager>();
        if (tlm != null)
            tlm.RegisterTrafficLight(Vector2Int.RoundToInt(transform.position), entityId);

        state = toState = true;
        //texture = gameObject.GetComponent<Texture>();
        //texture.color = new Color(1, 0, 0, 1);
        transform.angle = 0;
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
            transform.angle = 0;
        //texture.color = new Color(1, 0, 0, 1);
        else
            transform.angle = 90;
        //texture.color = new Color(0, 1, 0, 1);
    }

    public override void Update()
    {
        //if (carCounter == 0 && state != toState)
        //    SwapState();
        timer += Time.deltaTime;
        if (timer >= switchTimer)
        {
            timer = 0f;
            //SwapState();
        }
        if (Input.GetKeyDown(KeyCode.C))
        {
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

    //public override void OnDestroy()
    //{
    //    Debug.Log("Traffic light destroy");
    //    if (tlm != null)
    //        tlm.RemoveTrafficLight(Vector2Int.RoundToInt(transform.position));
    //}
}

