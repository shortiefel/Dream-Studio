using System;

public class RollingCredits : MonoBehaviour
{

  
    public override void Start()
    {
      
    }

    public override void Update()
    {
  
        transform.Move(new Vector2(0f, Time.deltaTime * 2f));

    }
}