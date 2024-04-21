using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class Particle : MonoBehaviour
{
    public float Gravity = 9.8f;
    public float Radius = 25.0f; 

    private Vector2 _position;
    private Vector2 _velocity;
    private RectTransform _rect;

    private void Start()
    {
        _rect = GetComponent<RectTransform>();
        _position = _rect.localPosition;
    }

    private void OnValidate()
    {
        GetComponent<RectTransform>().sizeDelta = new Vector2(Radius * 2, Radius * 2);
    }

    void Update()
    {
        _velocity += Gravity * Time.deltaTime * Vector2.down;
        _position += _velocity * Time.deltaTime;
        ResolveCollisions();

        _rect.localPosition = _position;
    }

    private void ResolveCollisions()
    {
        Vector2 halfScreenSize = new Vector2(Screen.width, Screen.height) / 2;
        if (Mathf.Abs(_position.x) > halfScreenSize.x)
        {
            _position.x = halfScreenSize.x * Mathf.Sign(_position.x);
            _velocity.x *= -1;
        }
        if (Mathf.Abs(_position.y) > halfScreenSize.y)
        {
            _position.y = halfScreenSize.y * Mathf.Sign(_position.y);
            _velocity.y *= -1;
        }
    }
}
