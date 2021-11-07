/*using System.Collections;
using System.Collections.Generic;
using System;

public class CountDownSystem : MonoBehaviour
{

    public int countdownTimer;
    public TMP_Text countdownDisplay;
    public GameObject HUDOverlay;
    public GameObject PauseMenuIcon;

    public override void Start()
    {
        StartCoroutine(CountdownToStart());

        // disable all inputs
        PauseMenuIcon.SetActive(false);
    }

    private void TurnOnPauseMenu()
    {
        PauseMenuIcon.SetActive(true);
    }

    IEnumerator CountdownToStart()
    {
        while (countdownTimer > 0)
        {
            countdownDisplay.text = countdownTimer.ToString();

            yield return new WaitForSeconds(1f); //wait one seconds

            countdownTimer--;
            PauseMenuIcon.SetActive(false);
        }

        countdownDisplay.text = "GO!";

        //gameplay is allowed to start

        yield return new WaitForSeconds(1f);

        countdownDisplay.gameObject.SetActive(false);
        //HUDOverlay.gameObject.SetActive(false);
        HUDOverlay.SetActive(false);
        TurnOnPauseMenu();
    }

}
*/