using System;
public class Test : MonoBehaviour
{
    //public int num;
    RoadFixer roadFixer;
    public override void Start()
    {
        //Debug.Log("Test start");
        roadFixer = GameObject.Find("RoadManager").GetComponent<RoadFixer>();
    }

    public override void Update()
    {
        //Debug.Log("From Test ");
        /*if (Input.GetMouseButtonDown(2))
        {
            var gameObject = Instantiate(roadFixer.deadEnd);
            var structureModel = gameObject.AddComponent<StructureModel>();
            structureModel.SwapModel(roadFixer.deadEnd, 0); //not needed
        }*/
    }

    public override void OnMouseEnter()
    {
        //Debug.Log("From ENter ");
    }
    public override void OnMouseExit()
    {
        //Debug.Log("From exit ");
    }

}