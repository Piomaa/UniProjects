using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SocialPlatforms;
using UnityEngine.SocialPlatforms.Impl;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public GameObject player;
    public GameObject pauseMenu;
    private int newScore;
    public TMP_Text uiScore;
    private bool isRunning;

    void Start()
    {
        Resume(); // unpause the game
        isRunning = player.GetComponent<Player>().GetStatus(); // grabs the status of the player (if it's crashed or not)
        StartCoroutine(GameUpdate()); // update the score and ends game if player has crashed
    }

    public void UpdateHighScore()
    {
        if (newScore > PlayerPrefs.GetInt("HighScore"))
        {
            PlayerPrefs.SetInt("HighScore", newScore);
        }
    }

    public IEnumerator GameUpdate()
    {
        while (isRunning)
        {
            newScore = (int)player.GetComponent<Player>().GetScore(); // take the current score from the player class
            isRunning = player.GetComponent<Player>().GetStatus(); // take the player status from its class
            UpdateUIScore(newScore); // refresh the score text
            yield return new WaitForSeconds(0.5f);
        }
        if (!isRunning)
        {
            EndGame(); // end the game if the player is no longer running
        }
    }
    void UpdateUIScore(int score)
    {
          uiScore.SetText(score.ToString("0")); // simple conversion to string and set the ui text to the score
    }

    public void EndGame()
    {
        UpdateHighScore(); 
        PauseGame(); // freeze game time
        pauseMenu.SetActive(true); // bring up the pause menu
    }

    public void PauseGame()
    {
        Time.timeScale = 0f; // set game time to 0 (paused)
    }

    public void Resume()
    {
        Time.timeScale = 1.0f; // set game time to 1 (normal play)
    }

    public void Restart()
    {
        SceneManager.LoadScene("WallOfChina"); // reload scene, this is called from the start button in the main menu
    }
}
