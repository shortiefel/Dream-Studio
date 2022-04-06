
public class QuitYes : MonoBehaviour
{
    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Application.Quit();
        }
    }
}