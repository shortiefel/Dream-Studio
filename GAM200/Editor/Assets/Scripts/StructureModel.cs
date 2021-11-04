using System.Collections;
using System.Collections.Generic;

public class StructureModel : MonoBehaviour
{
    //float yHeight = 0;
    private Transform transform;

    private void Start()
    {
        transform = GetComponent<Transform>();
    }

    public void CreateModel(string model)
    {
        var structure = Instantiate(model, transform);
        //yHeight = structure.transform.position.y;
    }

    public void SwapModel(string model, float rotation)
    {
        foreach (Transform child in transform)
        {
            Destroy(child.gameObject);
        }
        var structure = Instantiate(model, transform);
        structure.transform.localPosition = new Vector2(0, 0);
        structure.transform.angle = rotation;
    }
}
