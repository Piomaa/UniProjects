using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioManagerScript : MonoBehaviour
{
    private static AudioManagerScript _instance;
    public static AudioManagerScript Instance { get { return _instance; } }
    // Start is called before the first frame update
    private void Awake()
    {
        GameObject.Find("PlayerSFX").GetComponent<AudioSource>().volume = PlayerPrefs.GetFloat("Sfx"); // make sure settings are applied before game starts
        GameObject.Find("MainMusic").GetComponent<AudioSource>().volume = PlayerPrefs.GetFloat("Music"); // make sure settings are applied before game starts
        if (_instance != null& _instance != this)
        {
            Destroy(this.gameObject);   // ensure this is the only instance of audio that exists
        }
        else
        {
            _instance = this;
        }
    }

    private void Start()
    {

        {
            DontDestroyOnLoad(this.gameObject); // make the object a singleton, so that it's not destroyed upon loading the scene
        }
    }
}
