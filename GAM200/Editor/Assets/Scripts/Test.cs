
public class Test : MonoBehaviour
{
    //public int num;

    public override void Start()
    {
        //num = 5;
    }

    public override void Update()
    {
        //Debug.Log("From Test " + num);
    }

    public override void OnMouseEnter()
    {
        Debug.Log("From ENter ");
    }
    public override void OnMouseExit()
    {
        Debug.Log("From exit ");
    }

}