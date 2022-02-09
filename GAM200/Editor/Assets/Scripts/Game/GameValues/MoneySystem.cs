using System;

public class MoneySystem : MonoBehaviour
{
    GameState gameState;
    Text textComp;

    private int money;
    private int currErp;
    private int currTL;

    public override void Start()
    {
        currErp = 1;
        money = 1000;
        currTL = 1;
        textComp = GetComponent<Text>();
        textComp.text = money.ToString();
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

    public int GetMoney()
    {
        return money;
    }
    public int GetCurrErp()
    {
        return currErp;
    }

    public void BuildErp()
    {
        money -= (currErp * 20);
        textComp.text = money.ToString();
        currErp++;
    }
    public void DestoryErp()
    {
        money = money + 10;
        textComp.text = money.ToString();
        currErp--;
    }
    public int GetCurrTL()
    {
        return currTL;
    }
    public void BuildTrafficLight()
    {
        money -= (int)(currTL * 50 * 1.2);
        textComp.text = money.ToString();
        currTL++;
    }
    public void DestroyTL()
    {
        currTL--;
    }
}

