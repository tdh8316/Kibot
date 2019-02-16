package com.tdh8316.kibot.client

import org.json.JSONException
import org.json.JSONObject

fun getObject(s: String): String {
    var o = ""
    val keys: MutableIterator<String> = classInfo!!.keys()
    classInfoReversed = JSONObject()
    while (keys.hasNext()) {
        val key: String = keys.next()
        classInfoReversed!!.put(classInfo!!.getString(key), key)
    }
    try {
        if (classInfo!!.getString(s) != null) {
            o = s
        }
    } catch (e: JSONException) {
        if (classInfoReversed!!.getString(s) != null) {
            o = s
        }
    }
    // TODO: NLP
    return o
}