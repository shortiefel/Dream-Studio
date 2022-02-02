using System;

public class MoneySystem : MonoBehaviour
{
    GameState gameState;
    Text textComp;

    private int money;

    public override void Start()
    {
        money = 0;

        textComp = GetComponent<Text>();
    }

    public void AddMoney(int val)
    {
        money += val;
        textComp.text = money.ToString();
    }

    public void MinusMoney(int val)
    {
        money -= val;
        if (money < 0) money = 0;
        textComp.text = money.ToString();
    }
}

