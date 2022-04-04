using System;

public class ButtonTypeClick : MonoBehaviour
{
    ButtonType bt;
    //public bool active;
    ButtonRoad buttonRoad;
    //Text tooltipText;
    //Transform tooltipTrans;
    Vector2 tooltipOffset;
    //Texture lineDivider1;
    //Texture lineDivider2;
    //Texture lineDivider3;


    public override void Start()
    {
        buttonRoad = GameObject.Find("Displaybtn").GetComponent<ButtonRoad>();
        //GameObject stringNameGo = GameObject.Find("stringname");
        //tooltipText = stringNameGo.GetComponent<Text>();
        //tooltipTrans = stringNameGo.GetComponent<Transform>();

        //lineDivider1 = GameObject.Find("Line1").GetComponent<Texture>();
        //lineDivider2 = GameObject.Find("Line2").GetComponent<Texture>();
        //lineDivider3 = GameObject.Find("Line3").GetComponent<Texture>();


        if (entityId == GameObject.Find("DrawRoad").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Draw;
            tooltipOffset = transform.position + new Vector2(-3.60f, 7.70f);
        }

        else if(entityId == GameObject.Find("DrawRoadWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Draw;
            tooltipOffset = transform.position + new Vector2(-3.60f, 7.70f);
        }

        else if (entityId == GameObject.Find("RemoveRoad").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Remove;
            tooltipOffset = transform.position + new Vector2(-6.00f, 7.70f);
        }

        else if(entityId == GameObject.Find("RemoveRoadWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Remove;
            tooltipOffset = transform.position + new Vector2(-6.00f, 7.70f);
        }

        else if (entityId == GameObject.Find("ERPbtn").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.ERP;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("ERPbtnWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.ERP;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("TrafficLight").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.TrafficLight;
            tooltipOffset = transform.position + new Vector2(-10.10f, 7.70f);
        }

        else if (entityId == GameObject.Find("TrafficLightWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.TrafficLight;
            tooltipOffset = transform.position + new Vector2(-10.10f, 7.70f);
        }

        else if (entityId == GameObject.Find("RemoveCar").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.RemoveCar;
            tooltipOffset = transform.position + new Vector2(-8.80f, 7.70f);
        }
        
        else if (entityId == GameObject.Find("RemoveCarWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.RemoveCar;
            tooltipOffset = transform.position + new Vector2(-8.80f, 7.70f);
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
            bt = ButtonType.PlaceHospital;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("PlaceOffice").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.PlaceOffice;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("PlacePark").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.PlacePark;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("PlaceMall").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.PlaceMall;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }

        else if (entityId == GameObject.Find("PlacePoliceStation").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.PlacePoliceStation;
            tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        }




        //else if (entityId == GameObject.Find("PlaceHospitalWhite").GetComponent<Transform>().entityId)
        //{
        //    bt = ButtonType.PlaceHospital;
        //    tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        //}
        //
        //else if (entityId == GameObject.Find("PlaceOfficeWhite").GetComponent<Transform>().entityId)
        //{
        //    bt = ButtonType.PlaceOffice;
        //    tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        //}
        //
        //else if (entityId == GameObject.Find("PlaceParkWhite").GetComponent<Transform>().entityId)
        //{
        //    bt = ButtonType.PlacePark;
        //    tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        //}
        //
        //else if (entityId == GameObject.Find("PlaceMallWhite").GetComponent<Transform>().entityId)
        //{
        //    bt = ButtonType.PlaceMall;
        //    tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        //}
        //
        //else if (entityId == GameObject.Find("PlacePoliceStationWhite").GetComponent<Transform>().entityId)
        //{
        //    bt = ButtonType.PlacePoliceStation;
        //    tooltipOffset = transform.position + new Vector2(-2.40f, 7.70f);
        //}
    }
    public override void OnMouseOver()
    {

        //if (!transform.isActive) return;
        //if (transform.isActive)
        //{
            //tooltipTrans.position = transform.position;
            //tooltipText.position = tooltipOffset;

            switch (bt)
            {
                //case ButtonType.Display:
                //    if( Input.GetMouseButtonDown(MouseCode.Left))
                //    {
                //        //buttonRoad.SwitchTabRoad(type);
                //        buttonRoad.SwitchTabRoad();
                //    }
                //
                //    buttonRoad.SetToolTips(true, tooltipOffset, "Display buttons");
                //    //Enable<Transform>(tooltipTrans);
                //    //tooltipText.text =  "Display buttons";
                //
                //    break;

                case ButtonType.Draw:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonRoad.CallFunction(bt);

                        buttonRoad.SetToolTips(true, tooltipOffset, "Road");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "Road";
                        break;
                    }
                case ButtonType.Remove:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonRoad.CallFunction(bt);

                        buttonRoad.SetToolTips(true, tooltipOffset, "Remove Road");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "Remove ";
                        break;
                    }
                case ButtonType.ERP:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonRoad.CallFunction(bt);

                        buttonRoad.SetToolTips(true, tooltipOffset, "ERP");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "ERP";
                        break;
                    }
                case ButtonType.TrafficLight:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonRoad.CallFunction(bt);

                        buttonRoad.SetToolTips(true, tooltipOffset, "TrafficLight");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "TrafficLight";
                        break;
                    }
                case ButtonType.RemoveCar:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonRoad.CallFunction(bt);

                        buttonRoad.SetToolTips(true, tooltipOffset, "Remove Car");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "Remove Car";
                        break;
                    }

                case ButtonType.PlaceHospital:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            buttonRoad.CallFunction(bt);
                        }

                        buttonRoad.SetToolTips(true, tooltipOffset, "Place Hospital");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "Place Hospital";

                        break;
                    }
                case ButtonType.PlaceOffice:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            buttonRoad.CallFunction(bt);
                        }

                        buttonRoad.SetToolTips(true, tooltipOffset, "Place Office");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "Place Office";

                        break;
                    }
                case ButtonType.PlacePark:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            buttonRoad.CallFunction(bt);
                        }

                        buttonRoad.SetToolTips(true, tooltipOffset, "Place Park");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "Place Park";

                        break;
                    }
                case ButtonType.PlaceMall:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            buttonRoad.CallFunction(bt);
                        }

                        buttonRoad.SetToolTips(true, tooltipOffset, "Place Mall");
                        //Enable<Transform>(tooltipTrans);
                        //tooltipText.text = "Place Mall";

                        break;
                    }
                case ButtonType.PlacePoliceStation:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                        {
                            buttonRoad.CallFunction(bt);
                        }

                        buttonRoad.SetToolTips(true, tooltipOffset, "Place Police Station");

                        break;
                    }
                default:
                    
                    break;
            }

        //}
    }

    public override void OnMouseExit()
    {

        buttonRoad.SetToolTips(false, Vector2.zero);
        //if (!transform.isActive) return;
        //if (transform.isActive)
        //{
            //switch (bt)
            //{
            //    case ButtonType.Display:
            //    case ButtonType.Draw:
            //    case ButtonType.Remove:
            //    case ButtonType.ERP:
            //    case ButtonType.TrafficLight:
            //    case ButtonType.RemoveCar:
            //        Disable<Transform>(tooltipTrans);
            //
            //        break;
            //    default:
            //        
            //        break;
            //}

        //}
    }

    public override void OnEnable()
    {
        Debug.Log("Enabling \n");
    }
}
