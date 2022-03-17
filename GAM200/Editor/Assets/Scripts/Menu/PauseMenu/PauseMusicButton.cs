using System;

public class PauseMusicButton : MonoBehaviour
{
   
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
        SFXDOWN
   
    };

    private ButtonType type;

    public override void Start()
    {
        //GetComponent<AudioSource>().Play();
        //vol = GetComponent<AudioSource>().volume;
        type = ButtonType.NONE;

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
            switch (type)
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

