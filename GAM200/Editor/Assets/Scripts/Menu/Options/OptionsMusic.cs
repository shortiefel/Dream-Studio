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
        UP = 0,
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

        if (GameObject.Find("UpVol").transform == transform)
            type = ButtonType.UP;
        else if (GameObject.Find("DownVol").transform == transform)
            type = ButtonType.DOWN;
        else if (GameObject.Find("MuteBGM").transform == transform)
            type = ButtonType.BGMMute;
        else if(GameObject.Find("MuteSFX").transform == transform)
            type = ButtonType.SFXMute;

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
            switch(type)
            {
                case ButtonType.UP:

                    break;

                case ButtonType.DOWN:

                    break;

                case ButtonType.BGMMute:
                    muteBGM = !muteBGM;
                    AudioSource.MuteGroup(AudioGroup.Music, muteBGM);
                    break;

                case ButtonType.SFXMute:
                    muteSFX = !muteSFX;
                    AudioSource.MuteGroup(AudioGroup.SFX, muteSFX);
                    break;
                case ButtonType.MasterMute:
                    muteMaster = !muteMaster;
                    AudioSource.MuteGroup(AudioGroup.Master, muteMaster);
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

