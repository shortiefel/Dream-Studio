using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

public class StructureManager : MonoBehaviour
{
    public StructurePrefabWeighted[] housesPrefabs, specialPrefabs;
    public PlacementManager placementManager;
    //public NotificationManager notificationManager;


    private float[] houseWeights, specialWeights;

    //private void Start()
    public override void Start()
    {
        /*houseWeights = housesPrefabs.Select(prefabStats => prefabStats.weight).ToArray();
        specialWeights = specialPrefabs.Select(prefabStats => prefabStats.weight).ToArray();
        placementManager = GetComponent<Pl_roadListacementManager>();*/

        placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

        housesPrefabs = new StructurePrefabWeighted[2];
        housesPrefabs[0].prefab = new Prefab("HouseColour"); housesPrefabs[0].weight = 1;

        specialPrefabs = new StructurePrefabWeighted[2];
        specialPrefabs[0].prefab = new Prefab("DestinationColour"); specialPrefabs[0].weight = 1;

        houseWeights = new float[] { housesPrefabs[0].weight };
        specialWeights = new float[] { specialPrefabs[0].weight };
    }

    //private IEnumerator waitABit(Vector2Int newPos)
    //{
    //    Debug.Log("got wait until");
    //    yield return new WaitForSeconds(notificationManager.GetRandomNumber()); //tell unity to wait!!
    //    notificationManager.CreateNotificationModel(newPos);

    //}
    public void PlaceHouse(Vector2Int position)
    {
        Debug.Log("here house");
        if (CheckPositionBeforePlacement(position))
        {
            int randomIndex = GetRandomWeightedIndex(houseWeights);
            placementManager.PlaceObjectOnTheMap(position, housesPrefabs[randomIndex].prefab, CellType.Structure);
            //AudioPlayer.instance.PlayPlacementSound();
            //StartCoroutine(waitABit(position));
            Debug.Log("place house");
        }
    }

    public void PlaceSpecial(Vector2Int position)
    {
        if (CheckPositionBeforePlacement(position))
        {
            int randomIndex = GetRandomWeightedIndex(specialWeights);
            placementManager.PlaceObjectOnTheMap(position, specialPrefabs[randomIndex].prefab, CellType.Structure);
            //AudioPlayer.instance.PlayPlacementSound();
        }
    }

    private int GetRandomWeightedIndex(float[] weights)
    {
        float sum = 0f;
        for (int i = 0; i < weights.Length; i++)
        {
            sum += weights[i];
        }

        float randomValue = Random.Range(0, (int)sum);
        float tempSum = 0;
        for (int i = 0; i < weights.Length; i++)
        {
            //0->weight[0] weight[0]->weight[1]
            if (randomValue >= tempSum && randomValue < tempSum + weights[i])
            {
                return i;
            }
            tempSum += weights[i];
        }
        return 0;
    }

    // change to public cause jiayi needs to use in notification manager
    public bool CheckPositionBeforePlacement(Vector2Int position)
    {
        if (placementManager.CheckIfPositionInBound(position) == false)
        {
            Debug.Log("This position is out of bounds");
            return false;
        }
        if (placementManager.CheckIfPositionIsFree(position) == false)
        {
            Debug.Log("This position is not EMPTY");
            return false;
        }
        if (placementManager.GetNeighboursOfTypeFor(position, CellType.Road).Count <= 0)
        {
            Debug.Log("Must be placed near a road");
            return false;
        }
        return true;
    }
}

[Serializable]
public struct StructurePrefabWeighted
{
    public Prefab prefab;
    //[Range(0, 1)]
    public float weight;
}