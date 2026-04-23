using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SettingsManager : MonoBehaviour
{
    public int controlMode;
    public bool vibrations;
    public float sfx;
    public float music;
    public Toggle vibrationToggle;
    public Slider sfxSlider;
    public Slider musicSlider;

    // Start is called before the first frame update
    void Awake()
    {
        SavedSettings();
    }

    void SavedSettings() // store the saved settings in the corresponding values
    {
        vibrations = PlayerPrefs.GetInt("Vibrate") == 1;
        vibrationToggle.GetComponent<Toggle>().isOn = vibrations;
        controlMode = PlayerPrefs.GetInt("ControlMode");
        sfx = PlayerPrefs.GetFloat("Sfx");
        music = PlayerPrefs.GetFloat("Music");
        sfxSlider.value = sfx;
        musicSlider.value = music;
    }
    public void TiltMode() // set the control mode to tilt 
    {
        controlMode = 2; 
        PlayerPrefs.SetInt("ControlMode", controlMode);
    }
    public void TapMode() // set the control mode to tap
    {
        controlMode = 1;
        PlayerPrefs.SetInt("ControlMode", controlMode);
    }
    public void VibrationMode(Toggle toggle) // toggle vibration, playerprefs doesnt support bools so we have to convert
    {
        vibrations = toggle.isOn;
        PlayerPrefs.SetInt("Vibrate", Convert.ToInt32(toggle));
    }
    public void SfxValue(Slider value) // apply slider values for sfx
    {
        sfx = value.value;
        GameObject.Find("PlayerSFX").GetComponent<AudioSource>().volume = value.value;
        PlayerPrefs.SetFloat("Sfx", sfx);

    }
    public void MusicValue(Slider value) // apply slider values for music
    {
        music = value.value;
        GameObject.Find("MainMusic").GetComponent<AudioSource>().volume = value.value;
        PlayerPrefs.SetFloat("Music", music);
    }
}
