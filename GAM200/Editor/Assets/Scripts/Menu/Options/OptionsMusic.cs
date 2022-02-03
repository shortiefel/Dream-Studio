using System;

public class OptionsMusic : MonoBehaviour
{
    Transform muteBGMX;
    Transform muteSFXX;

    private bool muteBGM;
    private bool muteSFX;
    private bool muteMaster;

    private static float volMaster;

    Text textVolume;

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

        muteBGM = AudioSource.GetGroup_Mute(AudioGroup.Music);
        muteSFX = AudioSource.GetGroup_Mute(AudioGroup.SFX);
        muteMaster = AudioSource.GetGroup_Mute(AudioGroup.Master);

        volMaster = AudioSource.GetGroup_Volume(AudioGroup.Master);

        textVolume = GameObject.Find("VolumeAdjust").GetComponent<Text>();
        textVolume.text = Convert.ToString(volMaster);

        if (GameObject.Find("UpVol").entityId == entityId)
            type = ButtonType.UP;
        else if (GameObject.Find("DownVol").entityId == entityId)
            type = ButtonType.DOWN;
        else if (GameObject.Find("MuteBGM").entityId == entityId)
        {
            type = ButtonType.BGMMute;
            muteBGMX = GameObject.Find("BGMMuteX").transform;
            if (!muteBGM) Disable<Transform>(muteBGMX);
        }
        else if (GameObject.Find("MuteSFX").entityId == entityId)
        {
            type = ButtonType.SFXMute;
            muteSFXX = GameObject.Find("SFXMuteX").transform;
            if (!muteSFX) Disable<Transform>(muteSFXX);
        }

        Debug.Log("Type " + type);
        
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

    //public override void Update()
    //{
    //    //textComp.text = Convert.ToString(volObject.volume);
    //}

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            Debug.Log("Hit inside");
            switch(type)
            {
                case ButtonType.UP:
                    volMaster += 10;
                    Debug.Log(volMaster);
                    if (volMaster > 100) volMaster = 100;
                    textVolume.text = Convert.ToString(volMaster);
                    AudioSource.SetGroup_Volume(AudioGroup.Master, volMaster);
                    break;

                case ButtonType.DOWN:
                    volMaster -= 10;
                    Debug.Log(volMaster);
                    if (volMaster < 0) volMaster = 0;
                    textVolume.text = Convert.ToString(volMaster);
                    AudioSource.SetGroup_Volume(AudioGroup.Master, volMaster);
                    break;

                case ButtonType.BGMMute:
                    muteBGM = !muteBGM;
                    if (muteBGM) Enable<Transform>(muteBGMX);
                    else Disable<Transform>(muteBGMX);
                    AudioSource.SetGroup_Mute(AudioGroup.Music, muteBGM);
                    Debug.Log("Mute BGM");
                    break;

                case ButtonType.SFXMute:
                    muteSFX = !muteSFX;
                    if (muteSFX) Enable<Transform>(muteSFXX);
                    else Disable<Transform>(muteSFXX);
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

