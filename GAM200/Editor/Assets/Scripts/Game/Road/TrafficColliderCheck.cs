
public class TrafficColliderCheck : MonoBehaviour
{
    public int carCount = 0;

    public override void OnTriggerEnter(uint entId)
    {
        ++carCount;
        //Debug.Log("The id is " + id);
    }

    public override void OnTriggerExit(uint entId)
    {

        --carCount;
    }
}

