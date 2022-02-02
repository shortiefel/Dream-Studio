using System;

public class OptionsMusic : MonoBehaviour
{
  
    AudioSource volObject, BGM , SFX;
    Text textComp;
    bool BGMMute, SFXMute;
    Transform MuteBGMX;
    Transform MuteSFXX;


    public override void Start()
    {
        //GetComponent<AudioSource>().Play();
        //BGM = GameObject.Find("Camera").GetComponent<AudioSource>();

        volObject = GameObject.Find("VolumeAdjust").GetComponent<AudioSource>();
        textComp = GetComponent<Text>();
        if (textComp != null)
            textComp.text = Convert.ToString(volObject.volume);
        MuteBGMX = GameObject.Find("BGMMuteX").GetComponent<Transform>();
        MuteSFXX = GameObject.Find("SFXMuteX").GetComponent<Transform>();

        Disable<Transform>(MuteBGMX);
        Disable<Transform>(MuteSFXX);

        BGMMute = false;
        SFXMute = false;

        Debug.Log("oshfddosfhoidsfjhoi");
    }

    public override void Update()
    {
        textComp.text = Convert.ToString(volObject.volume);

    }

    public override void OnMouseOver()
    {
        if (Input.GetMouseButtonDown(MouseCode.Left))
        {
            if (BGMMute)
            {
                Enable<Transform>(MuteBGMX);
              
                
            }
            else
            {
                Disable<Transform>(MuteBGMX);
            }
        }
    }

}

