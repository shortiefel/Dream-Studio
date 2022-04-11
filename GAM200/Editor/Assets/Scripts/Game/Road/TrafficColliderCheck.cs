
public class TrafficColliderCheck : MonoBehaviour
{
    public int carCount = 0;

    public override void OnTriggerEnter(uint entId)
    {
        if (entId == TrafficLight.ignoreId) return;
        ++carCount;
    }

    public override void OnTriggerExit(uint entId)
    {
        if (entId == TrafficLight.ignoreId) return;
        --carCount;
    }
}

