using System;
using System.Collections;
using System.Collections.Generic;

public class InputManager : MonoBehaviour
{
	public static Action<Vector2Int> OnMouseClick, OnMouseHold;
	public static Action OnMouseUp;

	private Vector2 cameraMovementVector;
	private bool OverGameObject;
	
	Camera mainCamera;
	InputManager inputManager;

	//public LayerMask groundMask;

	public override void Start()
	{
		inputManager = GetComponent<InputManager>();
		mainCamera = GameObject.Find("Camera").GetComponent<Camera>();
	}

	public Vector2 CameraMovementVector
	{
		get { return inputManager.cameraMovementVector; }
	}

	//private void Update()
	public override void Update()
	{
		CheckClickDownEvent();
		CheckClickUpEvent();
		CheckClickHoldEvent();
		//CheckArrowInput();
	}

	private Vector2Int? RaycastGround()
	{
		//RaycastHit2D hit;
		//Ray2D ray = mainCamera.ScreenPointToRay(Input.mousePosition);
		//Debug.Log(ray);
		//if (Physics2D.Raycast(ray, out hit, Mathf.Infinity, groundMask))
		
		RaycastHit2D hit = Physics2D.RayCast(mainCamera.ScreenToWorldPoint(Input.GetMousePosition()), Vector2.zero);

		if (hit.collider != null)
		{
			//Debug.Log(hit.point);
			Vector2Int positionInt = Vector2Int.RoundToInt(hit.point);
			//Debug.Log(positionInt);
			return positionInt;
		}
		//else
			//Debug.Log("did not hit");
		return null;
	}

	//private void CheckArrowInput()
	//{
	//	cameraMovementVector = new Vector2(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical"));
	//}

	public override void OnMouseEnter()
	{
		inputManager.OverGameObject = true;
	}

	public override void OnMouseExit()
	{
		inputManager.OverGameObject = false;
	}

	private void CheckClickHoldEvent()
	{
		if (Input.GetMouseButton(0) && inputManager.OverGameObject)
		//if (Input.GetMouseButton(0))
		{
			//Debug.Log("here1");
			var position = RaycastGround();
			/*if (position != null)
				OnMouseHold?.Invoke(position.Value);*/
			if (position != null)
			{
				Console.WriteLine("here11113");
				if (OnMouseHold != null)
				{
					Console.WriteLine("here111114");
					//OnMouseHold.Invoke(position.Value);
				}
			}
		}
	}

	private void CheckClickUpEvent()
	{
		if (Input.GetMouseButtonUp(0) && inputManager.OverGameObject)
		{
			//OnMouseUp?.Invoke();
			if (OnMouseUp != null)
				OnMouseUp.Invoke();
		}
	}

	private void CheckClickDownEvent()
	{
		//Console.WriteLine("sodos  " + inputManager.OverGameObject);
		if (Input.GetMouseButtonDown(0) && inputManager.OverGameObject)
		{
			Debug.Log("here2");
			var position = RaycastGround();
			/*if (position != null)
				OnMouseClick?.Invoke(position.Value);*/
			if (position != null)
				if(OnMouseClick != null)
					OnMouseClick.Invoke(position.Value);

		}
	}
}
