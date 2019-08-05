using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyGizmo : MonoBehaviour {
    public Color _color = Color.yellow;
    public float _radius = 0.1f;

    void OnDrawGizmos() {
        Gizmos.color = _color;
        Gizmos.DrawSphere(transform.position, _radius);
    }

}
