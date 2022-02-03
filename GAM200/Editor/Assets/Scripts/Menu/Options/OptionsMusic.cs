using System;

public class OptionsMusic : MonoBehaviour
{
  
    AudioSource volObject, BGM , SFX;
    Text textComp;
    bool buttonType, BGMMute, SFXMute;
    Transform MuteBGMX;
    Transform MuteSFXX;

    Transform VolumeUp;
    Transform VolumeDown;

    private float vol;

    private bool muteBGM;
    private bool muteSFX;
    private bool muteMaster;

    public enum ButtonType
    {
        NONE = 0,
        UP,
        DOWN,
        BGMMute,
        SFXMute,
        MasterMute
    };

    private ButtonType type;

    public override void Start()
    {
        //GetComponent<AudioSource>().Play();
        //vol = GetComponent<AudioSource>().volume;
        type = ButtonType.NONE;

        if (GameObject.Find("UpVol").entityId == entityId)
            type = ButtonType.UP;
        else if (GameObject.Find("DownVol").entityId == entityId)
            type = ButtonType.DOWN;
        else if (GameObject.Find("MuteBGM").entityId == entityId)
            type = ButtonType.BGMMute;
        else if(GameObject.Find("MuteSFX").entityId == entityId)
            type = ButtonType.SFXMute;
        Debug.Log(type);
        muteBGM = false;
        muteSFX = false;
        muteMaster = false;
        /**
         * VOLUMEES
         */
        //volObject = GameObject.Find("VolumeAdjust").GetComponent<AudioSource>();
        //textComp = GetComponent<Text>();
        //if (textComp != null)
        //    textComp.text = Convert.ToString(volObject.volume);

        //VolumeUp = GameObject.Find("UpVol").GetComponent<Transform>();
        //VolumeDown = GameObject.Find("DownVol").GetComponent<Transform>();




        /**
         * MUTINGS
         */
        //MuteBGMX = GameObject.Find("BGMMuteX").GetComponent<Transform>();
        //MuteSFXX = GameObject.Find("SFXMuteX").GetComponent<Transform>();

        //Disable<Transform>(MuteBGMX);
        //Disable<Transform>(MuteSFXX);

        //BGMMute = false;
        //SFXMute = false;

        //if (transform.entityId == GameObject.Find("MuteBGM").GetComponent<Transform>().entityId ||
        //  transform.entityId == GameObject.Find("MuteSFX").GetComponent<Transform>().entityId)
        //{
        //    Debug.Log("button loaded");
        //    buttonType = true;

        //}

        //Debug.Log("start loaded");
    }

    public override void Update()
    {
        //textComp.text = Convert.ToString(volObject.volume);
    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Debug.Log("Hit inside");
            switch(type)
            {
                case ButtonType.UP:

                    break;

                case ButtonType.DOWN:

                    break;

                case ButtonType.BGMMute:
                    muteBGM = !muteBGM;
                    AudioSource.SetGroup_Mute(AudioGroup.Music, muteBGM);
                    Debug.Log("Mute BGM");
                    break;

                case ButtonType.SFXMute:
                    muteSFX = !muteSFX;
                    AudioSource.SetGroup_Mute(AudioGroup.SFX, muteSFX);
                    Debug.Log("Mute SFX");
                    break;
                case ButtonType.MasterMute:
                    muteMaster = !muteMaster;
                    AudioSource.SetGroup_Mute(AudioGroup.Master, muteMaster);
                    break;
            }
        //    if (buttonType)
        //    {
        //        if (BGMMute)
        //        {
        //            Enable<Transform>(MuteBGMX);
        //        }
        //        else
        //        {
        //            Disable<Transform>(MuteBGMX);
        //        }

        //    }
        //    else
        //    {
        //        if (SFXMute)
        //        {
        //            Enable<Transform>(MuteSFXX);
        //        }
        //        else
        //        {
        //            Disable<Transform>(MuteSFXX);
        //        }
        //    }
          
        }
    }

}

