using System;

public class ButtonTypeClick : MonoBehaviour
{
    ButtonType bt;
    bool type;
    //public bool active;
    ButtonRoad buttonRoad;

    public override void Start()
    {
        buttonRoad = GameObject.Find("ButtonRoad").GetComponent<ButtonRoad>();

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
            Debug.Log("selected1");
            bt = ButtonType.Display;
            type = true;
            Debug.Log("selected2");
            //active = true;
        }

        if (entityId == GameObject.Find("DisplaybtnWhite").GetComponent<Transform>().entityId)
        {
            bt = ButtonType.Display;
            type = false;
            //active = false;
        }
    }
    public override void OnMouseOver()
    {
        //if (!transform.isActive) return;
        if (transform.isActive && Input.GetMouseButtonDown(MouseCode.Left))
        {
            switch (bt)
            {
                case ButtonType.Display:
                    buttonRoad.SwitchTab(type);
                    break;
                default:
                    buttonRoad.CallFunction(bt, type);
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
