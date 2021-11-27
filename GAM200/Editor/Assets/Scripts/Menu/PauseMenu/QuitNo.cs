
public class QuitNo : MonoBehaviour
{
    PauseMenu pauseMenu;
    public override void Start()
    {
        pauseMenu = GameObject.Find("PauseIcon").GetComponent<PauseMenu>();
    }
    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            pauseMenu.QuitNoAction();
        }
    }
}