using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;

public class AppManager : MonoBehaviour
{

    [Header("Result text reference")]
    public Text nothing;
    public Text pair;
    public Text twopair;
    public Text three;
    public Text straight;
    public Text flush;
    public Text full;
    public Text four;
    public Text straightFlush;
    public Text royal;
    public Text total;

    [Header("All result text reference")]
    public Text[] allTexts;
    [HideInInspector]
    public List<string> rememberState;

    [DllImport("Lib", EntryPoint = "gendeck")]
    public static extern void GenDeck();
    [DllImport("Lib", EntryPoint = "getResults")]
    public static extern void GetResults(byte[] buf);

    void Awake()
    {
        foreach (var item in allTexts)
        {
            rememberState.Add(item.text);
        }
    }

    public void StartWork()
    {
        GenDeck();
        StopAllCoroutines();
        StartCoroutine(DisplayResults());
    }

    public void StopWork()
    {
        StopAllCoroutines();
    }

    public void ResetResults()
    {
        StopAllCoroutines();

        for (int i = 0; i < allTexts.Length; i++)
        {
            allTexts[i].text = rememberState[i];
        }
    }

    IEnumerator DisplayResults()
    {
        byte[] buf = new byte[300];

        while (true)
        {
            GetResults(buf);
            Debug.Log(System.Text.Encoding.ASCII.GetString(buf));
            yield return new WaitForSeconds(1);
        }
    }
}
