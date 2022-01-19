using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Vertex : IEquatable<Vertex>
{
    public Vector2 Position { get; private set; }
    public Vertex(Vector2 position)
    {
        this.Position = position;
    }
    public bool Equals(Vertex other)
    {
        return Vector2.Distance(Position, other.Position) < 0.0001f;
    }

    public override string ToString()
    {
        return Position.ToString();
    }
}
