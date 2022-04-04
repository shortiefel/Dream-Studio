using System;

public class ButtonTutorialClick : MonoBehaviour
{
    TutButtonType tbt;
    //public bool active;
    ButtonTutorial buttonTut;
   
    Vector2 tooltipOffset;
    //Texture lineDivider1;
    //Texture lineDivider2;
    //Texture lineDivider3;


    public override void Start()
    {
        buttonTut = GameObject.Find("TutorialRoad").GetComponent<ButtonTutorial>();
     

        if (entityId == GameObject.Find("DrawRoad").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Draw;
            tooltipOffset = transform.position + new Vector2(-3.60f, 7.70f);
            //active = true;
        }

        else if (entityId == GameObject.Find("RemoveRoad").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Remove;
            tooltipOffset = transform.position + new Vector2(-6.00f, 7.70f);
            //active = true;
        }

        else if (entityId == GameObject.Find("RemoveCar").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.RemoveCar;
            tooltipOffset = transform.position + new Vector2(-8.80f, 7.70f);
        }

        else if (entityId == GameObject.Find("PlaceHospital").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.PlaceHospital;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
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


        //if (entityId == GameObject.Find("Displaybtn").GetComponent<Transform>().entityId)
        //{
        //    //Debug.Log("selected1");
        //    tbt = TutButtonType.Display;
        //    type = true;
        //    //Debug.Log("selected2");
        //    //active = true;
        //}

        //if (entityId == GameObject.Find("DisplayGlow").GetComponent<Transform>().entityId)
        //{
        //    //Debug.Log("selected1");
        //    tbt = TutButtonType.Display;
        //    type = true;
        //    //Debug.Log("selected2");
        //    //active = true;
        //}



        //tooltipOffset = transform.position + new Vector2(-2f, 6.5f);

    }
    public override void OnMouseOver()
    {

        //if (!transform.isActive) return;
        if (transform.isActive)
        {
            switch (tbt)
            {
                //case TutButtonType.Display:
                //    if (Input.GetMouseButtonDown(MouseCode.Left))
                //    {
                //        //Debug.Log("Calling for switich");
                //        buttonTut.SwitchTabTut(type);
                //    }

                //    Enable<Transform>(tooltipTrans);
                //    tooltipTrans.position = tooltipOffset;
                //    tooltipText.text = "Display buttons";

                //    break;

                case TutButtonType.Draw:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonTut.CallFunctionTut(tbt);

                        buttonTut.SetToolTips(true, tooltipOffset, "Road");

                        //Enable<Transform>(tooltipTrans);
                        //tooltipTrans.position = tooltipOffset;
                        //tooltipText.text = "Road";
                        break;
                    }
                case TutButtonType.Remove:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonTut.CallFunctionTut(tbt);

                        buttonTut.SetToolTips(true, tooltipOffset, "Remove Road");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipTrans.position = tooltipOffset;
                        //tooltipText.text = "Remove ";
                        break;
                    }
                case TutButtonType.RemoveCar:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonTut.CallFunctionTut(tbt);

                        buttonTut.SetToolTips(true, tooltipOffset, "Remove Car");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "Remove Car";
                        break;
                    }
                case TutButtonType.PlaceHospital:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            buttonTut.CallFunctionTut(tbt);
                        }

                        buttonTut.SetToolTips(true, tooltipOffset, "Place Hospital");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "Place Hospital";

                        break;
                    }

                default:

                    break;
            }

        }
    }

    public override void OnMouseExit()
    {
        buttonTut.SetToolTips(false, Vector2.zero);

        //if (!transform.isActive) return;
        //if (transform.isActive)
        //{
        //    switch (tbt)
        //    {
        //        case TutButtonType.Display:
        //        case TutButtonType.Draw:
        //        case TutButtonType.Remove:
        //            Disable<Transform>(tooltipTrans);

        //            break;
        //        default:

        //            break;
        //    }

        //}
    }

    public override void OnEnable()
    {
        Debug.Log("Enabling \n");
    }
}