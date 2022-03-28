using System.Collections;


public class CloseReceipt : MonoBehaviour
{
    GameObject roadNumber;
    GameObject tlNumber;
    GameObject erpNumber;

    GameObject roadTax;
    GameObject tlTax;
    GameObject erpTax;

    GameObject totalTax;
    GameObject balance;

    GameObject receipt;
    Transform closeTransform;

    GameState gameState;

    public override void Start()
    {
        roadNumber = GameObject.Find("RoadNum");
        //Disable<Transform>(roadNumber.transform);

        tlNumber = GameObject.Find("TrafficLightNum");
        //Disable<Transform>(tlNumber.transform);

        erpNumber = GameObject.Find("ERPNum");
        //Disable<Transform>(erpNumber.transform);

        roadTax = GameObject.Find("RoadTax");
        //Disable<Transform>(roadTax.transform);

        tlTax = GameObject.Find("TrafficLightTax");
        //Disable<Transform>(tlTax.transform);

        erpTax = GameObject.Find("ERPTax");
        //Disable<Transform>(erpTax.transform);

        totalTax = GameObject.Find("TotalTax");
        //Disable<Transform>(totalTax.transform);

        balance = GameObject.Find("Balance");
        //Disable<Transform>(balance.transform);

        receipt = GameObject.Find("Receipt");
        closeTransform = GetComponent<Transform>();

        gameState = GameObject.Find("GameManager").GetComponent<GameState>();
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Disable<Transform>(roadNumber.transform);
            Disable<Transform>(tlNumber.transform);
            Disable<Transform>(erpNumber.transform);

            Disable<Transform>(roadTax.transform);
            Disable<Transform>(tlTax.transform);
            Disable<Transform>(erpTax.transform);

            Disable<Transform>(totalTax.transform);
            Disable<Transform>(balance.transform);

            Disable<Transform>(receipt.transform);
            Disable<Transform>(closeTransform);

            gameState.ResetDay();
            gameState.SetPause(false);
            gameState.GameOver();
        }
    }
}