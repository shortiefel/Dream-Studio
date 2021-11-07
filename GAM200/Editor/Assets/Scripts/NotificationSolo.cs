using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class NotificationSolo : MonoBehaviour
{
    private float lifeTime; 
    private float maxLifeTime = 40f;

    public override void OnEnable()
    {
        lifeTime = 0f;
    }

    // Update is called once per frame
    public override void Update()
    {
        lifeTime += Time.deltaTime;
        if (lifeTime > maxLifeTime)
        {
            // if the notification takes too long and there's no car spawn 
            // display end game UI
            //MassNotification.Instance.ReturnNPrefab(this.gameObject);
            if (Input.GetKeyDown(KeyCode.C))
            {
                MassNotification.Instance.ReturnNPrefab(this.gameObject);
            }
            else 
            {
                GameOver();
            }
            
        }
    }

    public void GameOver()
        {
            SceneManager.LoadScene("GameOver");
        } 
}
