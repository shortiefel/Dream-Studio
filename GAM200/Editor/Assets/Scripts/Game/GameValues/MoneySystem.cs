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

    public override void Update()
    {
        textComp.text = money.ToString();
    }

    public void AddMoney(int val)
    {
        money += val;
    }

    public void MinusMoney(int val)
    {
        money -= val;
        if (money < 0) money = 0;
    }
}

