package com.tdh8316.kibot.client

import org.json.JSONObject
import java.net.URL


fun initClassInfo() {
    val jsonString = URL(DATA_URL).readText()

    if (jsonString == "") {
        // TODO: Read something from internal storage
    } else {
        // TODO: Save it!
    }

    classInfo = JSONObject(jsonString)
}

fun getId(o: String): Int {
    // TODO: match id
    // classInfo!!.getString(o)
    return 101
}