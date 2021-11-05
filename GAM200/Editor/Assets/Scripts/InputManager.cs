using System;
using System.Collections;
using System.Collections.Generic;

public class InputManager : MonoBehaviour
{
	public Action<Vector2Int> OnMouseClick, OnMouseHold;
	public Action OnMouseUp;
	private Vector2 cameraMovementVector;

	public Camera mainCamera;

	public bool OverGameObject;

	//public LayerMask groundMask;

	public override void Start()
	{
		mainCamera = GameObject.Find("Camera").GetComponent<Camera>();
	}

	public Vector2 CameraMovementVector
	{
		get { return cameraMovementVector; }
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
			Debug.Log(hit.point);
			Vector2Int positionInt = Vector2Int.RoundToInt(hit.point);
			Debug.Log(positionInt);
			return positionInt;
		}
		else
			Debug.Log("did not hit");
		return null;
	}

	//private void CheckArrowInput()
	//{
	//	cameraMovementVector = new Vector2(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical"));
	//}

	public override void OnMouseEnter()
	{
		OverGameObject = true;
	}

	public override void OnMouseExit()
	{
		OverGameObject = false;
	}

	private void CheckClickHoldEvent()
	{
		//if (Input.GetMouseButton(0) && OverGameObject == false)
		if (Input.GetMouseButton(0))
		{
			//Debug.Log("here1");
			var position = RaycastGround();
			/*if (position != null)
				OnMouseHold?.Invoke(position.Value);*/
			if (position != null)
				if (OnMouseHold != null)
					OnMouseHold.Invoke(position.Value);
		}
	}

	private void CheckClickUpEvent()
	{
		if (Input.GetMouseButtonUp(0) && OverGameObject == false)
		{
			//OnMouseUp?.Invoke();
			if (OnMouseUp != null)
				OnMouseUp.Invoke();
		}
	}

	private void CheckClickDownEvent()
	{
		if (Input.GetMouseButtonDown(0) && OverGameObject == false)
		{
			//Debug.Log("here2");
			var position = RaycastGround();
			/*if (position != null)
				OnMouseClick?.Invoke(position.Value);*/
			if (position != null)
				if(OnMouseClick != null)
					OnMouseClick.Invoke(position.Value);

		}
	}
}
