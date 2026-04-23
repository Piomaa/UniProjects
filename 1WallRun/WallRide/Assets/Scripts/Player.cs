using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using UnityEditor;
using UnityEngine;
using UnityEngine.UIElements;
using static UnityEngine.EventSystems.StandaloneInputModule;

public class Player : MonoBehaviour
{
    [SerializeField] private float horizontalSpeed = 1;
    Rigidbody rb;
    AudioSource playerCrashSFX;
    private bool isRunning = true;
    private float score;
    private float elapsed;
    private int controlMode;
    private void Start()
    {
        rb = GetComponent<Rigidbody>(); // this component is used to apply the forward force that moves the player forward
        playerCrashSFX = GameObject.Find("PlayerSFX").GetComponent<AudioSource>(); // instance for sound effect
        controlMode = PlayerPrefs.GetInt("ControlMode"); // preference for how the player wants to control the movement
    }
    void FixedUpdate() // fixed update ensures more consistent movement
    {
        score = transform.position.z; // increases scored based on player position
        elapsed += Time.deltaTime; // time spent in gameplay
        if (isRunning)
        {
            rb.AddForce(Vector3.forward * (Mathf.Clamp(10f + Mathf.Log(elapsed, 2), 10f, 50f))); // speed increases logarithmically based on time spent in game
            if (Input.GetKey(KeyCode.LeftArrow))
            {
                transform.position += Vector3.left * Time.deltaTime * horizontalSpeed; // using this instead of physics based movement makes for more snappy movement

            }
            if (Input.GetKey(KeyCode.RightArrow))
            {
                transform.position += Vector3.right * Time.deltaTime * horizontalSpeed;

            }

            if (controlMode == 1) // check which control preference the player selected
            {
                TapMovement();
            }
            if (controlMode == 2)
            {
                AccelMovement();
            }
        }
    }

    void TapMovement()
    {
        if (Input.touchCount == 1) // if a tap is detected
        {
            if (Input.touches[0].position.x < (Screen.width * 0.5)) // if input is on the left hand of the screen
            {
                transform.position += Vector3.left * Time.deltaTime * horizontalSpeed; // move
            }
            if (Input.touches[0].position.x > (Screen.width * 0.5)) // if input is on the right hand of the screen
            {
                transform.position += Vector3.right * Time.deltaTime * horizontalSpeed;
            }

        }
    }

    void AccelMovement()
    {
        transform.position += Vector3.right * (Input.acceleration.x * horizontalSpeed) * Time.deltaTime; // take the accelerometer values and add them to the movement
    }


    private void OnCollisionEnter(Collision collision) // when the player hits a collider
    {
        if (PlayerPrefs.GetInt("Vibration") == 1) // vibrate if the setting is on
        {
            Handheld.Vibrate();
        }
        rb.velocity = Vector3.zero; // stop the player
        isRunning = false; // for the game manager 
        playerCrashSFX.Play(); // play crash sound
    }

    public float GetScore()
    {
        return score;   
    }

    public bool GetStatus()
    {
        return isRunning;
    }

}
