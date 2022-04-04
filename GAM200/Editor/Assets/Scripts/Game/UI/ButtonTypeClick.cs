using System;

public class ButtonTypeClick : MonoBehaviour
{
    ButtonType bt;
    bool type;
    //public bool active;
    ButtonRoad buttonRoad;
    Text tooltipText;
    Transform tooltipTrans;
    Vector2 tooltipOffset;
    //Texture lineDivider1;
    //Texture lineDivider2;
    //Texture lineDivider3;


    public override void Start()
    {
        buttonRoad = GameObject.Find("ButtonRoad").GetComponent<ButtonRoad>();
        tooltipText = GameObject.Find("stringname").GetComponent<Text>();
        tooltipTrans = GameObject.Find("stringname").GetComponent<Transform>();

        //lineDivider1 = GameObject.Find("Line1").GetComponent<Texture>();
        //lineDivider2 = GameObject.Find("Line2").GetComponent<Texture>();
        //lineDivider3 = GameObject.Find("Line3").GetComponent<Texture>();


        if (entityId == GameObject.Find("DrawRoad").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Draw;
            type = true;
            //active = true;
        }

        else if(entityId == GameObject.Find("DrawRoadWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Draw;
            type = false;
            //active = false;
        }

        else if (entityId == GameObject.Find("RemoveRoad").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Remove;
            type = true;
            //active = true;
        }

        else if(entityId == GameObject.Find("RemoveRoadWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Remove;
            type = false;
            //active = false;
        }

        else if (entityId == GameObject.Find("ERPbtn").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.ERP;
            type = true;
            //active = true;
        }

        else if (entityId == GameObject.Find("ERPbtnWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.ERP;
            type = false;
            //active = false;
        }

        else if (entityId == GameObject.Find("TrafficLight").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.TrafficLight;
            type = true;
            //active = true;
        }

        else if (entityId == GameObject.Find("TrafficLightWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.TrafficLight;
            type = false;
            //active = false;
        }

       if (entityId == GameObject.Find("Displaybtn").GetComponent<Transform>().entityId)
        {
            //Debug.Log("selected1");
            bt = ButtonType.Display;
            type = true;
            //Debug.Log("selected2");
            //active = true;
        }

        if (entityId == GameObject.Find("DisplaybtnWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Display;
            type = false;
            
            //active = false;
        }

        tooltipOffset = transform.position + new Vector2(-2f, 8.5f);
    }
    public override void OnMouseOver()
    {

        //if (!transform.isActive) return;
        if (transform.isActive)
        {
            switch (bt)
            {
                case ButtonType.Display:
                    if( Input.GetMouseButtonDown(MouseCode.Left))
                    {
                        buttonRoad.SwitchTabRoad(type);
                    }

                    Enable<Transform>(tooltipTrans);
                    tooltipTrans.position = tooltipOffset;
                    tooltipText.text =  "Display buttons";

                    break;

                case ButtonType.Draw:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonRoad.CallFunction(bt, type);

                        Enable<Transform>(tooltipTrans);
                        tooltipTrans.position = tooltipOffset;
                        tooltipText.text = "Road";
                        break;
                    }
                case ButtonType.Remove:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonRoad.CallFunction(bt, type);

                        Enable<Transform>(tooltipTrans);
                        tooltipTrans.position = tooltipOffset;
                        tooltipText.text = "Remove ";
                        break;
                    }
                case ButtonType.ERP:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonRoad.CallFunction(bt, type);

                        Enable<Transform>(tooltipTrans);
                        tooltipTrans.position = tooltipOffset;
                        tooltipText.text = "ERP";
                        break;
                    }
                case ButtonType.TrafficLight:
                    {
                        if (Input.GetMouseButtonDown(MouseCode.Left))
                            buttonRoad.CallFunction(bt, type);

                        Enable<Transform>(tooltipTrans);
                        tooltipTrans.position = tooltipOffset;
                        tooltipText.text = "TrafficLight";
                        break;
                    }
                default:
                    
                    break;
            }
        //Debug.Log("Entity " + entityId + " " + transform.isActive);
            
            //switch (bt)
            //{
            //    case ButtonType.Draw:
            //        break;
            //
            //    case ButtonType.Remove:
            //        break;
            //
            //    case ButtonType.ERP:
            //        break;
            //
            //    case ButtonType.TrafficLight:
            //        break;
            //}
        }
    }

    public override void OnMouseExit()
    {

        //if (!transform.isActive) return;
        if (transform.isActive)
        {
            switch (bt)
            {
                case ButtonType.Display:
                case ButtonType.Draw:
                case ButtonType.Remove:
                case ButtonType.ERP:
                case ButtonType.TrafficLight:
                    Disable<Transform>(tooltipTrans);

                    break;
                default:
                    
                    break;
            }
            //Debug.Log("Entity " + entityId + " " + transform.isActive);

            //switch (bt)
            //{
            //    case ButtonType.Draw:
            //        break;
            //
            //    case ButtonType.Remove:
            //        break;
            //
            //    case ButtonType.ERP:
            //        break;
            //
            //    case ButtonType.TrafficLight:
            //        break;
            //}
        }
    }

    public override void OnEnable()
    {
        Debug.Log("Enabling \n");
    }
}
