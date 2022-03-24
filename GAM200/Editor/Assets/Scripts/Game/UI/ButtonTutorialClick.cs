using System;

public class ButtonTutorialClick : MonoBehaviour
{
    TutButtonType tbt;
    bool type;
    //public bool active;
    ButtonTutorial buttonTut;
    Text tooltipText;
    Transform tooltipTrans;
    Vector2 tooltipOffset;
    //Texture lineDivider1;
    //Texture lineDivider2;
    //Texture lineDivider3;


    public override void Start()
    {
        buttonTut = GameObject.Find("TutorialRoad").GetComponent<ButtonTutorial>();
        tooltipText = GameObject.Find("stringname").GetComponent<Text>();
        tooltipTrans = GameObject.Find("stringname").GetComponent<Transform>();


        if (entityId == GameObject.Find("DrawRoad").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Draw;
            type = true;
            //active = true;
        }

        else if (entityId == GameObject.Find("DrawRoadWhite").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Draw;
            type = false;
            //active = false;
        }

        else if (entityId == GameObject.Find("RemoveRoad").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Remove;
            type = true;
            //active = true;
        }

        else if (entityId == GameObject.Find("RemoveRoadWhite").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Remove;
            type = false;
            //active = false;
        }
        //else if (entityId == GameObject.Find("RemoveRoadGlow").GetComponent<Transform>().entityId)
        //{
        //    tbt = TutButtonType.Remove;
        //    type = false;
        //    //active = false;
        //}
        //else if (entityId == GameObject.Find("DrawRoadGlow").GetComponent<Transform>().entityId)
        //{
        //    tbt = TutButtonType.Draw;
        //    type = false;
        //    //active = false;
        //}


        if (entityId == GameObject.Find("Displaybtn").GetComponent<Transform>().entityId)
        {
            //Debug.Log("selected1");
            tbt = TutButtonType.Display;
            type = true;
            //Debug.Log("selected2");
            //active = true;
        }

        //if (entityId == GameObject.Find("DisplayGlow").GetComponent<Transform>().entityId)
        //{
        //    //Debug.Log("selected1");
        //    tbt = TutButtonType.Display;
        //    type = true;
        //    //Debug.Log("selected2");
        //    //active = true;
        //}

        if (entityId == GameObject.Find("DisplaybtnWhite").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Display;
            type = false;

            //active = false;
        }

        tooltipOffset = transform.position + new Vector2(-5f, 7f);

    }
    public override void OnMouseOver()
    {

        //if (!transform.isActive) return;
        if (transform.isActive)
        {
            switch (tbt)
            {
                case TutButtonType.Display:
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        //Debug.Log("Calling for switich");
                        buttonTut.SwitchTabTut(type);
                    }

                    Enable<Transform>(tooltipTrans);
                    tooltipTrans.position = tooltipOffset;
                    tooltipText.text = "Display";

                    break;

                case TutButtonType.Draw:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonTut.CallFunctionTut(tbt, type);

                        Enable<Transform>(tooltipTrans);
                        tooltipTrans.position = tooltipOffset;
                        tooltipText.text = "Road";
                        break;
                    }
                case TutButtonType.Remove:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonTut.CallFunctionTut(tbt, type);

                        Enable<Transform>(tooltipTrans);
                        tooltipTrans.position = tooltipOffset;
                        tooltipText.text = "Remove";
                        break;
                    }

                default:

                    break;
            }

        }
    }

    public override void OnMouseExit()
    {

        //if (!transform.isActive) return;
        if (transform.isActive)
        {
            switch (tbt)
            {
                case TutButtonType.Display:
                case TutButtonType.Draw:
                case TutButtonType.Remove:
                    Disable<Transform>(tooltipTrans);

                    break;
                default:

                    break;
            }

        }
    }

    public override void OnEnable()
    {
        Debug.Log("Enabling \n");
    }
}