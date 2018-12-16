package com.takturstudio.kibot.client

import android.os.Bundle
import android.util.Log
import com.takturstudio.kibot.client.bluetooth.BluetoothService
import io.flutter.app.FlutterActivity
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugins.GeneratedPluginRegistrant

class MainActivity : FlutterActivity() {
    private val channel = "Kibot/client"
    private val bluetoothService: BluetoothService = BluetoothService()
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        GeneratedPluginRegistrant.registerWith(this)
        MethodChannel(flutterView, channel).setMethodCallHandler { call, result ->
            when (call.method.toString()) {
                "bluetoothInit" -> bluetoothInit()
                "bluetoothWrite" -> bluetoothWrite(call.arguments.toString())
                else -> result.notImplemented()
            }
        }
    }

    private fun bluetoothInit() {
        bluetoothService.init()
        Log.d(channel, "bluetooth initialized")
    }

    private fun bluetoothWrite(s: String) {
        bluetoothService.write(s)
        Log.d(channel, "write $s via bluetooth")
    }
}
