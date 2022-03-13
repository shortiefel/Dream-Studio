using System;

public class Notification : MonoBehaviour
{
    InstructionsClick timerNoti;
    GameObject go1;
    Animation animation;

    private float lifeTime;
    private float notiTime;
    private float maxLifeTime;
    private float showNotification;
    private GameObject notifiSymbol;
    public bool shouldShow;
    public bool timerShow;
    public bool alreadyShowing;

    //Animation animation;

    Vector2 center;
    bool appearBool;
    bool destroyBool;
    bool tappearBool;
    bool tdestroyBool;
    float countDownTimer;


    public override void Start()
    {
        lifeTime = 0f;
        notiTime = 0f;
        maxLifeTime = 80f;
        showNotification = 0f;
        shouldShow = false;
        timerShow = false;
        alreadyShowing = false;

        countDownTimer = 0f;

        appearBool = true;
        destroyBool = false;
        tappearBool = false;
        tdestroyBool = false;
    }

    public void ResetTimer()
    {
        lifeTime = 0f;
        notiTime = 0f;
        showNotification = Random.Range(2, 10);
        shouldShow = false;
        alreadyShowing = true;
        //animation.Play("Appear");
        //Debug.Log("Reset");
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
    public bool TickerAppearCheck()
    {
        if (tappearBool)
        {
            countDownTimer += Time.deltaTime;
            if (countDownTimer > 0.4f)
            {
                countDownTimer = 0f;
                tappearBool = false;
                return true;
            }
        }
        return false;
    }
    public bool TickerDestroyCheck()
    {
        if (tdestroyBool)
        {
            countDownTimer += Time.deltaTime;
            if (countDownTimer > 0.5f)
            {
                countDownTimer = 0f;
                tdestroyBool = false;
                return true;
            }
        }
        return false;
    }
    public bool NotificationUpdate()
    {
        //if (alreadyShowing) //Only increase timer when notification is shown
            lifeTime += Time.deltaTime; // slowly add until maxLifeTime
        if (!alreadyShowing)
            notiTime += Time.deltaTime;
        //Console.WriteLine(lifeTime);
        if (lifeTime > 65.0f)
        {
            timerShow = true;
        }
        if (lifeTime > maxLifeTime)
        {
            //GameOver();
            //Debug.Log("Lose");
            lifeTime = 0f;
            return false;
        }
        if (notiTime > showNotification)
        {
            Console.WriteLine("Enter here once");
            shouldShow = true;
            //showNotification = maxLifeTime;
        }
        //Debug.Log(lifeTime);

        return true;
    }

    public void SetAnimation(string state)
    {
        countDownTimer = 0f;
    
        if (state == "Appear")
            appearBool = true;
        if (state == "Destroy")
            destroyBool = true;
        if (state == "TickingAppear")
            tappearBool = true;
        if (state == "TickingClose")
            tdestroyBool = true;

    }
}