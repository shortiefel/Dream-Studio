
public class PlayButton : MonoBehaviour
{
    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Debug.Log("Play");
            //SceneManager.LoadScene("NewGame");
        }
    }
}