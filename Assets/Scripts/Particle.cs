using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class Particle : MonoBehaviour
{
    public float Gravity;
    public Vector2 BoundsHalfSize;

    private Vector2 _position;
    private Vector2 _velocity;
    private RectTransform _rect;

    private void Start()
    {
        _rect = GetComponent<RectTransform>();
        _position = _rect.localPosition;
    }

    void Update()
    {
        _velocity += Gravity * Time.deltaTime * Vector2.down;
        _position += _velocity * Time.deltaTime;

        _rect.localPosition = _position;
    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.green;
        Gizmos.DrawWireCube(Vector2.zero, BoundsHalfSize * 2);
    }
}
