/// Author: Samuel Arzt
/// Date: March 2017

#region Includes
using UnityEngine;
using System.Collections;
#endregion

/// <summary>
/// Component for car movement and collision detection.
/// </summary>
public class PlayerMovement : MonoBehaviour {
    #region Members

    /// 벽, 차에 부딪히는 경우 실행되는 event
    public event System.Action HitCar;

    //Movement constants
    private const float MAX_VEL = 20f;
    private const float ACCELERATION = 8f;
    private const float VEL_FRICT = 2f;
    private const float TURN_SPEED = 100;

    private PlayerCtrl p_controller;
    private State_dyrosRL state_dyrosRL;

    /// <summary>
    /// The current velocity of the car.
    /// </summary>
    public float Velocity {
        get;
        private set;
    }

    /// <summary>
    /// The current rotation of the car.
    /// </summary>
    public Quaternion Rotation {
        get;
        private set;
    }

    //Horizontal = engine force, Vertical = turning force
    private double p_horizontalInput, p_verticalInput;


    /// <summary>
    /// The current inputs for turning and engine force in this order.
    /// </summary>
    public double[] CurrentInputs {
        get { return new double[] { p_horizontalInput, p_verticalInput }; }
    }
    #endregion

    #region Constructors
    void Start() {
        p_controller = GetComponent<PlayerCtrl>();
    }
    #endregion

    #region Methods
    // Unity method for physics updates
    void FixedUpdate() {
        //Get user input if controller tells us to
        if (p_controller != null && p_controller.UseUserInput)
            CheckInput();

        ApplyInput();

        ApplyVelocity();

        ApplyFriction();
    }

    // Checks for user input
    private void CheckInput() {
        p_horizontalInput = Input.GetAxis("Horizontal");
        p_verticalInput = Input.GetAxis("Vertical");
    }

    // Applies the currently set input
    private void ApplyInput() {
        //Cap input 
        if (p_verticalInput > 1)
            p_verticalInput = 1;
        else if (p_verticalInput < -1)
            p_verticalInput = -1;

        if (p_horizontalInput > 1)
            p_horizontalInput = 1;
        else if (p_horizontalInput < -1)
            p_horizontalInput = -1;

        //Car can only accelerate further if velocity is lower than engineForce * MAX_VEL
        bool canAccelerate = false;
        if (p_verticalInput < 0)
            canAccelerate = Velocity > p_verticalInput * MAX_VEL;
        else if (p_verticalInput > 0)
            canAccelerate = Velocity < p_verticalInput * MAX_VEL;

        //Set velocity
        if (canAccelerate) {
            Velocity += (float)p_verticalInput * ACCELERATION * Time.deltaTime;

            //Cap velocity
            if (Velocity > MAX_VEL)
                Velocity = MAX_VEL;
            else if (Velocity < -MAX_VEL)
                Velocity = -MAX_VEL;
        }

        //Set rotation
        Rotation = transform.rotation;
        Rotation *= Quaternion.AngleAxis((float)-p_horizontalInput * TURN_SPEED * Time.deltaTime, new Vector3(0, 0, 1));
    }

    /// <summary>
    /// Sets the engine and turning input according to the given values.
    /// </summary>
    /// <param name="input">The inputs for turning and engine force in this order.</param>
    public void SetInputs(float turn, float engine) {
        p_horizontalInput = turn;
        p_verticalInput = engine;
    }

    // Applies the current velocity to the position of the car.
    private void ApplyVelocity() {
        Vector3 direction = new Vector3(0, 1, 0);
        transform.rotation = Rotation;
        direction = Rotation * direction;

        this.transform.position += direction * Velocity * Time.deltaTime;
    }

    // Applies some friction to velocity
    private void ApplyFriction() {
        if (p_verticalInput == 0) {
            if (Velocity > 0) {
                Velocity -= VEL_FRICT * Time.deltaTime;
                if (Velocity < 0)
                    Velocity = 0;
            }
            else if (Velocity < 0) {
                Velocity += VEL_FRICT * Time.deltaTime;
                if (Velocity > 0)
                    Velocity = 0;
            }
        }
    }

    // Unity method, triggered when collision was detected.
    void OnCollisionEnter2D(Collision2D coll) {
        Debug.Log("[*] collision occured!");
        if (HitCar != null)
            HitCar();
    }

    /// <summary>
    /// Stops all current movement of the car.
    /// </summary>
    public void Stop() {
        Velocity = 0;
        Rotation = Quaternion.AngleAxis(0, new Vector3(0, 0, 1));
    }
    #endregion
}
