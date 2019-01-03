package com.takturstudio.kibot.client

import android.annotation.TargetApi
import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.view.WindowManager
import com.takturstudio.kibot.client.bluetooth.BluetoothService
import io.flutter.app.FlutterActivity
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugins.GeneratedPluginRegistrant

class MainActivity : FlutterActivity() {
    private val channel = "Kibot/client"
    private val bluetoothService: BluetoothService = BluetoothService()
    @TargetApi(Build.VERSION_CODES.ECLAIR)
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        window.addFlags(WindowManager.LayoutParams.FLAG_SHOW_WALLPAPER)
        window.addFlags(524288)
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

    override fun onUserLeaveHint() {
        startActivity(Intent(this, MainActivity::class.java))
    }
}
