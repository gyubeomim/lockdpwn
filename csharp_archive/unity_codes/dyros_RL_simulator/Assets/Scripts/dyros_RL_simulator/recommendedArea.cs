/// Author: Samuel Arzt
/// Date: March 2017

using UnityEngine;
using System.Collections;

/// <summary>
/// Class representing a checkpoint of a race track.
/// </summary>
public class recommendedArea : MonoBehaviour {
    /// <summary>
    /// The radius in Unity units in which this checkpoint can be captured.
    /// </summary>
    private SpriteRenderer spriteRenderer;

    /// <summary>
    /// Whether or not this checkpoint is being drawn to screen.
    /// </summary>
    public bool IsVisible {
        get { return spriteRenderer.enabled; }
        set { spriteRenderer.enabled = value; }
    }

    void Awake() {
        spriteRenderer = GetComponent<SpriteRenderer>();
    }

    private void Start() {
        spriteRenderer.color = new Color(0f, 1f, 0f, 0f);
    }

}
