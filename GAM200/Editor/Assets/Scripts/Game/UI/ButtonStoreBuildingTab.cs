//public class ButtonStoreBuildingTab : MonoBehaviour
//{
//    ButtonStore buttonStore;
//    Text text;
//    UI texture;
//    public override void Start()
//    {
//        buttonStore = GameObject.Find("BuildingTab").GetComponent<ButtonStore>();
//        text = GetComponent<Text>();
//        texture = GameObject.Find("BuildingTab").GetComponent<UI>();
//        texture.color = new Color(1f, 1f, 1f);
//        text.color = new Color(0f, 0f, 0f);
//    }
//    public override void OnMouseEnter()
//    {
//        text.color = new Color(1f, 1f, 1f);
//        texture.color = new Color(1f, 0.5f, 0f);
//    }
//    public override void OnMouseOver()
//    {
//        if (Input.GetMouseButtonDown(MouseCode.Left))
//        {
//            buttonStore.SetroadTabBool(false);
//            buttonStore.SetbuildingTabBool(true);
//            buttonStore.ToggleStore();
//        }
//    }
//    public override void OnMouseExit()
//    {
//        text.color = new Color(0f, 0f, 0f);
//        texture.color = new Color(1f, 1f, 1f);
//    }
//}