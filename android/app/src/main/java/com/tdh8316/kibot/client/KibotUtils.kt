package com.tdh8316.kibot.client

import android.util.Log
import org.json.JSONException
import org.json.JSONObject
import java.io.File
import java.net.URL


fun initClassInfo(file: File) {
    var jsonString: String? = null
    var err = false

    try {
        jsonString = URL(DATA_URL).readText()
    } catch (e: Exception) {
        Log.d("www", e.toString())
        err = true
    }

    if (jsonString == null || err || jsonString == "") {
        jsonString = file.readText()
    } else {
        file.run {
            createNewFile()
            writeText(text = jsonString)
        }
        Log.d(CLIENT_TAG, "Map data is saved")
    }

    classInfo = JSONObject(jsonString)
}

fun getId(o: String): Int? {
    return try {
        classInfo!!.getString(o)?.toInt()
    } catch (e: java.lang.Exception) {
        try {
            classInfoReversed!!.getString(o)?.toInt()
        } catch (e: JSONException) {
            null
        }
    }
}
