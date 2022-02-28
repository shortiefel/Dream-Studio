
public class TilesValues : MonoBehaviour
{
    RoadManager roadManager;

    Text buttonRoadCountText;
    Text buttonTrafficCountText;
    Text buttonERPCountText;

    Text storeRoadText;
    Text storeTrafficText;
    Text storeERPText;

    public override void Start()
    {
        roadManager = GameObject.Find("RoadManager").GetComponent<RoadManager>();

        buttonRoadCountText = GameObject.Find("currRoadDisplay").GetComponent<Text>();
        buttonTrafficCountText = GameObject.Find("currTrafficDisplay").GetComponent<Text>();
        buttonERPCountText = GameObject.Find("currERPDisplay").GetComponent<Text>();

        storeRoadText = GameObject.Find("RoadQty").GetComponent<Text>();
        storeTrafficText = GameObject.Find("TrafficQty").GetComponent<Text>();
        storeERPText = GameObject.Find("ERPQty").GetComponent<Text>();
    }

    public override void Update()
    {
        buttonRoadCountText.text = roadManager.roadCount.ToString();
        buttonTrafficCountText.text = roadManager.trafficLightManager.tlCount.ToString();
        buttonERPCountText.text = roadManager.erpManager.erpCount.ToString();

        storeRoadText.text = roadManager.roadCount.ToString();
        storeTrafficText.text = roadManager.trafficLightManager.tlCount.ToString();
        storeERPText.text = roadManager.erpManager.erpCount.ToString();
    }
}

