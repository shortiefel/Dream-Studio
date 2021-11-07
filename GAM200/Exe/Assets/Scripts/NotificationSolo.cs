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

    public static NotificationSolo Instance { get; private set; }

    public override void Awake()
    {
        if (Instance != null)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }

    public override void OnEnable()
    {
        lifeTime = 0f;
    }

    // Update is called once per frame
    public override void Update()
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
            lifeTime += Time.deltaTime; // slowly add until 40f
            if (lifeTime > maxLifeTime)
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
