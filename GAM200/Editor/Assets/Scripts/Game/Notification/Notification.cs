using System;

public class Notification : MonoBehaviour
{
    private float lifeTime;
    private float maxLifeTime;
    private float showNotification;
    public bool shouldShow;

    
    public override void Start()
    {
        lifeTime = 0f;
        maxLifeTime = 10f;
        showNotification = 0f;
        shouldShow = false;
    }

    public void ResetTimer()
    {
        lifeTime = 0f;
        showNotification = Random.Range(2, (int)(maxLifeTime / 3));
        shouldShow = false;
        Debug.Log("Reset");
    }

    public override void Update()
    {
        lifeTime += Time.deltaTime; // slowly add until maxLifeTime
        //Console.WriteLine(lifeTime);
        if (lifeTime > maxLifeTime)
        {
            //GameOver();
            //Debug.Log("Lose");
        }
        if (lifeTime > showNotification)
        {
            shouldShow = true;
            showNotification = maxLifeTime;
        }
    }

    public void GameOver()
    {
        SceneManager.LoadScene("GameOver");
    }
}