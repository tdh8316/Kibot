package com.tdh8316.kibot.client

import org.json.JSONObject

fun getObject(s: String): String {
    var o = ""
    val keys: MutableIterator<String> = classInfo!!.keys()
    val reversed = JSONObject()
    while (keys.hasNext()) {
        val key: String = keys.next()
        reversed.put(classInfo!!.getString(key), key)
    }
    if (classInfo!!.getString(s) != null) {
        o = s
    }
    // TODO: NLP
    return o
}