using System;

public class HelperPageTip : MonoBehaviour
{

    public override void Update()
    {
        if (transform.isActive && Input.GetMouseButtonDown(MouseCode.Left))
        {
            Disable<Transform>(transform);
            Time.timeScale = 1f;

            Enable<Transform>(GameObject.Find("MoneyText").GetComponent<Transform>());
            Enable<Transform>(GameObject.Find("CounterText").GetComponent<Transform>());
            Enable<Transform>(GameObject.Find("Displaybtn").GetComponent<Transform>());
        }
    }
}