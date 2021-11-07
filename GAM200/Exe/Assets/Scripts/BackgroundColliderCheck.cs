
class BackgroundColliderCheck : MonoBehaviour
{
    public InputManager inputManager;

    public override void Start()
    {
        inputManager = GameObject.Find("InputManager").GetComponent<InputManager>();
    }

	public override void OnMouseEnter()
	{
		inputManager.OverGameObject = true;
	}

	public override void OnMouseExit()
	{
		inputManager.OverGameObject = false;
	}
}
