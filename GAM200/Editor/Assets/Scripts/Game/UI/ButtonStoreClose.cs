
public class ButtonStoreClose : MonoBehaviour
{
    ButtonStore buttonStore;

    public override void Start()
    {
        buttonStore = GameObject.Find("Storebtn").GetComponent<ButtonStore>();
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            buttonStore.StoreAction();
        }
    }
}

