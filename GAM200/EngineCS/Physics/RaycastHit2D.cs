


public class RaycastHit2D
{
    public float distance;
	public Vector2 point;
	public Transform transform;
	public Collider collider;
}

public class RaycastHit2DGroup
{
	public float[] distance = new float[10];
	public Vector2[] point = new Vector2[10];
	public Transform[] transform = new Transform[10];
	public Collider[] collider = new Collider[10];
	public int count = 0;
}