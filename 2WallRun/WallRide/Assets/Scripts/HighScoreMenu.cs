using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class HighScoreMenu : MonoBehaviour
{
    // Start is called before the first frame update
    public TMP_Text uiHighScore;
    private void OnEnable()
    {
        uiHighScore.SetText(PlayerPrefs.GetInt("HighScore").ToString("0")); // this updates the highscore whenever the highscore menu is brought up (should probably be moved to game manager script)
    }
}
