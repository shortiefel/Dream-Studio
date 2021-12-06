using System;

public class Notification : MonoBehaviour
{
    private float lifeTime;
    private float notiTime;
    private float maxLifeTime;
    private float showNotification;
    public bool shouldShow;
    public bool alreadyShowing;

    //Animation animation;

    bool appearBool;
    bool destroyBool;
    float countDownTimer;


    public override void Start()
    {
        lifeTime = 0f;
        notiTime = 0f;
        maxLifeTime =40f;
        showNotification = 0f;
        shouldShow = false;
        alreadyShowing = false;

        //animation = GetComponent<Animation>();
        countDownTimer = 0f;

        appearBool = true;
        destroyBool = false;
    }

    public void ResetTimer()
    {
        lifeTime = 0f;
        notiTime = 0f;
        showNotification = Random.Range(2, (int)(maxLifeTime / 3));
        shouldShow = false;
        alreadyShowing = true;
        //animation.Play("Appear");
        Debug.Log("Reset");
    }

    public bool AppearCheck()
    {
        if (appearBool)
        {
            countDownTimer += Time.deltaTime;
            if (countDownTimer > 0.4f)
            {
                countDownTimer = 0f;
                appearBool = false;
                //animation.Play("Stay");
                return true;
            }
        }
        return false;
    }
    public bool DestroyCheck()
    {
        if (destroyBool)
        {
            countDownTimer += Time.deltaTime;
            if (countDownTimer > 0.5f)
            {
                countDownTimer = 0f;
                destroyBool = false;
                return true;
            }
        }
        return false;
    }

    public bool NotificationUpdate()
    {
        lifeTime += Time.deltaTime; // slowly add until maxLifeTime
        if (!alreadyShowing)
            notiTime += Time.deltaTime;
        //Console.WriteLine(lifeTime);
        if (lifeTime > maxLifeTime)
        {
            //GameOver();
            //Debug.Log("Lose");
            lifeTime = 0f;
            return false;
        }
        if (notiTime > showNotification)
        {
            shouldShow = true;
            showNotification = maxLifeTime;
        }

        return true;
    }

    public void SetAnimation(string state)
    {
        countDownTimer = 0f;
    
        if (state == "Appear")
            appearBool = true;
        if (state == "Destroy")
            destroyBool = true;
    }
}