using System.Collections.Generic;

public class CarManager : MonoBehaviour
{
    private List<uint> carLists;

    public override void Start()
    {
        carLists = new List<uint>();
    }

    public void RegisterCar(uint id)
    {
        carLists.Add(id);
    }

    public void RemoveCar(uint id)
    {
        carLists.Remove(id);
    }

    public bool IsCar(uint id)
    {
        foreach (var i in carLists) if (i == id) return true;
        return false;
    }
}
