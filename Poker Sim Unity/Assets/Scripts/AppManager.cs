/*
 MIT License
 Copyright (c) 2016 Andrey Lopukhov
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;

public class AppManager : MonoBehaviour
{

    [Header("Result text reference")]
    public Text[] allTexts;
    [HideInInspector]
    public List<string> rememberState;

    [DllImport("Lib", EntryPoint = "gendeck")]
    public static extern void GenDeck();
    [DllImport("Lib", EntryPoint = "getResults")]
    public static extern void GetResults(byte[] buf);

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

    private void Awake()
    {
        foreach (var item in allTexts)
        {
            rememberState.Add(item.text);
        }
    }

    private void ParseResults(string results)
    {
        char delim = System.Convert.ToChar(";");
        string[] parsedResults = results.Split(delim);

        for (int i = 0; i < allTexts.Length; i++)
        {
            allTexts[i].text = rememberState[i].Substring(0, rememberState[i].Length - 1) + parsedResults[i];
            allTexts[i].text += " -> " + (float.Parse(parsedResults[i]) / float.Parse(parsedResults[parsedResults.Length - 1]) * 100).ToString("n4") + "%";
        }
    }

    private IEnumerator DisplayResults()
    {
        byte[] buf = new byte[300];

        while (true)
        {
            GetResults(buf);
            //Debug.Log(System.Text.Encoding.ASCII.GetString(buf));
            ParseResults(System.Text.Encoding.ASCII.GetString(buf));
            yield return null;
        }
    }
}
