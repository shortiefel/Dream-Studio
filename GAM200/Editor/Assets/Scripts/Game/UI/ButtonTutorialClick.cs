using System;

public class ButtonTutorialClick : MonoBehaviour
{
    TutButtonType tbt;
    //public bool active;
    ButtonTutorial roadTab;
    ButtonTutorial buildingsTab;

    Vector2 tooltipOffset;
    //Texture lineDivider1;
    //Texture lineDivider2;
    //Texture lineDivider3;


    public override void Start()
    {
        roadTab = GameObject.Find("DisplayRoadBtn").GetComponent<ButtonTutorial>();
        buildingsTab = GameObject.Find("DisplayBuildingsBtn").GetComponent<ButtonTutorial>();

        if (entityId == GameObject.Find("DrawRoad").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Draw;
            tooltipOffset = transform.position + new Vector2(-3.60f, 7.70f);
        }

        else if (entityId == GameObject.Find("DrawRoadWhite").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Draw;
            tooltipOffset = transform.position + new Vector2(-3.60f, 7.70f);
        }

        else if (entityId == GameObject.Find("RemoveRoad").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Remove;
            tooltipOffset = transform.position + new Vector2(-6.00f, 7.70f);
        }

        else if (entityId == GameObject.Find("RemoveRoadWhite").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.Remove;
            tooltipOffset = transform.position + new Vector2(-6.00f, 7.70f);
        }

        else if (entityId == GameObject.Find("RemoveCar").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.RemoveCar;
            tooltipOffset = transform.position + new Vector2(-8.80f, 7.70f);
        }

        else if (entityId == GameObject.Find("RemoveCarWhite").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.RemoveCar;
            tooltipOffset = transform.position + new Vector2(-8.80f, 7.70f);
        }

        else if (entityId == GameObject.Find("ERPbtn").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.ERP;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("ERPbtnWhite").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.ERP;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("TrafficLight").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.TrafficLight;
            tooltipOffset = transform.position + new Vector2(-10.10f, 7.70f);
        }

        else if (entityId == GameObject.Find("TrafficLightWhite").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.TrafficLight;
            tooltipOffset = transform.position + new Vector2(-10.10f, 7.70f);
        }

        //else if (entityId == GameObject.Find("Displaybtn").GetComponent<Transform>().entityId)
        //{
        //    //Debug.Log("selected1");
        //    bt = ButtonType.Display;
        //    tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        //}
        //
        //else if(entityId == GameObject.Find("DisplaybtnWhite").GetComponent<Transform>().entityId)
        //{
        //    bt = ButtonType.Display;
        //    tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        //}

        else if (entityId == GameObject.Find("PlaceHospital").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.PlaceHospital;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("PlaceOffice").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.PlaceOffice;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("PlacePark").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.PlacePark;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("PlaceMall").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.PlaceMall;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("PlacePoliceStation").GetComponent<Transform>().entityId)
        {
            tbt = TutButtonType.PlacePoliceStation;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }
      


    }
    public override void OnMouseOver()
    {
        switch (tbt)
        {

            case TutButtonType.Draw:
                {
                    if (Input.GetMouseButtonDown(MouseCode.Left))
                        roadTab.CallFunctionTut(tbt);

                    roadTab.SetToolTips(true, tooltipOffset, "Road");
                    //Enable<Transform>(tooltipTrans);
                    //tooltipText.text = "Road";
                    break;
                }
            //case TutButtonType.Remove:
            //    {
            //        if (Input.GetMouseButtonDown(MouseCode.Left))
            //            roadTab.CallFunctionTut(tbt);

            //        roadTab.SetToolTips(true, tooltipOffset, "Remove Road");
            //        //Enable<Transform>(tooltipTrans);
            //        //tooltipText.text = "Remove ";
            //        break;
            //    }
            //case TutButtonType.ERP:
            //    {
            //        if (Input.GetMouseButtonDown(MouseCode.Left))
            //            roadTab.CallFunctionTut(tbt);

            //        roadTab.SetToolTips(true, tooltipOffset, "ERP");
            //        //Enable<Transform>(tooltipTrans);
            //        //tooltipText.text = "ERP";
            //        break;
            //    }
            //case TutButtonType.TrafficLight:
            //    {
            //        if (Input.GetMouseButtonDown(MouseCode.Left))
            //            roadTab.CallFunctionTut(tbt);

            //        roadTab.SetToolTips(true, tooltipOffset, "TrafficLight");
            //        //Enable<Transform>(tooltipTrans);
            //        //tooltipText.text = "TrafficLight";
            //        break;
            //    }
            //case TutButtonType.RemoveCar:
            //    {
            //        if (Input.GetMouseButtonDown(MouseCode.Left))
            //            roadTab.CallFunctionTut(tbt);

            //        roadTab.SetToolTips(true, tooltipOffset, "Remove Car");
            //        //Enable<Transform>(tooltipTrans);
            //        //tooltipText.text = "Remove Car";
            //        break;
            //    }

            //case TutButtonType.PlaceHospital:
            //    {
            //        if (Input.GetMouseButtonDown(MouseCode.Left))
            //        {
            //            buildingsTab.CallFunctionTut(tbt);
            //        }

            //        buildingsTab.SetToolTips(true, tooltipOffset, "Place Hospital");
            //        //Enable<Transform>(tooltipTrans);
            //        //tooltipText.text = "Place Hospital";

            //        break;
            //    }
            //case TutButtonType.PlaceOffice:
            //    {
            //        if (Input.GetMouseButtonDown(MouseCode.Left))
            //        {
            //            buildingsTab.CallFunctionTut(tbt);
            //        }

            //        buildingsTab.SetToolTips(true, tooltipOffset, "Place Office");
            //        //Enable<Transform>(tooltipTrans);
            //        //tooltipText.text = "Place Office";

            //        break;
            //    }
            //case TutButtonType.PlacePark:
            //    {
            //        if (Input.GetMouseButtonDown(MouseCode.Left))
            //        {
            //            buildingsTab.CallFunctionTut(tbt);
            //        }

            //        buildingsTab.SetToolTips(true, tooltipOffset, "Place Park");
            //        //Enable<Transform>(tooltipTrans);
            //        //tooltipText.text = "Place Park";

            //        break;
            //    }
            //case TutButtonType.PlaceMall:
            //    {
            //        if (Input.GetMouseButtonDown(MouseCode.Left))
            //        {
            //            buildingsTab.CallFunctionTut(tbt);
            //        }

            //        buildingsTab.SetToolTips(true, tooltipOffset, "Place Mall");
            //        //Enable<Transform>(tooltipTrans);
            //        //tooltipText.text = "Place Mall";

            //        break;
            //    }
            //case TutButtonType.PlacePoliceStation:
            //    {
            //        if (Input.GetMouseButtonDown(MouseCode.Left))
            //        {
            //            buildingsTab.CallFunctionTut(tbt);
            //        }

            //        buildingsTab.SetToolTips(true, tooltipOffset, "Place Police Station");

            //        break;
            //    }
            default:

                break;
        }
        //}
    }

    public override void OnMouseEnter()
    {
        InputManager.allowBuilding = false;
    }

    public override void OnMouseExit()
    {
        InputManager.allowBuilding = true;
        //roadTab.SetToolTips(false, Vector2.zero);
        //buildingsTab.SetToolTips(false, Vector2.zero);
    }

    //public override void OnEnable()
    //{
    //    Debug.Log("Enabling \n");
    //}
}