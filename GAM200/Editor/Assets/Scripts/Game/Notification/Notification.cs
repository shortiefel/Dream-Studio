using System;

//public class Notification : MonoBehaviour
//{
//    //InstructionsClick timerNoti;
//    //GameObject go1;
//    //
//    //private float lifeTime;
//    //private float notiTime;
//    //private float maxLifeTime;
//    //private float showNotification;
//    //private GameObject notifiSymbol;
//    //public bool shouldShow;
//    //public bool timerShow;
//    //public bool alreadyShowing;
//    //public bool expirebool;
//    //
//    ////Animation animation;
//    //
//    //Vector2 center;
//    //bool appearBool;
//    //bool destroyBool;
//    //bool tappearBool;
//    //bool tdestroyBool;
//    //
//    //float countDownTimer;
//    //
//    //float dt;
//    //
//    //
//    //public override void Start()
//    //{
//    //    lifeTime = 0f;
//    //    notiTime = 0f;
//    //    maxLifeTime = 80f;
//    //    showNotification = 0f;
//    //    shouldShow = false;
//    //    timerShow = false;
//    //    alreadyShowing = false;
//    //
//    //    countDownTimer = 0f;
//    //
//    //    appearBool = true;
//    //    destroyBool = false;
//    //    tappearBool = false;
//    //    tdestroyBool = false;
//    //    expirebool = false;
//    //}
//
//    //public void ResetTimer()
//    //{
//    //    lifeTime = 0f;
//    //    notiTime = 0f;
//    //    showNotification = Random.Range(2, 10);
//    //    shouldShow = false;
//    //    alreadyShowing = true;
//    //}
//    //
//    //public bool AppearCheck()
//    //{
//    //    if (appearBool)
//    //    {
//    //        countDownTimer += Time.deltaTime;
//    //        if (countDownTimer > 0.4f)
//    //        {
//    //            countDownTimer = 0f;
//    //            appearBool = false;
//    //            //animation.Play("Stay");
//    //            return true;
//    //        }
//    //    }
//    //    return false;
//    //}
//    //public bool DestroyCheck()
//    //{
//    //    if (destroyBool)
//    //    {
//    //        countDownTimer += Time.deltaTime;
//    //        if (countDownTimer > 0.5f)
//    //        {
//    //            countDownTimer = 0f;
//    //            destroyBool = false;
//    //            return true;
//    //        }
//    //    }
//    //    return false;
//    //}
//    //public bool TickerAppearCheck()
//    //{
//    //    if (tappearBool)
//    //    {
//    //        countDownTimer += Time.deltaTime;
//    //        if (countDownTimer > 0.4f)
//    //        {
//    //            countDownTimer = 0f;
//    //            tappearBool = false;
//    //            return true;
//    //        }
//    //    }
//    //    return false;
//    //}
//    //public bool TickerDestroyCheck()
//    //{
//    //    if (tdestroyBool)
//    //    {
//    //        countDownTimer += Time.deltaTime;
//    //        if (countDownTimer > 0.5f)
//    //        {
//    //            countDownTimer = 0f;
//    //            tdestroyBool = false;
//    //            return true;
//    //        }
//    //    }
//    //    return false;
//    //}
//    //public bool NotificationUpdate()
//    //{
//    //    dt = Time.deltaTime;
//    //    //if (alreadyShowing) //Only increase timer when notification is shown
//    //        lifeTime += dt; // slowly add until maxLifeTime
//    //    if (!alreadyShowing)
//    //        notiTime += dt;
//    //
//    //    //Console.WriteLine(lifeTime);
//    //    if (lifeTime > 65.0f)
//    //    {
//    //        timerShow = true;
//    //    }
//    //    if (lifeTime > maxLifeTime)
//    //    {
//    //        //GameOver();
//    //        //Debug.Log("BREAK HERE");
//    //        expirebool = true;
//    //        lifeTime = 0f;
//    //        return false;
//    //    }
//    //    if (notiTime > showNotification)
//    //    {
//    //        Debug.Log("Enter here once");
//    //        shouldShow = true;
//    //        //showNotification = maxLifeTime;
//    //    }
//    //    //Debug.Log(lifeTime);
//    //    //if (Input.GetKeyDown(KeyCode.H)) Debug.Log(lifeTime + " " + entityId);
//    //    return true;
//    //}
//    //
//    //public void SetAnimation(string state)
//    //{
//    //    countDownTimer = 0f;
//    //
//    //    if (state == "Appear")
//    //        appearBool = true;
//    //    if (state == "Destroy")
//    //        destroyBool = true;
//    //    if (state == "TickingAppear")
//    //        tappearBool = true;
//    //    if (state == "TickingClose")
//    //        tdestroyBool = true;
//    //
//    //}
//}