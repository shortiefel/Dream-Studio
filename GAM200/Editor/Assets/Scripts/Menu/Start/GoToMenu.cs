﻿public class GoToMenu : MonoBehaviour
{
    Text text;
    Texture texture;
    public override void Start()
    {
        text = GetComponent<Text>();
        GameObject gameGO = GameObject.Find("GOMenu");
        if (gameGO != null)
        {
            texture = gameGO.GetComponent<Texture>();
            text.color = new Color(0f, 0f, 0f);
            texture.color = new Color(1f, 1f, 1f);
        }
    }
    public override void OnMouseEnter()
    {
        text.color = new Color(1f, 1f, 1f);
        texture.color = new Color(1f, 0.5f, 0f);
    }
    public override void Update()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Time.timeScale = 1;
            SceneManager.LoadScene("MainMenu");
        }
    }
    public override void OnMouseExit()
    {
        text.color = new Color(0f, 0f, 0f);
        texture.color = new Color(1f, 1f, 1f);
    }
}
