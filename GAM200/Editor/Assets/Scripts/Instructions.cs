using System;
using System.Collections.Generic;
using System.Linq;

public class Instructions : MonoBehaviour
{
    Rigidbody2D rb;
    Transform trans;

    public override void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        trans = GetComponent<Transform>();
    }
}
