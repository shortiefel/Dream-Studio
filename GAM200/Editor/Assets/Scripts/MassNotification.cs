using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class MassNotification : MonoBehaviour
{
    public Prefab notiPrefab;
    public int prefabCounter = 5;


    GameObject[] n_inactive; // inactive notification array
    GameObject[] n_active;

    public static MassNotification Instance { get; private set; }

    public override void Awake()
    {
        if (Instance != null)
        {
            Destroy(this);
        }
        else
        {
            Instance = this;
        }
    }

    public override void Start()
    {
        notiPrefab = new Prefab("notification"); //Need to have the same texture name
    }

    public void CreateNotificationModel()
    {
        GameObject[] temp = new GameObject[prefabCounter];
        for (int index = 0; index < prefabCounter; index++)
        {
            GameObject initNow = Instantiate(notiPrefab, new Vector3(0, 0, 1), Quaternion.identity);
            initNow.SetActive(false);
            temp[index] = initNow;
        }

        n_inactive = temp;
    }

    // Reusing the game objects
    public void PlaceNotif(Vector2Int newPos)
    {
        Vector3 pos = new Vector3((newPos.x - 0.4f), (newPos.y + 0.5f), 1);
        if (SearchVaildInactiveObjectIndex() > n_inactive.Length)
        {
            Debug.Log("Sorry, No notification left to fill up");
            return;
        }

        int index = SearchVaildInactiveObjectIndex();

        GameObject temp = n_inactive[index];
        n_inactive[index] = null;

        temp.transform.position = pos;
        temp.SetActive(true);
    }

    private int SearchVaildInactiveObjectIndex()
    {
        // how to only retun int when i want to 
        int index;

        for (index = 0; index < n_inactive.Length; ++index)
        {
            if (n_inactive[index] != null)
            {
                return index;
                // go find the object and set active
            }
        }
        return n_inactive.Length;
    }

    public int SearchEmptyInactiveObjectIndex()
    {
        // how to only retun int when i want to 
        int index;

        for (index = 0; index < n_inactive.Length; ++index)
        {
            if (n_inactive[index] == null)
            {
                return index;
                // go find the object and set active
            }
        }
        return n_inactive.Length;
    }


    public void ReturnNPrefab(GameObject notification)
    {
        if (GetInactiveObjectLength() >= n_inactive.Length)
        {
            Debug.Log("Sorry, Array is full. No empty slots to fill");
            return;
        }
        Debug.Log("Valid Inactive Length: " + GetInactiveObjectLength());
        //find the first empty slot
        n_inactive[SearchEmptyInactiveObjectIndex()] = notification;
        notification.SetActive(false);
        Debug.Log("Valid Inactive Length: " + GetInactiveObjectLength());


    }

    private int GetInactiveObjectLength()
    {
        int counter = 0;
        for (int index = 0; index < n_inactive.Length; ++index)
        {

            if (n_inactive[index] != null)
            {
                counter++;
            }

        }
        return counter;
    }
}
