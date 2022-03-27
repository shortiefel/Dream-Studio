
public class TilesValues : MonoBehaviour
{
    RoadManager roadManager;

    Text buttonRoadCountText;
    Text buttonTrafficCountText;
    Text buttonERPCountText;

    

    public override void Start()
    {
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();

        buttonRoadCountText = GameObject.Find("currRoadDisplay").GetComponent<Text>();
        buttonTrafficCountText = GameObject.Find("currTrafficDisplay").GetComponent<Text>();
        buttonERPCountText = GameObject.Find("currERPDisplay").GetComponent<Text>();


    }

    public override void Update()
    {
        buttonRoadCountText.text = roadManager.roadCount.ToString();
        buttonTrafficCountText.text = roadManager.trafficLightManager.tlCount.ToString();
        buttonERPCountText.text = roadManager.erpManager.erpCount.ToString();
    }
}

