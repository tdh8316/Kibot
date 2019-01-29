package com.tdh8316.kibot.client

import org.json.JSONObject
import java.net.URL


fun initClassInfo() {
    val jsonString = URL(DATA_URL).readText()

    if (jsonString == "") {
        return
    }

    classInfo = JSONObject(jsonString)
}
