package com.tdh8316.kibot.client

import org.json.JSONObject

const val CLIENT_TAG: String = "KibotClient"
const val KIBOT_BLUETOOTH_PIN: Int = 1234
const val KIBOT_BLUETOOTH_NAME: String = "Kibot"
const val DATA_URL: String = "https://raw.githubusercontent.com/tdh8316/Kibot/master/client/share/classinfo.json"

var classInfo: JSONObject? = null
var classInfoReversed: JSONObject? = null
