package com.takturstudio.kibot.client

import android.annotation.TargetApi
import android.app.AlertDialog
import android.os.Build
import android.os.Bundle
import android.util.Log
import android.view.WindowManager
import io.flutter.app.FlutterActivity
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugins.GeneratedPluginRegistrant


@TargetApi(Build.VERSION_CODES.KITKAT)
class MainActivity : FlutterActivity() {
    private val TAG = MainActivity::class.java.simpleName
    private val channel = "Kibot/client"
    private val MAC = "EF:F3:0D:AB:49:A3"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        window.addFlags(WindowManager.LayoutParams.FLAG_SHOW_WALLPAPER)
        window.addFlags(524288)
        GeneratedPluginRegistrant.registerWith(this)

        MethodChannel(flutterView, channel).setMethodCallHandler { call, result ->
            when (call.method.toString()) {
                "bluetoothInit" -> {
                    try {
                        Log.d(TAG, "Request: Bluetooth Init")
                        bluetoothInit()
                        result.success(null)
                    } catch (e: Exception) {
                        Log.d(this.channel, e.toString())
                        result.error(e.toString(), null, null)
                    }
                }
                "bluetoothWrite" -> {
                    try {
                        bluetoothWrite(call.arguments.toString())
                        result.success(null)
                    } catch (e: Exception) {
                        Log.d(this.channel, e.toString())
                        result.error(e.toString(), null, null)
                    }
                }
                else -> result.notImplemented()
            }
        }
    }

    override fun onUserLeaveHint() {
        // INFO: DO NOT EDIT THIS SECTION
        // startActivity(Intent(this, MainActivity::class.java))
    }

    private fun bluetoothInit() {
        //("EF:F3:0D:AB:49:A3")
        /*if (blueAdapter != null && blueAdapter.isEnabled) {
            val bondedDevices = blueAdapter.bondedDevices
            if (bondedDevices.size > 0) {
                val devices = bondedDevices.toTypedArray() as Array<*>
                Log.d("Bluetooth Initializer", "Bonded devices: $devices")
                val device = devices[0] as BluetoothDevice
                val uuids = device.uuids
                val socket = device.createRfcommSocketToServiceRecord(uuids[0].uuid)
                socket.connect()
                Log.d("Is socket connected", socket.isConnected.toString())
                outputStream = socket.outputStream
                inStream = socket.inputStream
            } else {
                Log.d("Bluetooth Initializer", "No bonded devices")
                throw NoSuchElementException("No bonded devices!")
            }
        }*/
    }

    private fun bluetoothWrite(str: String) {
        dialogShow(str)
    }

    private fun dialogShow(msg: String) {
        val builder = AlertDialog.Builder(this)
        builder.setTitle("Native Dialog")
        builder.setMessage(msg)
        builder.setPositiveButton("OK", null)
        builder.show()
    }
}
