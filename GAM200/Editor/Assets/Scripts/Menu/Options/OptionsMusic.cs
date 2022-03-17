using System;

public class OptionsMusic : MonoBehaviour
{
    Transform muteBGMX;
    Transform muteSFXX;

    private bool muteBGM;
    private bool muteSFX;
    private bool muteMaster;

    private static float volMaster;
    private static float volBGM;
    private static float volSFX;

    Text textVolume;
    Text BGMVolume;
    Text SFXVolume;


    public enum ButtonType
    {
        NONE = 0,
        UP,
        DOWN,
        BGMUP,
        BGMDOWN,
        SFXUP,
        SFXDOWN,
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
        volBGM = AudioSource.GetGroup_Volume(AudioGroup.Music);
        volSFX = AudioSource.GetGroup_Volume(AudioGroup.SFX);
        

        textVolume = GameObject.Find("VolumeAdjust").GetComponent<Text>();
        textVolume.text = Convert.ToString(volMaster);

        BGMVolume = GameObject.Find("VolumeAdjustBGM").GetComponent<Text>();
        BGMVolume.text = Convert.ToString(volBGM);

        SFXVolume = GameObject.Find("VolumeAdjustSFX").GetComponent<Text>();
        SFXVolume.text = Convert.ToString(volSFX);

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
        else if (GameObject.Find("UpBGMVol").entityId == entityId)
            type = ButtonType.BGMUP;
        else if (GameObject.Find("DownBGMVol").entityId == entityId)
            type = ButtonType.BGMDOWN;
        else if (GameObject.Find("UpSFXVol").entityId == entityId)
            type = ButtonType.SFXUP;
        else if (GameObject.Find("DownSFXVol").entityId == entityId)
            type = ButtonType.SFXDOWN;

        Debug.Log("Type " + type);
        

    }


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

                case ButtonType.BGMUP:
                    volBGM += 10;
                    Debug.Log(volBGM);
                    if (volBGM > 100) volBGM = 100;
                    BGMVolume.text = Convert.ToString(volBGM);
                    AudioSource.SetGroup_Volume(AudioGroup.Music, volBGM);
                    break;

                case ButtonType.BGMDOWN:
                    volBGM -= 10;
                    Debug.Log(volBGM);
                    if (volBGM < 0) volBGM = 0;
                    BGMVolume.text = Convert.ToString(volBGM);
                    AudioSource.SetGroup_Volume(AudioGroup.Music, volBGM);
                    break;

                case ButtonType.SFXUP:
                    volSFX += 10;
                    Debug.Log(volSFX);
                    if (volSFX > 100) volSFX = 100;
                    SFXVolume.text = Convert.ToString(volSFX);
                    AudioSource.SetGroup_Volume(AudioGroup.SFX, volSFX);
                    break;

                case ButtonType.SFXDOWN:
                    volSFX -= 10;
                    Debug.Log(volSFX);
                    if (volSFX < 0) volSFX = 0;
                    SFXVolume.text = Convert.ToString(volSFX);
                    AudioSource.SetGroup_Volume(AudioGroup.SFX, volSFX);
                    break;
            }
          
        }
    }

}

