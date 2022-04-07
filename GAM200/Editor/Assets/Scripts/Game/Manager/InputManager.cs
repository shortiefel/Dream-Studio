﻿using System;
using System.Collections;
using System.Collections.Generic;

public class InputManager : MonoBehaviour
{
	public Action<Vector2Int> OnMouseClick, OnMouseHold;
	public Action OnMouseUp;
	//private Vector2 cameraMovementVector;

	public Camera mainCamera;

	public bool OverGameObject;

	PlacementManager placementManager;

	//public LayerMask groundMask;
	GameState gameState;

	static public bool allowBuilding = true;

	public bool removeCarBool = false;
	public Transform removeCarCursor;

	public override void Start()
	{
		gameState = GameObject.Find("GameManager").GetComponent<GameState>();
		mainCamera = GameObject.Find("Camera").GetComponent<Camera>();

		placementManager = GameObject.Find("PlacementManager").GetComponent<PlacementManager>();

		OverGameObject = false;

		removeCarCursor = GameObject.Find("RemoveCarCollider").GetComponent<Transform>();
	}

	//private void Update()
	public override void Update()
	{
		if (removeCarBool)
        {
			Vector2Int pos = RaycastGround();
			if (placementManager.CheckIfPositionInBound(pos))
				removeCarCursor.position = new Vector2(pos);

		}
		//if (Input.GetMouseButtonDown(MouseCode.Left))
		//{
		//	Vector3 mPos = mainCamera.ScreenToWorldPoint(Input.GetMousePosition());
		//	Vector2 mousePos = Vector2Int.RoundToInt(new Vector2(mPos.x, mPos.y));
		//	//Vector2 startPos = placementManager.placementGrid.GetStartPoint();
		//	//Vector2 endPos = placementManager.placementGrid.GetGridSize() + startPos;
		//	//Console.WriteLine("Actual Mouse position: " + mousePos + " ------------------------------------------\n");
		//
		//	Vector2Int offset = -placementManager.placementGrid.GetStartPoint();
		//	//Console.WriteLine("offset: " + (offset) + " ------------------------------------------\n");
		//	//Console.WriteLine("actually the Actual Mouse position: " + (offset + mousePos) + " ------------------------------------------\n");
		//
		//}
		if (Input.GetKeyDown(KeyCode.M) && Input.GetKey(KeyCode.Shift))
		{
			//placementManager.placementGrid.Expand();
			gameState.ExpandGrid();
		}

		//if (!gameState.GetPause())
		//{
		//	bool state = gameState.GetDrawMode();
		//	if (Input.GetMouseButtonDown(MouseCode.Left)) {
		//		if (!state)
		//		{
		//			var position = RaycastGround();
		//			if (position != null)
		//			{
		//				if (CheckIfOutside(position.Value) == true)
		//				{
		//					SwitchMode();
		//					return;
		//				}
		//			}
		//		}

		//		else
		//		{
		//			var position = RaycastGround();
		//			if (position != null) {
		//				if (CheckIfOutside(position.Value) == false)
		//				{
		//					SwitchMode();
		//					return;
		//				}
		//			}
		//		}
		//	}
		//}

		////if (Mathf.Approximately(0f, Time.timeScale)) return;
		//if (!gameState.ShouldDraw()) return;
		if (!allowBuilding) return;
		CheckClickDownEvent();
		CheckClickHoldEvent();
		CheckClickUpEvent();
		//CheckArrowInput();
	}

	//public Vector2 CameraMovementVector
	//{
	//	get { return cameraMovementVector; }
	//}

	private Vector2Int RaycastGround()
	{
		//RaycastHit2D hit = Physics2D.RayCast(mainCamera.ScreenToWorldPoint(Input.GetMousePosition()), Vector2.zero);
		//
		//if (hit.collider != null)
		//{
		//	Vector2Int positionInt = Vector2Int.RoundToInt(hit.point);
		//	return positionInt;
		//}
		//
		//return null;

		Vector3 vec3 = mainCamera.ScreenToWorldPoint(Input.GetMousePosition());
		return Vector2Int.RoundToInt(new Vector2(vec3.x, vec3.y));
	}

	//private void CheckArrowInput()
	//{
	//	cameraMovementVector = new Vector2(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical"));
	//}

	private void CheckClickHoldEvent()
	{
		//if (Input.GetMouseButton(0) && OverGameObject)
		if (Input.GetMouseButton(0))
		{
			var position = RaycastGround();
			/*if (position != null)
				OnMouseHold?.Invoke(position.Value);*/
			//if (position != null) {
				if (OnMouseHold != null)
					OnMouseHold.Invoke(position); 
					//OnMouseHold.Invoke(position.value); 
			//}
		}
	}

	private void CheckClickUpEvent()
	{
		//if (Input.GetMouseButtonUp(0) && OverGameObject)
		if (Input.GetMouseButtonUp(0))
		{
			//Console.WriteLine("out");
			//OnMouseUp?.Invoke();
			if (OnMouseUp != null)
			{
				//Console.WriteLine("not null");
				OnMouseUp.Invoke();
			}
		}
	}

	private void CheckClickDownEvent()
	{
		//if (Input.GetMouseButtonDown(0) && OverGameObject)
		if (Input.GetMouseButtonDown(0))
		{
			var position = RaycastGround();
			/*if (position != null)
				OnMouseClick?.Invoke(position.Value);*/
			//if (position != null) {
				if (OnMouseClick != null)
					OnMouseClick.Invoke(position);
					//OnMouseClick.Invoke(position.Value);
			//}
		}
	}

	//public void SwitchMode()
	//{

	//	if (gameState.GetDrawMode())
	//	{
	//		SceneManager.SetDrawMode(false);

	//		//drawModeBool = false;
	//		gameState.SetDrawMode(false);
	//	}
	//	else
	//	{
	//		SceneManager.SetDrawMode(true);

	//		//drawModeBool = true;
	//		gameState.SetDrawMode(true);
	//	}
	//}

	/*
	 * True = inside
	 * False = outside
	*/

	/*bool CheckIfOutside(Vector2Int pos)
    {
		Vector2Int startPoint = placementManager.placementGrid.GetStartPoint();
		Vector2Int gridSize = placementManager.placementGrid.GetGridSize() + startPoint;
		return (pos.x >= startPoint.x && pos.x < gridSize.x && pos.y >= startPoint.y && pos.y < gridSize.y);
	}*/
}