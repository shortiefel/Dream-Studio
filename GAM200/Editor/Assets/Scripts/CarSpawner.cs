using System.Collections;
using System.Collections.Generic;

public class CarSpawner : MonoBehaviour
{
    public Prefab[] carPrefabs;

    private void Start()
    {
        Instantiate(SelectACarPrefab(), transform);
    }

    private Prefab SelectACarPrefab()
    {
        var randomIndex = Random.Range(0, carPrefabs.Length);
        return carPrefabs[randomIndex];
    }
}
