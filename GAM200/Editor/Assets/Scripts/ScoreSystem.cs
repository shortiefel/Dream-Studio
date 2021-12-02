//using System;
//using System.Collections;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
////using TMPro;
//
//public class ScoreSystem : MonoBehaviour
//{
//    /*[SerializeField] TextMeshProUGUI scoreTxt;
//    [SerializeField] TextMeshProUGUI highScoreTxt;
//    int score = 0;
//    int highScore = 0;
//
//    public GameOverControl gameOverUI;
//
//
//    public static ScoreSystem Instance { get; private set; }
//
//    public override void Awake()
//    {
//        if (Instance != null)
//        {
//            Destroy(this);
//        }
//        else
//        {
//            Instance = this;
//        }
//    }
//
//    // Start is called before the first frame update
//    public override void Start()
//    {
//        //reset
//        scoreTxt.text = score.ToString();
//        // default value = 0;
//        highScoreTxt.text = PlayerPrefs.GetInt("HighScore", 0).ToString();
//    }
//
//    // Update is called once per frame
//    public override void Update()
//    {
//        // Add points when no. of cars travelled for orders
//        // Maybe extra points when happiness meter goes up
//
//        *//*if (Input.GetKeyDown(KeyCode.Q))
//        {
//            DeleteGameObject();
//            scoreTxt.text = score.ToString();
//        }*//*
//        if (Input.GetKeyDown(KeyCode.Y))
//        {
//            AddScore();
//        }
//
//        UpdateHighScore();
//    }
//
//
//
//    public void UpdateHighScore()
//    {
//        if (score > PlayerPrefs.GetInt("HighScore", 0))
//        {
//            // Store player high scores in unity
//            PlayerPrefs.SetInt("HighScore", highScore);
//            //update highscore
//            highScore = score;
//            highScoreTxt.text = highScore.ToString();
//        }
//    }
//
//    void DeleteGameObject()
//    {
//        *//*while (GameObject.Find("JobNotification"))
//        {
//            // Kills the game object in 5 seconds after loading the object
//            gameObject.SetActive(false);
//            //Destroy(gameObject, 5);
//            AddScore();
//        }*//*
//
//    }
//
//    // When orders are completed, add points to the score
//    public void AddScore()
//    {
//        Debug.Log(score);
//        ++score;
//        scoreTxt.SetText(score.ToString());// = score.ToString();
//        Debug.Log(score);
//        Debug.Log("Money score Added");
//
//    }
//
//    public void ResetScore()
//    {
//        score = 0;
//        scoreTxt.text = score.ToString();
//    }
//
//    public void ResetSavedHighScore()
//    {
//        // Deleting the high score saved in unity
//        PlayerPrefs.DeleteAll();
//        highScoreTxt.text = highScore.ToString();
//    }*/
//}

