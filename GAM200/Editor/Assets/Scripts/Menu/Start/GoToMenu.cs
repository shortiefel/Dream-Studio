public class GoToMenu : MonoBehaviour
{
    //Text text;
 

    public override void Update()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Time.timeScale = 1;
            SceneManager.LoadScene("MainMenu");
        }
    }
}
