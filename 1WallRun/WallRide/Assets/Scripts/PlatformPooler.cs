using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformPooler : MonoBehaviour
{
    public GameObject[] platformPrefabs;    // array to store every type of prefab to instantiate

    public int poolSize;

    public Dictionary<GameObject,bool> pool = new Dictionary<GameObject,bool>(); // dictionary to store all the objects

    public Transform spawnPosition;

    public Transform tempPosition;


    private void Start()
    {
        Spawn();

    }

    private void Spawn()
    {
        for (int i = 0; i < poolSize; i++)
        {
            GameObject obj = Instantiate(platformPrefabs[Random.Range(0, platformPrefabs.Length)], tempPosition.position, Quaternion.identity); // instantiate a random type of prefab for each type in the pool

            pool.Add(obj, true); // store each in pool and set as active
        }

        SpawnPrefab(); 
        SpawnPrefab();
        SpawnPrefab();
        SpawnPrefab();
        SpawnPrefab();
    }
    void SpawnPrefab()
    {
        foreach(KeyValuePair<GameObject, bool> obj in pool) // for each object in the dictionary
        {
            if (obj.Value == true) {

                pool[obj.Key] = false;
                obj.Key.transform.position = spawnPosition.position; // place prefab at the set spawn position

                NextSpawnPositionCal(obj.Key); // change spawn position

                StartCoroutine(ReturnPrefab(obj.Key)); // attempt to return eligible objects to an out of view location

                break;
            }
        }
    }

    void NextSpawnPositionCal(GameObject selPrefab)
    {
        spawnPosition.position = new Vector3(selPrefab.transform.position.x, selPrefab.transform.position.y, selPrefab.transform.position.z + selPrefab.GetComponent<Collider>().bounds.size.z); // this code decides the position of the next object
    }

    IEnumerator ReturnPrefab(GameObject selPrefab)
    {
        while(!selPrefab.GetComponent<Renderer>().isVisible) // while object not visible
        {
            yield return new WaitForEndOfFrame();
        }

        while (selPrefab.GetComponent<Renderer>().isVisible) // while object visible
        {
            yield return new WaitForEndOfFrame();
        }
        selPrefab.transform.position = tempPosition.position; // change position of this object

        pool[selPrefab] = true; // set as available for spawning

        SpawnPrefab();
 
    }

}
