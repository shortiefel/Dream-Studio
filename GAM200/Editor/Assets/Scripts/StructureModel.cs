using System.Collections;
using System.Collections.Generic;
using System;

public class StructureModel : MonoBehaviour
{
    //float yHeight = 0;
    //private Transform transform;
    Texture texure;

    //private void Start()
    public override void Start()
    {
        transform = GetComponent<Transform>();
        texure = GetComponent<Texture>();
    }

    /*public void CreateModel(Prefab model)
    {
        //var structure = Instantiate(model, transform);
        //yHeight = structure.transform.position.y;
    }*/

    public void SwapModel(Prefab model, float rotation)
    {
        /*foreach (Transform child in transform)
        {
            Destroy(child.gameObject);
        }*/

        texure.ChangeTexture(model.name);
        transform.angle = rotation;
        /*var structure = Instantiate(model, transform);
        structure.transform.localPosition = new Vector2(0, 0);
        structure.transform.angle = rotation;*/
    }
}