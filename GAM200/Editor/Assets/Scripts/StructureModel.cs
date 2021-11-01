using System.Collections;
using System.Collections.Generic;

public class StructureModel : MonoBehaviour
{
    //float yHeight = 0;

    public void CreateModel(GameObject model)
    {
        var structure = Instantiate(model, transform);
        //yHeight = structure.transform.position.y;
    }

    public void SwapModel(GameObject model, float rotation)
    {
        foreach (Transform child in transform)
        {
            Destroy(child.gameObject);
        }
        var structure = Instantiate(model, transform);
        structure.transform.localPosition = new Vector2(0, 0);
        structure.transform.localRotation = rotation;
    }
}
