
public class PauseQuitButton : MonoBehaviour
{
    PauseMenu pauseMenu;

    Text text;
    UI texture;
    private AudioSource btnClick;
    public override void Start()
    {
        pauseMenu = GameObject.Find("PauseIcon").GetComponent<PauseMenu>();
        btnClick = GetComponent<AudioSource>();
        text = GetComponent<Text>();
        texture = GameObject.Find("QuitBtn").GetComponent<UI>();
        texture.color = new Color(1f, 1f, 1f);
        text.color = new Color(0f, 0f, 0f);
    }


    public override void OnMouseEnter()
    {
        btnClick.Play();
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(1f, 0.5f, 0f);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            pauseMenu.QuitAction();
        }
    }

    public override void OnMouseExit()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }
}