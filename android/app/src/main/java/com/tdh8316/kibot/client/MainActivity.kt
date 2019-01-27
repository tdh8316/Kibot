package com.tdh8316.kibot.client

import android.app.AlertDialog
import android.bluetooth.BluetoothDevice
import android.content.pm.ActivityInfo
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.WindowManager
import me.aflak.bluetooth.Bluetooth
import me.aflak.bluetooth.DiscoveryCallback


class MainActivity : AppCompatActivity() {

    private var bluetooth: Bluetooth = Bluetooth(this)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        window.setFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS, 512)
        window.addFlags(WindowManager.LayoutParams.FLAG_SHOW_WALLPAPER)
        window.addFlags(524288) // FLAG_SHOW_WHEN_LOCKED

        initBluetooth()
    }

    private fun initBluetooth() {
        bluetooth.onStart()
        bluetooth.enable()
        bluetooth.setDiscoveryCallback(object : DiscoveryCallback {
            override fun onDiscoveryStarted() {}
            override fun onDiscoveryFinished() {}
            override fun onDeviceUnpaired(device: BluetoothDevice) {}
            override fun onError(message: String) {}
            override fun onDeviceFound(device: BluetoothDevice) {}
            override fun onDevicePaired(device: BluetoothDevice) {}
        })
        bluetooth.connectToName(KIBOT_BLUETOOTH_NAME)
        val devices = bluetooth.pairedDevices
        val device = devices[0]
        device.createBond()
        device.setPin(byteArrayOf(KIBOT_BLUETOOTH_PIN.toByte()))
        bluetooth.connectToDevice(device)
    }

    @Suppress("unused")
    private fun sendToKibot(str: String) {
        if (!bluetooth.isConnected) {
            showDialog("└(๑•Kibot 과 연결되어있지 않아요...•́๑)┐")
        } else {
            bluetooth.send(str)
        }
    }

    private fun showDialog(msg: String, title: String = "강원중학교 안내봇") {
        val builder = AlertDialog.Builder(this)
        builder.setTitle(title)
        builder.setMessage(msg)
        builder.setPositiveButton("확인", null)
        builder.show()
    }

    override fun onStop() {
        super.onStop()
        bluetooth.onStop()
    }

    override fun onBackPressed() {
        return
    }

    override fun onUserLeaveHint() {
        // INFO: DO NOT EDIT THIS SECTION
        // startActivity(Intent(this, MainActivity::class.java))
    }
}
