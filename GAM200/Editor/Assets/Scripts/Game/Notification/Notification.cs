public class Notification : MonoBehaviour
{
    private float lifeTime;
    private float maxLifeTime;

    public override void Start()
    {
        lifeTime = 0f;
        maxLifeTime = 10f;
    }

    public void ResetTimer()
    {
        lifeTime = 0f;
    }

    public override void Update()
    {
        lifeTime += Time.deltaTime; // slowly add until maxLifeTime
        if (lifeTime > maxLifeTime)
        {
            //GameOver();
            Debug.Log("Lose");
        }
    }

    public void GameOver()
    {
        SceneManager.LoadScene("GameOver");
    }
}