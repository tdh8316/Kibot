package com.takturstudio.kibot.client

import android.os.Bundle
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
                "bluetoothInit" -> bluetoothService.init()
                "bluetoothWrite" -> {
                    try {
                        result.success(bluetoothService.write(call.arguments.toString()))
                    } catch (e: Exception) {
                        result.error("No appropriate paired devices.", e.toString(), null)
                    } catch (e: UninitializedPropertyAccessException) {
                        result.error("Bluetooth is disabled.", e.toString(), null)
                    }
                }
                else -> result.notImplemented()
            }
        }
    }
}
